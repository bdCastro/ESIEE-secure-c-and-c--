#include <stdio.h>

#define MAX_DATA_SIZE 255
#define DATA_SIZE 1000

// **FAKE, only so it compiles** Represents a file or a network packet
struct FakeFile {
  char size[MAX_DATA_SIZE];
  char* data;
};

void MockFileFormat(struct FakeFile* mock) {
  char size[1];
  size[0] = DATA_SIZE;

  char* data = (char*) malloc(DATA_SIZE);
  memset(data, 'A', DATA_SIZE);

  memcpy(mock->size, size, 1);
  mock->data = data;
}

int main(int args, char** argv) {
  /* Pretend this gives us the fake file (or a network packet) */
  struct FakeFile mock;
  MockFileFormat(&mock);

  char sizeBuf[1];
  memcpy(sizeBuf, mock.size, 1);

  char size = sizeBuf[0];
  if (size < MAX_DATA_SIZE) {
    char buffer[MAX_DATA_SIZE];
    memset(buffer, '\0', MAX_DATA_SIZE);
    memcpy(buffer, mock.data, size);
    printf("%s\n", buffer);
  }

  return 0;
}
