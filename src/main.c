#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "toy.h"
#include "helper.h"

#include <assert.h>

#ifndef NDEBUG
    #define DEBUG
#endif


int main(int argc, char *argv[])
{
    uint16_t    ram[RAM_SIZE];
    uint16_t    ir=0;           //Instruction Register
    uint8_t     op_code;        //CPU Operation Code
    uint16_t    pc = 0;         //Program Counter
    uint16_t    data_addr=0;    //Adress of the 2nd operand (1. is ACCU)
    int         quit='n';       //Helper for program-flow exit (not part of CPU)
    bool        run = true;     //CPU halt and reset.(make better a coredamp befor)

    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++\n+Boot: "CPU_TYPE
    " with %zu x %zu Bit RAM.+\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n"
    ,(sizeof(ram)/sizeof(ram[0])),sizeof(ram[0])*8);

    if(initialise_ram(ram,argc,argv)==-1) return 1;     /*load data from command line into RAM
                                                        (-1 in case of error,
                                                        else number of correct read worts)*/
    while(run)
    {
        ir = ram[pc];        				//get instruction from RAM
        op_code = get_opcode(ir);			//determine the instruction form
        data_addr=get_data(ir);				/*locate the 2nd operand
                                                        (ignord from OP_Code 8 to 15)*/
        //handle user output
        printf("\ninstruction:\t");
        fprintBits(sizeof(*ram), ram+pc,stdout);
        printf("OP CODE: %"PRIu8"\tmeans: ",op_code);
        print_instruction(op_code);
        printf("address: %"PRIu16"\tcontent:%"
                PRIu16"\n",data_addr,ram[data_addr]);
        printf("RAM position:\t%"PRIu16"\n",pc);
        printf("\ninstruction result:\n");

        //CPU control flow
        if(execute(op_code,data_addr,ram))              //EXECUTE instruction, jump if ALU says
            pc=get_data(ir);
        else pc++;

        if(pc>=RAM_SIZE) pc %= RAM_SIZE;	        //TOY_CPU can only address 12 Bit

        //handle user output
        printf("ACCU: %d\n",get2compl(*ACCU));
        printf("PROGRAM COUNTER: %" PRIu16
                "\n-----------------------------------",pc);
        printf("\n(n)ext step or (q)uit or (c)oredump ?\n");

        //handle program flow
        while((quit = getchar()) != '\n')
        {
			switch(quit)
			{
				case EOF: break;
				case 'c': makeHexDump(true,ram); break;
				case 'q': run = false;
			}
        }
    }
    return 0;
}
