.section .text
.global align_up
align_up:
  # a0 - value
  # return (value + 15 & -16

  addi   a0, a0, 15
  andi   a0, a0, -16
  ret    # will not allow "ret   a0"
