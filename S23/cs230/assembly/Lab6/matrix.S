 # Will Buziak
 # extra credit lab
 # matrix manipulations

# struct Vector { float v[4]; }
# struct Matrix { float m[16]; }

#   n       o         s   ->  Vector
# float     0         8
# float     8         8
# float     16        8
# float     24        8
# total size = 32 bytes

#   n       o         s   ->  Matrix
# float     0         8
# float     8         8
# float     16        8
# float     24        8
# float     32        8
# float     40        8
# float     48        8
# float     56        8
# float     64        8
# float     72        8
# float     80        8
# float     88        8
# float     96        8
# float     104       8
# float     112       8
# float     120       8
# total size = 128 bytes

.section .text
.global scale
scale:
 # a0 - const Matrix &orig
 # fa0 - float sx
 # fa1 - float sy 
 # fa2 - float sz

 mv  t0, a0  # move a0 into t0
 flw  ft1, 0(t0)
 flw  ft2, 20(t0)
 flw  ft3, 40(t0) # load each value
 

 fmul.s ft0, fa0, ft1 # multiply each value
 fmul.s ft4, fa1, ft2
 fmul.s ft5, fa2, ft3

 fsw  ft0, 0(t0) # store each value back into t0
 fsw  ft4, 20(t0)
 fsw  ft5, 40(t0)

 mv  a0, t0 # move t0 back into a0
 ret

.section .text
.global translate
translate:

 mv  t0, a0

 flw ft0, 12(t0) # load each word
 flw ft1, 28(t0)
 flw ft2, 44(t0)

 fadd.s ft0, fa0, ft0 # add each value
 fadd.s ft1, fa1, ft1
 fadd.s ft2, fa2, ft2

 fsw ft0, 12(t0) # store each value back into t0
 fsw ft1, 28(t0)
 fsw ft2, 44(t0)

 mv  a0, t0
 ret

.section .text
.global mul
mul:
 mv  t5, a0 # matrix m
 mv  t0, a1 # vector v
 
 li  t0, 4 # iterator row
 li  t1, 0 # i = 0
 

1:
 beq t0, t1, 1f # 
 li  t3, 0.0F

 sw  t3, t1(t0)  
 li  t2, 0 # col = 0
 

 2:
   beq  t0, t2, 2f
   
   flw  t6, t2(t0) 
   slli t7, t1, 2
   add  t7, t7, t2
   flw  t7, t7(t5)
   fmul.s t7, t7, t6

   fsw  t7, t1(t0)
   
   addi  t2, t2, 1 # increment col
   j  2b
 2:

 addi t1, t1, 1 # increment row
 j  1b
1: 
 
 mv  a0, t0
 ret

.section .text
.global norm
norm:

mv  t0, a0

li  t1, 0
fmv.w.x ft0, t1
li  t1, 0
li  t2, 4

1:
  beq t2, t1, 1f
  

  fadd.s ft0, ft0, ft2

1:

mv  a0, t0
ret
