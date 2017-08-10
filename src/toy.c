#include "toy.h"

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
        fprintf(stderr,"%s","no \".toy\" input file!\n");
        return -1;
    }
    if(argc >2)
    {
        fprintf(stderr,"%s","too many input files!\n");
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

int find_data(uint16_t instruction)
{
    int instr;
    if(instruction > 32767) instr = -1;
    else instr=instruction & 4095;
    return instr;
}

bool execute(uint8_t op_code, int data_addr, uint16_t *ram) // jump when 1
{

    //vorsicht uint16 und Zweierkomplement noch nicht stringent !!!
    //Vorsicht bool ops bei sigend int typs sind undefiniert !
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
        printf("ACCU: %"PRIu16 "\n",accu);
        return jump;
}

