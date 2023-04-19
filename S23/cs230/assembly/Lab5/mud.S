 # Will Buziak
 # mud lab
 # lab 5
 # implement all three methods for a mud

 # Room structure:
 
 # N             O        S
 # *title        0        8
 # *description  8        8
 # exits[4]      16       16

 # total size = 32 -> (32 % 16) = 0

.section .rodata
enter_prompt: .asciz "%s\n%s\nExits: "
exit0: .asciz "n "
exit1: .asciz "e "
exit2: .asciz "s "
exit3: .asciz "w "
all_rooms: .asciz "\n"


.section .text
.global look_at_room
look_at_room:

 addi sp, sp, -16
 
 sd   ra, 0(sp)
 sd   s0, 8(sp)

 mv   s0, a0
 ld   a1, 0(s0)
 ld   a2, 8(s0)

 # ao - const Room *r -> pointer to Room instance
 
 # printf(“%s\n%s\nExits: ”, r->title, r->description);
 la   a0, enter_prompt
 call printf

 li   a5, -1  # load -1
 ld   a1, 16(s0)
 ld   a2, 20(s0)
 ld   a3, 24(s0)
 ld   a4, 28(s0)

 bne  a1, a5, 1f
 bne  a2, a5, 2f
 bne  a3, a5, 3f
 bne  a4, a5, 4f
1:
 la   a0, exit0
 call printf
 j    5f
2:
 la   a0, exit1
 call printf
 j    5f
3:
 la  a0, exit2
 call printf
 j    5f
4:
 la  a0, exit3
 call printf
 j    5f

5:
 ret

.section .text
.global look_at_all_rooms
look_at_all_rooms:
 # ao - const Room *rooms
 # a1 - int num_rooms
 addi  sp, sp, -32  # allocate space on the stack
 sd    s0, 0(sp)    # store s0 on the stack
 sd    s1, 8(sp)    # store s1 on the stack
 sd    s2, 16(sp)   # store s2 on the stack
 sd    ra, 24(sp)


 addi  s2, s2, 0    # declare i
 mv    s0, a0       # move a0 into s0
 mv    s1, a1       # move a1 into s1 

 bge   s2, s1, 1f   # for loop, if i >= num_rooms, jump forward
 
 add   s0, s0, s2   # add rooms and i

 # call look_at_rooms(rooms + 1)
 mv    a0, s0       # move rooms back into a0 to be called
 call  look_at_room
 
 # store the newline character for printf to call in a0
 la    a0, all_rooms
 call  printf

 addi  s2, s2, 1    # increment i

 1:
 # end of for loop
 mv    a0, s0  # move s0 into a0
 ld    ra, 24(sp)
 ld    s2, 16(sp)
 ld    s1, 8(sp)
 ld    s0, 0(sp)
 addi  sp, sp, 32 # deallocate from the stack

 ret

.section .text
.global move_to
move_to:
 # a0 - Room *rooms
 # a1 - const Room *current
 # a2 - int direction

 li   a3, -1
 addi a1, a1, 16  # 16 + direction
 li   t0, 4
 mul  a2, a2, t0
 add  a2, a2, a1
 lw   a4, 0(a2)  # current->exits[direction]
 
 bne  a4, a3, 1f

# a5 - current->exits[direction] 
 slli a4, a4, 5
 add  a0, a0, a4
 ret
 
1:

 li  a0, 0 # return a nullptr
 ret
