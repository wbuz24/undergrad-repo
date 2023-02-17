struct MyStruct {
  char a;
  int b;
  short c;
}

extern "C" {
  int all(MyStruct &ms); // memory address (as an int) of the struct
}

int main() {
  MyStruct ms = {5, 9, 32};


}
