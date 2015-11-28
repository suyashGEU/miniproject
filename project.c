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

        int i;
        for(i=0;i<symtab_size;i++)
        {
        if(strcmp(operand,symtab[i].label_name)==0)
        {
            return(symtab[i].opcode);
            break;
        }

    }
    return(0);
}
hexascii(char b[10000],char a)
{
    int x=(int)(a);
    char val[20];
    val[0]='\0';
    itoa(x,val,16);
    strcat(b,val);
}

unsigned long convtodecno(char hex[])
{
    char *hexstring;
    int length = 0;
    const int base = 16;
    unsigned long decno = 0;
    int i;
    for (hexstring = hex; *hexstring != '\0'; hexstring++)
    {
        length++;
    }
    hexstring = hex;
    for (i = 0; *hexstring != '\0' && i < length; i++, hexstring++)
    {
        if (*hexstring >= 48 && *hexstring <= 57)
        {
            decno += (((int)(*hexstring)) - 48) * pow(base, length - i - 1);
        }
        else if ((*hexstring >= 65 && *hexstring <= 70))
        {
            decno += (((int)(*hexstring)) - 55) * pow(base, length - i - 1);
        }
        else if (*hexstring >= 97 && *hexstring <= 102)
        {
            decno += (((int)(*hexstring)) - 87) * pow(base, length - i - 1);
        }
        else
        {
            printf(" Invalid Hexadecimal Number \n");

        }
    }
    return decno;
}
chk_byte_length(char operand[15],int *loccount)
{
    int flag=0,i;
    int operand_Size=strlen(operand);
    if(operand[0]=='c')
    {
        (*loccount)=(*loccount)+(operand_Size-3);
    }
    if(operand[0]=='x')
    {
        for(i=2;operand[i]!='\0';i++)
        {
            flag++;
        }
        (*loccount)=(*loccount)+(flag/2);
    }
}
chk_label(char label[15],int *p,int loccount)
{
    int temp,i;
    temp=(*p);
    for(i=0;i<temp;i++)
    {
        if(strcmp(symtab[i].label_name,label)==0)
            {
                printf("symbol table..error.....label ambiguity generated");
                exit(0);
            }
    }
    (*p)=(*p)+1;
    strcpy(symtab[temp].label_name,label);
    symtab[temp].opcode=loccount;
}
chk_opcode(char opcode[15],int *loccount,char operand[15])
{
    int i,operand_value,flag;
    for(i=0;i<5;i++)
    {
        if(strcmp(opcode,optab[i].mnemonics)==0)
            flag=1;
    }
    if(flag!=1)
    {
        if(strcmp(opcode,"WORD")==0)
            (*loccount)=(*loccount)+3;
        else if(strcmp(opcode,"RESW")==0)
        {
            operand_value=atoi(operand);
            (*loccount)=(*loccount)+(3*operand_value);
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            operand_value=atoi(operand);
            (*loccount)=(*loccount)+operand_value;
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            chk_byte_length(operand,loccount);
        }
        else
        {
            printf("ERROR:\n");
            printf("mnemonics can not be found in the operation table.\n");
            printf("Input the valid mnemonics\n");
            exit(0);
        }
    }
    else
    {
        (*loccount)=(*loccount)+3;
    }
}
int main()
{
    FILE *input,*inter,*output;
    char label[15],opcode[15],operand[15],current_address[15],addr[15],record[10000],byte_value[50],text_value[50],opcode_value[50];
    int startaddr=0,loccount=0,program_length,symtab_size=0,i,j,text_length,byte_length,value;
    input=fopen("input.txt","r");
    inter=fopen("inter.txt","w");
    fscanf(input,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        startaddr=convtodecno(operand);
        loccount=startaddr;
        printf("*\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(label,"*")!=0)
        {
            chk_label(label,&symtab_size,loccount);
        }
        printf("%x\t%s\t%s\t%s\n",loccount,label,opcode,operand);
        fprintf(inter,"%x\t%s\t%s\t%s\n",loccount,label,opcode,operand);
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode(opcode,&loccount,operand);
        }
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    printf("*\t%s\t%s\t%s\n",label,opcode,operand);
    fprintf(inter,"*\t%s\t%s\t%s\n",label,opcode,operand);
    program_length=loccount-startaddr;
    printf("\nprogram length is ==%x\n\n",program_length);
    fclose(input);
    fclose(inter);
    printf("........................pass 2.......................................\n\n");
    output=fopen("output.txt","w");
    inter=fopen("inter.txt","r");
    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        printf("H^%s^00%s^0000%x\n",label,operand,program_length);
        fprintf(output,"H^%s^00%s^0000%x\n",label,operand,program_length);
        fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
        {
            strcpy(addr,current_address);
            text_length=0;
            record[0]=0;

            while((text_length<30)&&(strcmp(opcode,"END")!=0))
            {

                int y=s_opcode(opcode);
                if(y!=0)
                {

                    text_length+=3;

                    strcat(record,"^");

                   strcat(record,optab[y].opcode);
                    if(strcmp(operand,"*")!=0)
                    {

                        value=s_operand(operand,symtab_size);
                        itoa(value,text_value,16);

                        strcat(record,text_value);

                    }
                    else
                    {

                        strcat(record,"0000");

                    }



                }

                if(strcmp(opcode,"WORD")==0)
                {

                    text_length+=3;
                    strcat(record,"^");
                    strcat(record,"00000");
                    strcat(record,operand);

                }
                if(strcmp(opcode,"BYTE")==0)
                {

                    byte_length=strlen(operand);

                    byte_value[0]=0;

                    if(operand[0]=='c')
                    {

                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {

                            byte_value[j]=operand[i];

                        }
                        byte_value[j]='\0';
                        text_length+=(j);

                        strcat(record,"^");
                        for(i=0;i<strlen(byte_value);i++)
                        {
                            hexascii(record,byte_value[i]);
                        }

                    }
                    if(operand[0]=='x')
                    {
                        for(i=2,j=0;i<byte_length-1;i++,j++)
                        {
                            byte_value[j]=operand[i];
                        }
                        text_length+=(j/2);
                        strcat(record,"^");
                        strcat(record,byte_value);
                    }

                }
               if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
                {
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
                    break;
                }
                    fscanf(inter,"%s%s%s%s",current_address,label,opcode,operand);
            }
        printf("T^00%s^%x%s\n",addr,text_length,record);
        fprintf(output,"T^00%s^%02x%s\n",addr,text_length,record);
        }

        printf("E^00%x\n",startaddr);
        fprintf(output,"E^00%x\n",startaddr);
        fclose(inter);
        fclose(output);
        printf("SYMBOL TABLE OF THE ABOVE PROGRAM IS :\n\n\n");
        for(i=0;i<symtab_size;i++)
        {
            printf("%s\t%x\n",symtab[i].label_name,symtab[i].opcode);
        }
        printf("\t\t\t\t\t\t\t\t\t Submitted by: SUYASH KANDARI  5th SEM");
    return(0);


}
