# Will Buziak
# cs230
# lab 4
# Implement a structure to make a right triangle

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

addi sp, sp -32

# store save registers onto stack

sw  s0, 0(sp)
sw  s1, 4(sp)
sw  s2. 8(sp)

# compute the hypotenuse by calling sqrt


# compute theta0 & theta1 by calling asinf

# store everying into a0 -> return RightTriangle struct


# load values from stack back into save registers

lw  s0, 0(sp)
lw  sw, 4(sp)
lw  s2, 8(sp)

ret
