#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main(int args, char** argv) {
  /*
   *  Initialize the socket
   */
  sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = INADDR_ANY;
  local.sin_port = htons((u_short) 8080);

  /*
   *  Check and see if we have a valid socket to go on
   */
  int s;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1) {
    cout << "[x] Invalid socket. Abort" << endl;
    return -1;
  }

  /*
   *  Attempt to bind to the socket
   */
  if (bind(s, (sockaddr*) &local, sizeof(local)) != 0) {
    cout << "[x] Unable to bind. Abort" << endl;
    return -1;
  }

  /*
   *  Start listening
   */
  if (listen(s, 10) != 0) {
    cout << "[x] Unable to listen. Abort" << endl;
    return -1;
  }
  cout << "[*] Listening on port 8080..." << endl;

  int cli;
  sockaddr_in src;
  socklen_t srcLen = sizeof(src);

  while (true) {
    cli = accept(s, (struct sockaddr*) &src, &srcLen);
    int r;

    /* Keep recving until the client closes the connection */
    do {
      char *recvBuf = (char*) malloc(1024);
      memset(recvBuf, 0x00, 1024);
      r = recv(cli, recvBuf, 1023, 0);

      cout << "Client: " << recvBuf << endl;
      cout << "[*] ACK!" << endl;

      // Send the client something
      char *buf = "hello\n";
      send(cli, buf, strlen(buf), 0);
    } while (r > 0);

    /* 0 = RECV ; 1 = SEND ; 2 = BOTH */
    shutdown(cli, 2);
    close(cli);
  }

  close(s);
  return 0;
}
