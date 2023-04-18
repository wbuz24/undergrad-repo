 # Will Buziak
 # mud lab
 # lab 5
 # implement all three methods for a mud

.section .text
.global look_at_room
look_at_room:

 # ao - const Room *r -> pointer to Room instance

 # printf(“%s\n%s\nExits: ”, r->title, r->description);
 # many if statements with prints

 ret

.section .text
.global look_at_all_rooms
look_at_all_rooms:
 # ao - const Room *rooms
 # a1 - int num_rooms

 addi  a2, a2, 0    # declare i
 
 bge   a2, a1, 1f   # for loop
 
 add   a0, a0, a2   # add rooms and i

 # store on the stack to make call?

 # call look_at_rooms(rooms + 1)
 # printf("\n")
 addi  a2, a2, 1    # increment i

 1:
 # end of for loop
 ret

.section .text
.global move_to
move_to:
 # a0 - Room *rooms
 # a1 - const Room *current
 # a2 - int direction

 addi a3, a3, -1
 bne  a4, a3, 1f

# a5 - current->exits[direction] 

 add  a0, a0, a5
 ret
 
1:

 # a0 - nullptr
 ret
