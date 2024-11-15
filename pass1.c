#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char label[10], opcode[10], operand[10];
    char label1[10], add1[10];
    char opp[10], mn[10];
    int flg;

    FILE * sym, *op, *in, *out, *symread;
    int locctr = 0;  
    sym = fopen("sym.txt", "w");
    symread = fopen("sym.txt", "r");
    op = fopen("op.txt", "r");
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    
    fscanf(in, "%s\t%s\t%s\n", label, opcode, operand); 
    fscanf(in, "%s\t%s\t%s\n", label, opcode, operand);  

    while (strcmp("END", opcode) != 0) {
        fprintf(out, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        printf("%s\n",opcode);
        if (strcmp(label, "-") != 0) {
            //symread = fopen("sym.txt", "r");
            rewind(symread);
            
            while (fscanf(symread, "%s\t%s\n", label1, add1)!=EOF) {
                printf("%s\n",opcode);
                if (strcmp(label1, label) == 0) {
                    printf("duplicate key found");
                    return 1;
                }
            }
            fclose(symread);  // Don't forget to close the file after reading
            fprintf(sym, "%s\t%d\n", label, locctr);
            fflush(sym);
        }

        // Reset the op file pointer to the start for each new line from input file
        rewind(op);
        flg = 0;
        fscanf(op, "%s\t%s\n", opp, mn);  // Read the first line of opcode file
        while (strcmp(opp, "END") != 0) {
            
            if (strcmp(opp, opcode) == 0) {
                flg = 1;
                locctr+=3;
                break;
            }
            fscanf(op, "%s\t%s\n", opp, mn);
        }

        if (strcmp(opcode, "RESW") == 0) {
            flg = 1;
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "WORD") == 0) {
            flg = 1;
            locctr += 3;
        } else if (strcmp(opcode, "BYTE") == 0) {
            flg = 1;
            ++locctr;
        } else if (strcmp(opcode, "RESB") == 0) {
            flg = 1;
            locctr += atoi(operand);
        }

        if (!flg) {
            printf("No opcode found for: %s\n", opcode);
            return 1;
        }

        fscanf(in, "%s\t%s\t%s\n", label, opcode, operand);  // Read the next line
    }

    // Close all files after processing
    fclose(sym);
    fclose(op);
    fclose(in);
    fclose(out);

    return 0;
}
