.section .text
.global myfunc
myfunc:
                            # a0 - double *value
                            # fa0 - double value2

  fld     ft0, 0(a0)        # dest, offset(rd) 
  fadd.d  fa0, fa0, ft0     # add is commutative

  ret                       # returns a0
