#ifndef TOY_H
#define TOY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define RAM_SIZE 4096 
#define CPU_WORD_SIZE 16


int initialise_ram(uint16_t *ram, int argc, char **argv ); 
uint8_t get_opcode(uint16_t instruction);
int find_data(uint16_t instruction);

#endif
