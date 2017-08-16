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

    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++\n+Boot: "CPU_TYPE
    " wite %zu x %zu Bit RAM.+\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n"
    ,(sizeof(ram)/sizeof(ram[0])),sizeof(ram[0])*8);
    
    if(initialise_ram(ram,argc,argv)==-1) return 1;

    while(run && pc<(RAM_SIZE-1))
    {
        ir = ram[pc];
        op_code = get_opcode(ir);
        data_addr=find_data(ir);

        //Handele user output
        printf("\ninstruction: ");
        fprintBits(sizeof(*ram), ram+pc,stdout);
        printf("OP Code: %"PRIu8"\t",op_code);
        printf("Adresse: %u\n",data_addr);
        printf("\ninstruction result:\n");
        //CPU control flow
        if(execute(op_code,data_addr,ram)) //jump if ALU says 
            pc=find_data(ram[pc]); 
        else pc++;

        //Handele user output
        printf("PROGRAM COUNTER: %" PRIu16 "\n",pc);
        printf("\x1b[32m \n(n)ext step or (q)uit or (c)oredump ?\n \x1b[0m");

        //handel program flow
        while((quit = getchar()) != '\n' && quit != EOF)
        {
            if(quit == 'c') makeHexDump(true,ram);
                
            else if(quit == 'q') run = false;
        }
    }
    return 0;
}
