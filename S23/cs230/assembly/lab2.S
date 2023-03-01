# Will Buziak
# Lab2
# Return a random number between a minimum and max

.section .text
.global .get_rand
get_rand:

# a0 - min_val
# a1 - max_val
  ld    t1, 0(a0)   # load min_val into t1  
  sub   t0, a1, a0  # max_val - min_val
  addi  t0, t0, 1   # (max_val - min_val + 1)


  addi  sp, sp, -16 # allocate space on the stack
  sd    s0, 0(t0)      # save the value of t0      
  call  rand        # c std rand() stores output in a0
  add   a0, a0, t1  # min_val + rand()
  rem   a0, a0, t0  # a0 = (min_val + rand()) % (max_val - min_val + 1)

  addi  sp, sp, 16  # deallocate from the stack
  
  ret  
