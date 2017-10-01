#ifndef DEBUG_H
#define DEBUG_H

/**
* get2compl(): interprets the transfer value as tow's complement
* Return: tow's complement value between -32768 and 32767
*/

int32_t get2compl(uint16_t value);

/**
 * fprintBits(): interprets an integer value as a binary pattern.(little endian)
 * if you pass the datatype and the address of an integer,
 * the funktion will supply the binary representation.
 * (give "stdout" as the last parameter for standard output,
 * otherwise hand over a filepointer)
 * Return: none
 */

void fprintBits(size_t const size, void const * const ptr, FILE *file_pointer);

/**
 * makeHexDump(): writes the RAM content to a textfile.
 * if you pass true to base_2, binary code is written to the textfile,
 * otherwise hexcode.
 * Return: none
 */

void makeHexDump(bool base_2, uint16_t ram[]);

#endif
