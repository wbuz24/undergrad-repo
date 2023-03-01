# Will Buziak
# Lab2
# Return a random number between a minimum and max

.section .text
.global get_rand
get_rand:

# a0 - min_val
# a1 - max_val
# int64_t get_rand (int64_t min_val, 
#                      int64_t max_val) 
# {
#   return min_val + rand() % (max_val – min_val + 1);
# }

  addi  sp, sp, -32 # allocates 32 bytes on stack
  sd    s0, 0(sp)   # stores double word s0 into the address of 0(sp) 
  sd    s1, 8(sp)
  sd    ra, 16(sp)  # stores ra (must store ara if function call)

  sub   t0, a1, a0  # max_val - min_val
  addi  t0, t0, 1   # (max_val - min_val + 1)
  
  mv    s0, t0
  mv    s1, a0

  call  rand        # c std rand() stores output in a0
  rem   a0, a0, s0  # a0 = (min_val + rand()) % (max_val - min_val + 1)
  add   a0, a0, s1 
  

  ld    ra, 16(sp)  # load registers
  ld    s1, 8(sp)
  ld    s0, 0(sp)

  addi  sp, sp, 32  # deallocate from the stack
 
  ret  
