#ifndef TOY_H
#define TOY_H

#define CPU_TYPE "Koopman_TOY_CPU"
#define RAM_SIZE 4096
#define CPU_WORD_SIZE 16


extern const uint16_t * const ACCU; //read only access to accu

/**
* print_instructionSet(): print the cpu instruction set
* This is a user help function, can be activated via
* the -h paramter.
* Return: none
*/

void print_instructionSet(void);

/**
* initialise_ram(): read inputstream into the toy-ram
* Return:
*	the number of successfully read machine words,
*	-1 in case of error
*/

int initialise_ram(uint16_t *ram, int argc, char **argv );

/**
* get_opcode(): segments the mashine code in the OP-Code
* Return: 4 bit OP-Code
*/

uint8_t get_opcode(uint16_t instruction);

/**
* get_data(): get the addressed data from the RAM
* Return: the 12 bit data address
*/

uint16_t get_data(uint16_t instruction);

/**
* execute(): execute the toy-CPU instruction
* This function implements the CPU instruction set,
* use print_instructionSet() for an overview.
* Return: true if there is a jump
*/

bool execute(uint8_t op_code, int data_addr,uint16_t *ram);

#endif
