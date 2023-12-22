#include <Windows.h>
#include <stdio.h>

#define ORIGINAL_STRING_SIZE 1024

int main(int args, char** argv) {
  WCHAR buffer[32];
  memset(buffer, '\0', sizeof(buffer));
  MultiByteToWideChar(CP_ACP, 0, argv[1], -1, buffer, sizeof(buffer));
  wprintf(L"%ls\n", buffer);
  return 0;
}
