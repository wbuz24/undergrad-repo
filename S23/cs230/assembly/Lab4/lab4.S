# Will Buziak
# cs230
# lab 4
# Implement a structure to make a right triangle
# Assistance from TA Clayton Gilmer

.section .text
.global make_triangle
make_triangle:

# fa0 - float side0
# fa1 - float side1
# a0 - rightTriangle structure:

# Name   Offset    Size (bytes)
# s0     0         4
# s1     4         4
# hypo   8         4
# theta0 12        4
# theta1 16        4
# total size = 20 bytes

addi sp, sp, -48

# store save registers onto stack
fsd     fs0, 0(sp)
fsd     fs1, 8(sp)
fsd     fs2, 16(sp)
sd      s0, 24(sp)
sd      ra, 32(sp)

# move sid0 & side1 into save registers
fmv.s   fs0, fa0
fmv.s   fs1, fa1

# put sid0 & side1 into a0
fsw     fa0, 0(a0) 
fsw     fa1, 4(a0)

# save a0
mv      s0, a0

# compute the hypotenuse by calling sqrt
fmul.s  fa0, fs0, fs0
fmul.s  fa1, fs1, fs1 
fadd.s  fa0, fa0, fa1
fsqrt.s fa0, fa0  # fsqrt.s was ideal over call sqrt

# move hypotenuse into saved register and store 
fsw     fa0, 8(s0)
fmv.s   fs2, fa0

# compute theta0 & theta1 by calling asinf
fdiv.s  fa0, fs0, fs2
call asinf
fsw     fa0, 12(s0)

fdiv.s  fa0, fs1, fs2
call asinf
fsw     fa0, 16(s0)

# load values from stack back into save registers
fld     fs0, 0(sp) 
fld     fs1, 8(sp)
fld     fs2, 16(sp)
ld      s0, 24(sp)
ld      ra, 32(sp)

addi    sp, sp, 48

ret
