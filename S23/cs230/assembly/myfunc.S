
 # assembly program notes
 # this program performs bubble sort

.section .text
.global myfunc
myfunc: 

 # void myfun(int32_t *values, uint64_t num_values);
 # void myfunc(a0, a1)

 # bool swapped;
 # uint64_t i;
 # uint64_t n;

 # do {
 #   swapped = false;
 #   for (i = 1; i < n; i++) {
 #     if (values[i - 1] > values[i]) {
 #       swap(values[i - 1], values[i]);
 #       swapped = true;
 #     }
 #   }
 #   n -= 1;
 # }


 # t0 = bool swapped
 # t1 = uint64_t i;
 # t2 = uint64_t n;

  mv   t2, a1        # t2 = n
1:
  li   t0, 0         # bool swapped = 0
 
  li   t1, 1         # i = 1
2:
  bge  t1, t2, 2f    # branch greater than or equal to
  
  slli t3, t1, 2     
  add  t3, a0, t3

  lw   t4, -4(t3)    # t4 = i - 1
  lw   t5, 0(a0)     # t5 = values[i]

  ble  t4, t5, 3f
  li   t0, 1         # swapped = true

  sw   t4, 0(t3)  
  sw   t5, 04(t3)

3:
  addi t1, t1, 1     # i++
  j    2b            # jump to beginning of for loop

2:

  addi t3, t2, -1    
  bne  t0, zero, 1b  # while (swapped)

  ret                # return

