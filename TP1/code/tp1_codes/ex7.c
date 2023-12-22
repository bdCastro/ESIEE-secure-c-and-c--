#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>

#define DEFAULT_RECV_BUFFER_LEN 512
#define PORT 4444
#define REQ_READ 0x01

int serverSocket;
struct addrinfo* addrResult;

struct addrinfo* InitSock() {
  struct addrinfo hints;
  bzero(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo *addrResult = NULL;
  int res = getaddrinfo(NULL, "4444", &hints, &addrResult);
  if (res != 0) {
    return NULL;
  }

  return addrResult;
}

int CreateSocket(struct addrinfo* addrResult) {
  int s = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
  if (s == -1) {
    freeaddrinfo(addrResult);
    return -1;
  }

  int iResult = bind(s, addrResult->ai_addr, (int) addrResult->ai_addrlen);
  if (iResult == -1) {
    freeaddrinfo(addrResult);
    close(s);
    return -1;
  }

  return s;
}

int Listen() {
  printf("- Listening on port %d\n", PORT);
  int iResult = listen(serverSocket, SOMAXCONN);
  if (iResult == -1) {
    return -1;
  }

  return 1;
}

void ClientRequestHandler(int clientSocket,
                          struct sockaddr_in clientInfo, unsigned char packet[]) {
  unsigned char type = *(unsigned char*)&packet[0];
  switch (type) {
    case REQ_READ:
      unsigned short packetLen = htons(*(unsigned short*)&packet[1]);
      packet += (sizeof(unsigned char) + sizeof(unsigned short));
      char* payload = (char*) malloc(packetLen+1);
      memcpy(payload, packet, packetLen);
      payload[packetLen] = '\0';
      send(clientSocket, payload, packetLen, MSG_DONTROUTE);
      printf("- Returned %d unsigned chars\n", packetLen);
      free(payload);
      payload = NULL;
    break;
    default:
      send(clientSocket, "OK\n", 3, MSG_DONTROUTE);
    break;
  }
}

void ReceiveClientMessages(int clientSocket, struct sockaddr_in clientInfo) {
  unsigned char recvBuffer[DEFAULT_RECV_BUFFER_LEN+1];
  unsigned int recvBufferLen = DEFAULT_RECV_BUFFER_LEN;
  unsigned int bytesRead = 0;
  do {
    // recv() will complete when the input ends with \r\d
    bytesRead = recv(clientSocket, recvBuffer, recvBufferLen, MSG_PEEK);
    if (bytesRead > 0) {
      recvBuffer[bytesRead] = '\0';
      ClientRequestHandler(clientSocket, clientInfo, recvBuffer);
      bytesRead = 0;
    }
  } while (bytesRead > 0);
}

void AcceptConnection() {
  printf("- Ready to accept a connection\r\n");
  struct sockaddr_in clientInfo;
  int clientInfoLen = sizeof(clientInfo);
  int clientSocket = accept(serverSocket, (struct sockaddr*) &clientInfo, &clientInfoLen);
  char *ip = inet_ntoa(clientInfo.sin_addr);
  if (clientSocket == -1) {
    return;
  }

  printf("- Received a connection\n");
  ReceiveClientMessages(clientSocket, clientInfo);

  printf("- Shutting down connection\n");
  int iResult = shutdown(clientSocket, SHUT_RDWR);
  if (iResult == -1) {
    close(clientSocket);
  }
}


void StartVulnerableServer() {
  struct addrinfo* addrResult = InitSock();
  if (!addrResult) {
    printf("- Failed to InitSock.\n");
    return;
  }

  serverSocket = CreateSocket(addrResult);
  int iResult = Listen();
  if (!iResult) {
    return;
  }

  while (true) {
    AcceptConnection();
  }
}

int main(int argc, char** argv) {
  StartVulnerableServer();
  return 0;
}
