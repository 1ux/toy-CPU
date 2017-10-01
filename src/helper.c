#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include "toy.h"

int32_t get2compl(uint16_t value)
{
    int32_t sign_value = value;
    if(value>32767)
    {
        value=(~value)+1;
        sign_value = value*(-1);
    }
    return sign_value;
}

//assumes little endian
//stackoverflow.com/questions/111928
void fprintBits(size_t const size, void const * const ptr, FILE *file_pointer)
{
    //Beispiel:
    //printBits(sizeof(*ram), ram);
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            fprintf(file_pointer,"%u", byte);
        }
    }
    fputs("\n",file_pointer);
}

void makeHexDump(bool base_2, uint16_t ram[])
{
    time_t timer;
    struct tm *tm_timer;
    char timestamp[32];
    FILE *fp;

    time(&timer);
    tm_timer=localtime(&timer);
    if(strftime(timestamp,sizeof(timestamp),"coredump_%d_%b_%y_%T.toy",tm_timer)==0)
    {
        fprintf(stderr,"Buffer for system-time fault! hexdump canceled\n");
        return;
    }

    if(NULL==(fp=fopen(timestamp,"w")))
    {
        fprintf(stderr,"File system access failed, hexdump canceled\n");
        return;
    }
    if(base_2)
    {
        for(int i=0; i<RAM_SIZE; i++) fprintBits(sizeof(uint16_t),ram+i,fp);
    }
    else
    {
        for(int i=0; i<RAM_SIZE; i++) fprintf(fp,"%X\n",ram[i]);
    }
    fclose(fp);
}
