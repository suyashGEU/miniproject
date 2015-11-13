#include<stdio.h>
 #include<string.h>
void chk_label();
 void chk_opcode();
 void READ_LINE();
struct optab
 {
     char   code[10],objcode[10];
 }myoptab[3]={
                    {"LDA","00"},
                    {"JMP","01"},
                    {"STA","02"}
              };


 struct symtab{
                     char symbol[10];
                     int addr;
               }mysymtab[10];

 int startaddr,locctr,symcount=0,length;
 char line[20],label[8],opcode[8],operand[8],programname[10];

