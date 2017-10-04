#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "toy.h"

void print_instructionSet(void)
{
    printf("interpretation terminated.\n");
    printf("TOY-CPU Instruction Set:\n\n");
    printf("OP_Code 0 (0000b):\t   STORE<12 BIT ADDRESS>\n");
    printf("OP_Code 1 (0001b):\t   LOAD\t<12 BIT ADDRESS>\n");
    printf("OP_Code 2 (0010b):\t   JMPZ\t<12 BIT ADDRESS>\n");
    printf("OP_Code 3 (0011b):\t   ADD\t<12 BIT ADDRESS>\n");
    printf("OP_Code 4 (0100b):\t   SUB\t<12 BIT ADDRESS>\n");
    printf("OP_Code 5 (0101b):\t   OR\t<12 BIT ADDRESS>\n");
    printf("OP_Code 6 (0110b):\t   AND\t<12 BIT ADDRESS>\n");
    printf("OP_Code 7 (0111b):\t   XOR\t<12 BIT ADDRESS>\n");
    printf("OP_Code 8 (1000b):\t   NOT\t<12 BIT undefined>\n");
    printf("OP_Code 9 (1001b):\t   INC\t<12 BIT undefined>\n");
    printf("OP_Code 10 (1010b):\t   DEC\t<12 BIT undefined>\n");
    printf("OP_Code 11 (1011b):\t   ZERO\t<12 BIT undefined>\n");
    printf("OP_Code 12 (1100b):\t   NOP\t<12 BIT undefined>\n");
    printf("OP_Code 13 (1101b):\t   NOP\t<12 BIT undefined>\n");
    printf("OP_Code 14 (1110b):\t   NOP\t<12 BIT undefined>\n");
    printf("OP_Code 15 (1111b):\t   NOP\t<12 BIT undefined>\n\n");

    printf("BIT\t|15 14 13 12|11 10 9 8 7 6 5 4 3 2 1 0|\n"
            "\t---------------------------------------\n"
            "\t|  OP-CODE  |\t\tADDRESS\t      |\n"
            "\t---------------------------------------\n\n");
    printf("This machine has the following registers:\n"
            "16 BIT Instruction Register(4 BIT OP, 12 BIT Addr)\n"
            "16 BIT Accumulator\n"
            "12 BIT Program Counter\n\n");
    printf("Example: 0001000000001010 at RAM position 0\n"
            "0001 means: LOAD the content of ADDRESS 000000001010 into the ACCU\n\n");
    printf("This is an interpreter for the Koopman_TOY_CPU by\n"
            "\tmichael.krause@uni-leipzig.de\n");
}

void print_instruction(uint8_t opcode)
{
    opcode%=16;
    switch(opcode)
    {
        case 0: printf("STORE\n");  break;
        case 1: printf("LOAD\n");   break;
	case 2: printf("JMP\n");    break;
        case 3: printf("ADD\n");    break;
        case 4: printf("SUB\n");    break;
        case 5: printf("OR\n");     break;
        case 6: printf("AND\n");    break;
        case 7: printf("XOR\n");    break;
        case 8: printf("NOT\n");    break;
        case 9: printf("INC\n");    break;
        case 10: printf("DEC\n");   break;
        case 11: printf("ZERO\n");  break;
        case 12: printf("NOP\n");   break;
        case 13: printf("NOP\n");   break;
        case 14: printf("NOP\n");   break;
        case 15: printf("NOP\n");   break;
    }
}

int initialise_ram(uint16_t *ram, int argc, char **argv )
{

    //opens and checks the input stream
    FILE *fp;
    int int_cache=0;
    size_t j=0;
    char tempS[CPU_WORD_SIZE+1]; //+1 for "\0

    for(size_t i=0;i<RAM_SIZE;i++) ram[i]=0;	//initialise the toy-RAM with NULL

    if(argc<2)
    {
        fprintf(stderr,"%s","no \".toy\" input file!\n"
                "interpretation terminated. (press -h for help)\n");
        return -1;
    }
    if(argc >2)
    {
        fprintf(stderr,"%s","too many input files!\n");
        return -1;
    }

    if(strcmp(argv[1],"-h")==0)
    {
      print_instructionSet();
      return -1;
    }

    if(NULL==(fp=fopen(argv[1],"r")))
    {
        fprintf(stderr,"%s","open input stream error !\n");
        return -1;
    }

	// Fill the toy-RAM with data and break in case of error
	for(;;)
	{
		for(int i = 0;i <= CPU_WORD_SIZE;i++)
		{
			int_cache = fgetc(fp);

			if((int_cache =='\n' && i<CPU_WORD_SIZE) || (feof(fp) && i!=0))
			{
				fprintf(stderr,"%s","input file has word length error(s) !\n");
				fclose(fp);
				return -1;
			}

			if(feof(fp)) break;

			if((int_cache != '1' && int_cache != '0' && int_cache != '\n') || j >= RAM_SIZE )
			{
				fprintf(stderr,"%s","input file corrupted\n");
				fclose(fp);
				return -1;
			}
			tempS[i] = int_cache;
		}
		if(feof(fp)) break;
		tempS[CPU_WORD_SIZE] = '\0'; 		//replace \n with \0
		ram[j] = strtoul(tempS,NULL,2);
		j++;
	}
    fclose(fp);
    return j;
}

uint8_t get_opcode(uint16_t instruction)
{
    uint8_t opcode;
    opcode = instruction>>12;
    return opcode;
}

uint16_t get_data(uint16_t instruction)
{
    uint16_t operand;
    operand = instruction & 4095;
    return operand;
}

static uint16_t accu;
const uint16_t * const ACCU = &accu;

bool execute(uint8_t op_code, int data_addr, uint16_t *ram) // jump if true
{
   bool jump=false;

    switch(op_code)
    {
        case 0: ram[data_addr] = accu;              break; //STORE
        case 1: accu = ram[data_addr];              break; //LOAD
	case 2: jump = (accu == 0);		    break; //JMP
        case 3: accu = accu + ram[data_addr];       break; //ADD
        case 4: accu = accu - ram[data_addr];       break; //SUB
        case 5: accu = accu | ram[data_addr];       break; //OR
        case 6: accu = accu & ram[data_addr];       break; //AND
        case 7: accu = accu ^ ram[data_addr];       break; //XOR
        case 8: accu = ~accu;                       break; //NOT
        case 9: accu++;                             break; //INC
        case 10: accu--;                            break; //DEC
        case 11: accu = 0;                          break; //ZERO
        case 12: ;                                  break; //NOP
        case 13: ;                                  break; //NOP
        case 14: ;                                  break; //NOP
        case 15: ;                                  break; //NOP
    }
    return jump;
}

