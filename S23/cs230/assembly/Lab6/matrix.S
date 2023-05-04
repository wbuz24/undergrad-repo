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
 
 
 fmul.d  

 ret

 .section .text
 .global translate
 translate:



 .section .text
.global mul
mul:



.section .text
.global normalize
normalize:

