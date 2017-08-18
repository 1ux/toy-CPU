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
            "16 BIT Instruction Register(4 BIT OP, 12 BIT Adr)\n"
            "16 BIT Accumulator\n"
            "12 BIT Program Counter\n\n");
    printf("Example: 0001000000001010 on RAM position 0\n"
            "0001 means: LOAD the content of ADDRESS 000000001010 into the ACCU\n\n");
    printf("This is an interpreter for the Koopman_TOY_CPU by\n"
            "\tmichael.krause@uni-leipzig.de\n");
}

//gibt Anzahl der erfolgreich gelesenen Maschinenworte zurück(-1 im Fehlerfall).
int initialise_ram(uint16_t *ram, int argc, char **argv )
{

    //open Input Stream
    FILE *fp;
    int j=0;
    char tempS[CPU_WORD_SIZE+1]; //+1 for "\0"	

    for(int i=0;i<RAM_SIZE;i++) ram[i]=0;

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

    if(!(fp=fopen(argv[1],"rb")))
    {
        fprintf(stderr,"%s","open input stream fault !\n");
        return -1;
    }
    
    // initialise Toy-RAM

    do
    {
        for(int i=0;i<=CPU_WORD_SIZE;i++)
        {
            tempS[i]=fgetc(fp);
            if(tempS[0]==EOF) break;
            if(tempS[i]!='1' && tempS[i]!='0' && i<CPU_WORD_SIZE)
            {
                fprintf(stderr,"%s","input file corrupted\n");
                return -1;
            }
        }
        tempS[CPU_WORD_SIZE]='\0';
        ram[j]=strtoul(tempS,NULL,2);
        j++;
    }while(tempS[0]!=EOF);

    fclose(fp);
    return j-1;
}

uint8_t get_opcode(uint16_t instruction)
{
    uint8_t opcode;
    opcode = instruction>>12;
    return opcode;
}

uint16_t find_data(uint16_t instruction)
{
    uint16_t operand;
    operand = instruction & 4095;
    return operand;
}

int get2compl(uint16_t value)
{
    int sign_value = value;
    if(value>32767)
    {
        value=(~value)+1;
        sign_value = value*(-1);
    }    
    return sign_value;
}


bool execute(uint8_t op_code, int data_addr, uint16_t *ram) // jump if true
{
   static uint16_t accu;
   bool jump=false;

    switch(op_code)
    {
        case 0: ram[data_addr] = accu;              break; //STORE
        case 1: accu = ram[data_addr];              break; //LOAD
        case 2: jump = ((accu==0) ? true : false);  break; //JMPZ
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
        printf("ACCU: %d\n",get2compl(accu));  // not good place for it !
        return jump;
}

