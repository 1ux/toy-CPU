#include "toy.h"
#include "./debug/debug.h"

#include<assert.h>

#ifndef NDEBUG
    #define DEBUG 
#endif


int main(int argc, char *argv[])
{
    uint16_t    ram[RAM_SIZE];
    uint16_t    ir=0;
    uint8_t     op_code;
    uint16_t    pc = 0;
    int         data_addr=0;
    bool        run = true;

    if(initialise_ram(ram,argc,argv)==-1) return 1;

//    while(run && pc<(RAM_SIZE-1))
//    {
        ir = ram[pc];
        op_code = get_opcode(ir);
        data_addr=find_data(ir);
        #ifdef DEBUG
            printf("OP Code: %u\n",op_code);
            printf("Adresse: %d\n",data_addr);
            makeHexDump(true,ram);
        #endif
        if(execute(op_code,data_addr,*ram))
            pc=data_addr(ram[pc]);
        else pc++;
//    }
 


    return 0;
}
