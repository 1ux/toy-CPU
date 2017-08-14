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
    int         quit='n';
    bool        run = true;

    if(initialise_ram(ram,argc,argv)==-1) return 1;

    while(run && pc<(RAM_SIZE-1))
    {
        ir = ram[pc];
        op_code = get_opcode(ir);
        data_addr=find_data(ir);
        #ifdef DEBUG
            printf("OP Code: %"PRIu8"\n",op_code);
            printf("Adresse: %d\n",data_addr);
        #endif
        if(execute(op_code,data_addr,ram))
            pc=find_data(ram[pc]);              //jump if ACCU is ZERO
        else pc++;
        printf("(n)ext step or (q)uit or (c)oredump ?\n");
        while((quit = getchar()) != '\n' && quit != EOF)
        {
            if(quit == 'c') makeHexDump(true,ram);
                
            else if(quit == 'q') run = false;
        }
    }
 


    return 0;
}
