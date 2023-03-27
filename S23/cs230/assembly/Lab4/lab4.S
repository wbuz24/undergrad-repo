# Will Buziak
# cs230
# lab 4
# Implement a structure to make a right triangle

.section .text
.global make_triangle
make_triangle:

# fa0 - float side0
# fa1 - float side1
# rightTriangle structure:
# Name   Offset    Size (bytes)
# s0     0         8
# s1     8         8
# hypo   16        8
# theta0 24        8
# theta1 32        8
# total size = 40 bytes -> 48 bytes from the stack just for struct


