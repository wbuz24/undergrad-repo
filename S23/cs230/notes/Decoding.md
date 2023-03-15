# RISC-V Decoding Instructions

## Step 1: Determine the opcode

opcode stores:
 - Size
 - Type
 - Category

Little Endian systems store the least significant bits first.

```
0x40eeba33
33 ba ee 40
```

## Step 2: Narrow down the instruction with funct3 & funct7
 - "One bit has a lot of power"
 - "funct3 usually narrows it down, but not always, then we need funct7"
 - If two instructions have the same funct3, look at the funct7

```
0b0100_0000_1110_1110_1000_1010_0011_0011
```

sub   rd, rs1, rs2

sub   s4, t4, a4

```
0xFC04_3783

0b1111_1100_0000_0100_0011_0111_1000_0011
```
Step 1: opcode
- 1[000_0011] -> I-type
- Last 2 bits are 11, therefore it is a 32 bit instruction.

Break up the instruction:
- next 5 bits are rd
- next 3 bits are funct3
- next 5 bits are rs1
- last 12 bits are the immediate

Step 2: Narrow down the instruction 
 - funct3 details ld
 


