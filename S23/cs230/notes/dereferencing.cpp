struct MyStruct {
  int a;
  char b;
}

extern "C" {

}

int main() {

  // compiles
  // assembles
  // links
  // operating system reads executable into memory
  MyStruct ms; // allocates memory on the stack
  MyStruct *ms2 = new MyStruct; // allocates memory on the heap

  ms.a = 100; // moves the stack pointer and operates on the memory
  ms.b = 'c';

  // ms2.a = 45 does not work
  // ms2.b = 's' does not work, must dereference

  (*ms2).a = 45;
  (*ms2).b = 's';
}
