#include "toy.h"
#include "./debug/debug.h"

#include<assert.h>

#ifndef NDEBUG
    #define DEBUG 
#endif


int main(int argc, char *argv[])
{
    uint16_t    ram[RAM_SIZE];
    uint16_t    ir=0;           //Instruction Register
    uint8_t     op_code;        //CPU Operation Code
    uint16_t    pc = 0;         //Program Counter
    int         data_addr=0;    //Adress of the 2nd operator (1. is ACCU)
    int         quit='n';       //Helper for program-flow exit (not part of CPU)
    bool        run = true;     //CPU halt and reset.(make better a coredamp befor)

    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++\n+Boot: "CPU_TYPE
    " wite %zu x %zu Bit RAM.+\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n"
    ,(sizeof(ram)/sizeof(ram[0])),sizeof(ram[0])*8);
    
    if(initialise_ram(ram,argc,argv)==-1) return 1; //load data from command line into RAM
                                                    //(-1 in case of error, 
                                                    //else number of correct read worts)

    while(run && pc<(RAM_SIZE-1))
    {
        ir = ram[pc];                       //get instruction from RAM
        op_code = get_opcode(ir);           //determine the instruction form
        data_addr=find_data(ir);            //locate the 2nd operand (ignord from OP_Code 8 to 15)

        //Handele user output
        printf("\ninstruction: ");
        fprintBits(sizeof(*ram), ram+pc,stdout);
        printf("OP Code: %"PRIu8"\t",op_code);
        printf("Adresse: %u\n",data_addr);
        printf("\ninstruction result:\n");

        //CPU control flow
        if(execute(op_code,data_addr,ram))  //EXECUTE instruction, jump if ALU says 
            pc=find_data(ram[pc]); 
        else pc++; 
        if(pc>4095) pc = pc % 4096;         //TOY can only address 12 Bit

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
