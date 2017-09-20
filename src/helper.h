#ifndef DEBUG_H
#define DEBUG_H

void fprintBits(size_t const size, void const * const ptr, FILE *file_pointer);
void makeHexDump(bool base_2, uint16_t ram[]);

#endif
