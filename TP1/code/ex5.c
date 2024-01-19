#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE 254
#define DATA_SIZE 100

// **FAKE, only so it compiles** Represents a file or a network packet
struct FakeFile {
  char size[MAX_DATA_SIZE];
  char* data;
};

int MockFileFormat(struct FakeFile* mock) {
  char size[1];
  size[0] = DATA_SIZE;

  char* data = (char*) malloc(DATA_SIZE);

  if(data == NULL) return 1;

  memset(data, 'A', DATA_SIZE);
  data[DATA_SIZE-1] = '\0';

  memcpy(mock->size, size, 1);
  mock->data = data;

  return 0;
}

int main() {
  /* Pretend this gives us the fake file (or a network packet) */
  struct FakeFile mock;
  if(MockFileFormat(&mock)) return 1;

  char sizeBuf[1];
  memcpy(sizeBuf, mock.size, 1);

  char size = sizeBuf[0];

  if (size < MAX_DATA_SIZE) {
    char buffer[MAX_DATA_SIZE];
    memset(buffer, '\0', MAX_DATA_SIZE);
    memcpy(buffer, mock.data, size);
    printf("%s\n", buffer);
  }

  free(mock.data);

  return 0;
}
