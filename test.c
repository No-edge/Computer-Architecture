#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* You may find implementing this function helpful */
int bitSigner(unsigned int field UNUSED, unsigned int size UNUSED) {
    /* YOUR CODE HERE */
    return 0;
}

/* You may find implementing this function handy */
int get_imm_operand(Instruction inst UNUSED) {//deal with jalr ...
    /* YOUR CODE HERE */
    //I-type
    unsigned int a = inst.itype.imm;
    int b=0x800;
    b=b&a;
    if(b==0x800)
    {
        a-=1;
        a=~a;
    }
    //把二进制转换成十进制
    int sum=0;
    for(int i=0;i<12;i++)
    {
        b=0x1;
        b=b<<i;
        int c=a&b;
        if(c==b)
        {
            sum+=c;
        }
    }
    if(b==0x800)
    {
        sum=-1*sum;
    }
            
    return sum;
            
}//输入为I-type

/* Remember that the offsets should return the offset in BYTES */

int get_branch_offset(Instruction inst UNUSED) {//deal with beq...
    /* YOUR CODE HERE */
    //SB-type

    //拼接，所得的imm的值为imm
    unsigned int a1,a2,a3,a4;
    unsigned int imm5,imm7;
    imm5=inst.sbtype.imm5;
    imm7=inst.sbtype.imm7;
    a3=imm5&0x1;
    a3=a3<<10;
    a1=imm5>>1;
    int per=1<<6;
    a4=imm7&per;
    a2=imm7-a4;
    a2=a2<<4;
    a4=a4<<5;
    unsigned int imm;
    imm=a1+a2+a3+a4;

    //判断imm的正负
    if(a4==0x800)
    {
        imm-=1;
        imm=~imm;
    }
    //转换成十进制
    int sum=0;
    for(int i=0;i<12;i++)
    {
        int b=0x1;
        b=b<<i;
        int c=imm&b;
        if(c==b)
        {
            sum+=c;
        }   
    }

    if(a4==0x800)
    {
        sum=-1*sum;
    }
            
    return sum; 
}

int get_jump_offset(Instruction inst UNUSED) {//deal with jal
    /* YOUR CODE HERE */
    //UJ-type
    unsigned int a1,a2,a3,a4;
    unsigned int imm=inst.ujtype.imm;
    a4=imm&0x80000;
    a2=imm&0x100;
    a3=imm&0xff;
    a1=imm&0x7fe00;
    a1=a1>>9;
    a2=a2<<2;
    a3=a3<<11;
    imm=a1+a2+a3+a4;

    //判断imm的正负
    if(a4==0x80000)
    {        
        imm-=1;
        imm=~imm;
    }
    //转换成十进制
    int sum=0;
    for(int i=0;i<12;i++)
    {    
        int b=0x1;
        b=b<<i;
        int c=imm&b;
        if(c==b)
        {
            sum+=c;
        }   
    }

    if(a4==0x80000)
    {
        sum=-1*sum;
    }
                
    return sum; 
}

int get_store_offset(Instruction inst UNUSED) {//deal with sw,sb,sh...
    /* YOUR CODE HERE */
    //s-type
    unsigned int a2=inst.stype.imm7;
    unsigned int a1=inst.stype.imm5;
    a2=a2<<5;
    unsigned int imm=a1+a2;
    //判断imm的正负
    int a=0x800;
    a=a&imm;
    if(a==0x800)
    {
        imm-=1;
        imm=~imm;
    }
    int sum=0;
    for(int i=0;i<12;i++)
    {
        int b=0x1;
        b=b<<i;
        int c=imm&b;
        if(c==b)
        {
            sum+=c;
        }   
    }

    if(a==0x800)
    {
        sum=-1*sum;
    }
        
    return sum;
 
}

void handle_invalid_instruction(Instruction inst) {
    printf("Invalid Instruction: 0x%08x\n", inst.bits); 
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}

