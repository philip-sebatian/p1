#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    FILE * symread, *symwrite, *opp, *out, *in;
    symread = fopen("sym.txt","r");
    symwrite = fopen("sym.txt","w");
    opp = fopen("op.txt","r");
    out = fopen("output.txt","w");
    in = fopen("input.txt","r");
    char label[10],operand[10],oppcode[10];
    char label1[10],operand1[10];
    char opval[10],opadd[10];

    int locctr=0;

    fscanf(in,"%s\t%s\t%s\n",label,oppcode, operand);
    if(strcmp(oppcode,"START")==0){
        locctr=atoi(operand);
    }
    fscanf(in,"%s\t%s\t%s\n",label,oppcode, operand);
    printf("%d%s",locctr,oppcode);
    while(strcmp(oppcode,"END")!=0){
        fprintf(out,"%d\t%s\t%s\t%s\n",locctr,label,oppcode,operand);
        printf("%s\n",oppcode);
        if(strcmp("-", label)!=0){
            rewind(symread);
            while(fscanf(symread,"%s\t%s\n",label1,operand1)!=EOF){
                if(strcmp(label1,label)==0){
                    printf("duplicate");
                    return;
                }
            }
            fprintf(symwrite,"%s\t%d\n",label,locctr);
            fflush(symwrite);
        }

        rewind(opp);
        while(fscanf(opp,"%s\t%s\n",opval,opadd)!=EOF){
            if(strcmp(opval,oppcode)==0){
                locctr+=3;
                break;
            }
        }
        if(strcmp(oppcode,"RESW")==0){
            locctr+=3*atoi(operand);
        }
        else if(strcmp(oppcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(oppcode, "RESB")==0){
            locctr+=atoi(operand)*1;
        }
        else if(strcmp(oppcode,"BYTE")==0){
            locctr+=1;
        }
    fscanf(in,"%s\t%s\t%s\n",label,oppcode, operand);
        
    }
    fclose(symwrite);
}