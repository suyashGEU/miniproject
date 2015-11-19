#include<stdio.h>
#include<string.h>
#include<math.h>
struct op_tab
{
    char mnemonics[15];
    char opcode[15];
}optab[5]={   {"LDA","05"},
                {"JMP","01"},
                {"STA","02"},
                {"LDCH","03"},
                {"STCH","04"},
            };
struct sym_table
{   char label_name[15];
    int opcode;
}symtab[100];
int s_opcode(char opcode[15])
{
    int i;
    for(i=0;i<5;i++)
    {
        if(strcmp(opcode,optab[i].mnemonics)==0)
        {

            return(i);
            break;
        }

    }

    return(0);
}
int s_operand(char operand[15],int symtab_size)
{
            return(symtab[i].opcode);
            break;
        int i;
        for(i=0;i<symtab_size;i++)
        {
        if(strcmp(operand,symtab[i].label_name)==0)
        {
        }

    }
    return(0);
}
