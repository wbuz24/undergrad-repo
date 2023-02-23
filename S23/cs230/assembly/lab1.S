.section .text 
.global sum_prod
sum_prod:

# a0 = const int32_t *values;
# a1 = uint64_t num_values;
# a2 = int32_t &product
# t0 = i
# t1 = sum

li    t0, 0     # i = 0
li    t1, 0     # sum = 0

li    t2, 1     # product

1:              # body of the loop
bge   t0, a1, 2f
lw    t3, 0(a0) # t3 = values[i];

add   t1, t1, t3
mul   a2, a2, t3




1: 
  
  mv a0, t1  
  ret            # returns a0 
