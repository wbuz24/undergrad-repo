.section .text 
.global sum_prod
sum_prod:

                  # a0 = const int32_t *values;
                  # a1 = uint64_t num_values;
                  # a2 = int32_t &product
                  # t0 = i
                  # t1 = sum

li    t0, 0       # i = 0
li    t1, 0       # sum = 0

li    t2, 1       # product

1:                # body of the loop
bge   t0, a1, 1f

slli  t3, t0, 2   # Multiply i by 4 (shift 1 by 2)
add   t3, a0, t3  # Update memory address
lw    t3, 0(t3)   # Dereference address to get integer
add   t1, t1, t3  # Add integer value to ret
mul   t2, t2, t3  # Mult integer value to ret

addi  t0, t0, 1   # Increment iterator

jal   zero, 1b    # Jump back to start


1: 
  
  mv  a0, t1
  sw  t2, 0(a2)   # save value of t2 
  ret             # returns a0  
