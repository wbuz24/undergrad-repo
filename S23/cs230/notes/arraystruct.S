.section .text
.global get_long
get_long:
  # a0 - const MyStruct *s
  # a1 - int index
 
  # struct MyStruct {
  #    int i;
  #    short j;
  #    long k;
  # };

  # extern "C" {
  #    long get_long(const MyStruct *ms, int index)
  # };

  # int main() {

  #    MyStruct ms[10];
  #    ms[3].k = -1111;

  #    cout << get_long(ms, 3);

  slli  a1, a1, 4   # shift left by four (multiply by 16)
  add   a0, a0, a1  # now looking at the base of element 3 (integer in third element)
  ld    a0, 8(a0)   # adds 8 to the base (getting to the long
  ret               # returns what is in a0
