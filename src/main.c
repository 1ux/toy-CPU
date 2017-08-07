#include "toy.h"
#include "./debug/debug.h"

int main(int argc, char *argv[])
{
    uint16_t    ram[RAM_SIZE];
    uint16_t    ir;
    uint8_t     op_code;
    uint16_t    pc = 0;
    uint16_t    accu = 0;
    int         data_addr=0;
    bool        run = true;

    if(initialise_ram(ram,argc,argv)==-1) return 1;
//    makeHexDump(true,ram);

//    while(run && pc<(RAM_SIZE-1))
//    {
        ir = ram[2];
        pc++;
        op_code = get_opcode(ir);
        printf("OP Code: %u\n",op_code);
        data_addr=find_data(ir);
        printf("Adresse: %d\n",data_addr);
//    }
 



    return 0;
}
