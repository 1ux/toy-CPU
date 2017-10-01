#ifndef DEBUG_H
#define DEBUG_H

/**
* get2compl(): interpret the transfer value as tow's complement
* Return: tow's complement value between -32768 and 32767
*/

int32_t get2compl(uint16_t value);

void fprintBits(size_t const size, void const * const ptr, FILE *file_pointer);
void makeHexDump(bool base_2, uint16_t ram[]);

#endif
