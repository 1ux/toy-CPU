#ifndef TOY_H
#define TOY_H

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CPU_TYPE "Koopman_TOY_CPU"
#define RAM_SIZE 4096 
#define CPU_WORD_SIZE 16


void print_instructionSet(void);
int initialise_ram(uint16_t *ram, int argc, char **argv ); 
uint8_t get_opcode(uint16_t instruction);
uint16_t find_data(uint16_t instruction);
int get2compl(uint16_t value); //not good place for something!
bool execute(uint8_t op_code, int data_addr,uint16_t *ram);

#endif
