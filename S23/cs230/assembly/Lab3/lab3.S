# Will Buziak
# 03/06/2023
# Go through an array of doubles and execute a function on each one.
# Performs basic floating point arithmetic and logic instructions


.section .text
.global map
map:

# a0 - double *values
# a1 - uint64_t num_values
# a2 - double (*mapping_func)
# fa0 - double map_value
# s3 - uint64_t i
# void, no ret 

 addi  sp, sp, -64    # allocate the stack

 sd        s0, 0(sp)  
 sd        s1, 8(sp)
 sd        s2, 16(sp)
 fsd       fs0, 24(sp)
 sd        s3, 32(sp)
 sd        s4, 40(sp)
 sd        ra, 48(sp)
 
 mv        s0, a0       # *values
 mv        s1, a1       # num_values
 mv        s2, a2       # mapping_func
 li        s3, 0        # i = 0 
 fmv.d     fs0, fa0     # map_values   
 
1:
 bge       s3, s1, 1f   # beginning of loop
 slli      t0, s3, 3    # offset * size
 add       s4, s0, t0   # base + offset * size
 fld       fa0, 0(s4)   # load values[i]
 fmv.d     fa1, fs0     # moves map_values into fa1 to be called

 jalr      ra, s2       # calling mapping_func

 fsd       fa0, 0(s4)   # save values[i]
 addi      s3, s3, 1    # increment i

 jal       zero, 1b     # jump back to the top
1:

 ld        s0, 0(sp)    
 ld        s1, 8(sp)
 ld        s2, 16(sp)
 fld       fs0, 24(sp)
 ld        s3, 32(sp)
 ld        s4, 40(sp)
 ld        ra, 48(sp)
 addi      sp, sp, 64   # deallocate the stack

.global map_add
map_add:

# fa0 - double left
# fa1 - double right
 
 fadd.d    fa0, fa0, fa1

 ret

.global map_sub
map_sub:

# fa0 - double left
# fa1 - double right
 
 fsub.d fa0, fa0, fa1

 ret

.global map_min
map_min:

# fa0 - double left
# fa1 - double right

 fmin.d fa0, fa0, fa1
 ret

.global map_max
map_max:

# fa0 - double left
# fa1 - double right

 fmax.d fa0, fa0, fa1
 ret
