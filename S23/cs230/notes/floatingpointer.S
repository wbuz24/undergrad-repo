# class notes March 3 2023
# accompanied with corresponding cpp file

.section .text
.global compare
compare:
  # fa0 - float a
  # fa1 - double b

  fcvt.d.s   fa0, fa0          # must convert because of mismatching data types (float and double, regardless of where they are stored)
  fld        fa1, 0(a0)
  feq.d      a0, fa0, fa1      # if equal to each other, value of a0 will be 1 
  ret                          # must be an integer or bool (from cpp declaration)
