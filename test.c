#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* You may find implementing this function helpful */
int bitSigner(unsigned int field UNUSED, unsigned int size UNUSED) {
    /* YOUR CODE HERE */
    return 0;
}

/* You may find implementing this function handy */
int get_imm_operand(Instruction inst UNUSED) {
    int retval;
    retval=(int)inst.itype.imm;
    if(retval > 2047) retval |= (-4096);
    return retval;
}

/* Remember that the offsets should return the offset in BYTES */

int get_branch_offset(Instruction inst UNUSED) {
    int pa,pb,pc,pd,retval;
    pc = inst.sbtype.imm5 & 1;
    pa = inst.sbtype.imm5 - pc;
    pd = (inst.sbtype.imm7 & (1<<6));
    pb = (inst.sbtype.imm7 - pd);
    retval = (pa >> 1) + (pc << 10) + (pb << 4) + (pd << 5);
    if(retval & (1<<11)) retval |= (-4096);
    return retval;
}

int get_jump_offset(Instruction inst UNUSED) {
    int pa,pb,pc,pd,retval;
    pa = (inst.ujtype.imm >> 9) & 1023;
    pb = (inst.ujtype.imm >> 8) & 1;
    pc = (inst.ujtype.imm) & 255;
    pd = (inst.ujtype.imm >> 19) & 1;
    retval = pa + (pb << 10) +(pc << 11) + (pd << 19);
    if(pd) retval |= (-1048576);
    return retval;
}

int get_store_offset(Instruction inst UNUSED) {
    int pa,pb,retval;
    pa = inst.stype.imm5;
    pb = inst.stype.imm7 << 5;
    retval = pb+pa;
    if(retval & (1<<11)) retval |= (-4096);
    return retval;
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
