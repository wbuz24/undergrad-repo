
import numpy                 # we import the array library

from matplotlib import pyplot    # import plotting library

myarray = numpy.linspace(0, 5, 10)
myarray
print(myarray) # Python does not require ; 

a = numpy.linspace(1,5,5)
b = a # assigns a pointer to a instead of copying the elements into b
      # i.e. when a is changed, b changes as well since it is an "address" or pointer
a[2] = 17 # changes second element in array a to 17
c = a.copy() # Now c is a copy of the elements of a and when changed does not affect c

