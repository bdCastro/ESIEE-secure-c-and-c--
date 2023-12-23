#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Object {
public:
  void* buf = NULL;

  Object() {
    buf = malloc(1024);
    printf("Object initialized\n");
  }

  ~Object() {
    printf("Destructor is triggered\n");
    free(buf);
    buf = NULL;
  }
};

void test(Object obj) {
  printf("In Function %s()\n", __func__);
}

int main(int args, char** argv) {
  Object obj;
  test(obj);
  return 0;
}
