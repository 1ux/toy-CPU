#ifndef DEBUG_H
#define DEBUG_H

/**
* get2compl(): interprets the transfer value as two's complement
* Return: two's complement value between -32768 and 32767
*/

int32_t get2compl(uint16_t value);

/**
 * fprintBits(): interprets an integer value as a binary pattern.(Little-Endian)
 * if you transfer the datatype and the address of an integer,
 * the function will supply the binary representation.
 * (enter "stdout" as the last parameter for standard output,
 * otherwise enter a file pointer)
 * Return: none
 */

void fprintBits(size_t const size, void const * const ptr, FILE *file_pointer);

/**
 * makeHexDump(): writes the RAM content to a text file.
 * if you enter true for base_2, binary code is written to the text file,
 * otherwise hex code.
 * Return: none
 */

void makeHexDump(bool base_2, uint16_t ram[]);

#endif
