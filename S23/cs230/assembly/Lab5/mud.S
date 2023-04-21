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

 lw   a1, 16(s0)
 bltz a1, 1f     # check if negative

 la   a0, exit0
 call printf
1:
 lw   a1, 20(s0)
 bltz a1, 2f

 la   a0, exit1
 call printf
2:
 lw   a1, 24(s0)
 bltz a1, 3f

 la  a0, exit2
 call printf
3:
 lw   a1, 28(s0)
 bltz a1, 4f
 
 la  a0, exit3
 call printf

4:
 la  a0, all_rooms
 call printf

 ld   ra, 0(sp)
 ld   s0, 8(sp)

 addi sp, sp, 16
 ret

.section .text
.global look_at_all_rooms
look_at_all_rooms:

 # la    a0, exit0
 # call printf

 # ao - const Room *rooms
 # a1 - int num_rooms
 addi  sp, sp, -32  # allocate space on the stack
 sd    s0, 0(sp)    # store s0 on the stack
 sd    s1, 8(sp)    # store s1 on the stack
 sd    s2, 16(sp)   # store s2 on the stack
 sd    ra, 24(sp)

 li    s2, 0        # declare i
 mv    s0, a0       # move a0 into s0
 mv    s1, a1       # move a1 into s1 

5:
 bge   s2, s1, 5f   # for loop, if i >= num_rooms, jump forward
 #li    t0, 32
 #mul   t1, t0, s2   # i * 32
 slli   t0, s2, 5
 add    a0, s0, t0   # add rooms and i
 
 # call look_at_rooms(rooms + 1)
 call  look_at_room
 # li    a0, 10
 # store the newline character for printf to call in a0
 la    a0, all_rooms
 call  printf

 addi  s2, s2, 1    # increment i
 j     5b
5:
 # end of for loop
 # mv    a0, s0  # move s0 into a0
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
 slli  a2, a2, 2
 add  a1, a2, a1
 lw   a4, 0(a1)  # current->exits[direction]
 
 bltz a4, 1f

 slli a4, a4, 5
 add  a0, a0, a4
 ret
 
1:

 li  a0, 0 # return a nullptr
 ret
