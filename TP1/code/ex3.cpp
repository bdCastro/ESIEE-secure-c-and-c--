#include <cassert>
#include <cstdio>

class SomeObject {
public:
  bool flag;
  SomeObject() : flag{false} {}
};

int main(int args, char** argv) {
  if (args <= 1) {
    return 0;
  }

  SomeObject* obj = new SomeObject();
  printf(argv[1]);
  printf("\n");

  assert(!obj->flag);
  delete(obj);
  obj = NULL;
  return 0;
}
