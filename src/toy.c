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
    switch(op_code)
    {
        case 0: ram[data_addr]=accu; break;
        case 1: accu=ram[data_addr]; break;
//        case 2: if(!accu) break;
        case 3: accu=accu + ram[data_addr]; break;
        case 4: accu=accu - ram[data_addr]; break;
        case 5: accu=accu | ram[data_addr]; break;
        case 6: accu=accu & ram[data_addr]; break;
        case 7: accu=accu & ram[data_addr]; break;
        case 8: break;
        case 9: break;
        case 10: break;
        case 11: break;
        case 12: break;
        case 13: break;
        case 14: break;
        case 15: break;
}

