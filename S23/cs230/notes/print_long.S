.section .rodata
output: .asciz "%ld\n"

.section .text
.global print_long
print_long:
  # a0 - long values
  # printf("%ld\n", value);
  
  mv    a1, a0
  la    a0, output 
  call  printf     # overwrites the value of ra

  mv    ra, s5     # restore value of ra
  ld    s5, 0(sp)  # load s5
  addi  sp, sp, 16 
  ret
