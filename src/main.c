#include "toy.h"
#include "./debug/debug.h"

int main(int argc, char *argv[])
{
    uint16_t ram[RAM_SIZE];

    if(initialise_ram(ram,argc,argv)==-1) return 1;
    makeHexDump(true,ram);

    return 0;
}
