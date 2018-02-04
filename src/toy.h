#ifndef TOY_H
#define TOY_H

#define CPU_TYPE "Koopman_TOY_CPU"
#define RAM_SIZE 4096
#define CPU_WORD_SIZE 16


extern const uint16_t * const ACCU; //read only access to accu

/**
* print_instructionSet(): prints the cpu instruction set.
* This is a user help function and can be activated via
* the -h parameter.
* Return: none
*/

void print_instructionSet(void);

/**
* print_instructionSet(): prints the cpu architecture.
* This is a user help function and can be activated via
* the -i parameter.
* Return: none
*/


void print_architecture(void);

/**
* print_instruction(): converts a OP-Code into a human word.
* Return: none
*/

void print_instruction(uint8_t opcode);

/**
* initialise_ram(): reads input stream into the toy-ram.
* Return:
*	the number of successfully read machine words,
*	-1 in case of error.
*/

int initialise_ram(uint16_t *ram, int argc, char **argv );

/**
* get_opcode(): segments machine code as OP-Code.
* Return: 4-bit OP-Code.
*/

uint8_t get_opcode(uint16_t instruction);

/**
* get_data(): gets the addressed data from RAM.
* Return: the 12-bit data address.
*/

uint16_t get_data(uint16_t instruction);

/**
* execute(): executes the toy-CPU instruction.
* This function implements the CPU instruction set;
* use print_instructionSet() for an overview.
* Return: true if there is a jump.
*/

bool execute(uint8_t op_code, int data_addr,uint16_t *ram);

#endif
