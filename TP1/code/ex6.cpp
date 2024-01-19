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

  Object(const Object& obj) {
    buf = malloc(1024);
    memcpy(buf, obj.buf, 1024);
    printf("Object copied\n");
  }

  Object& operator=(const Object& other) {
    memcpy(buf, other.buf, 1024);
    printf("buf copied\n");

    return *this;
  }

  ~Object() {
    printf("Destructor is triggered\n");
    free(buf);
    buf = NULL;
  }
};

void test() {
  printf("In Function %s()\n", __func__);
}

int main() {
  Object obj;
  test();
  return 0;
}
