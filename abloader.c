#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    FILE *f1,*f2;
    int i , j ;
    f1 = fopen("inp.txt","r");
    f2 = fopen("out.txt","w");
    char line[50],strtadd[50],buffer[50];
    fscanf(f1,"%s", line);
    fscanf(f1,"%s", line);
    while(line[0]!='E'){
        
        for(i=0,j=2;i<6,j<8;i++,j++){
            strtadd[i]=line[j];
        }
        strtadd[i]='\0';
        
        int add= atoi(strtadd);
        j=12;
        while (line[j] != '$' && j < strlen(line)) {
    if (line[j] != '^' && j + 1 < strlen(line)) { // Ensure j+1 is valid
        buffer[0] = line[j];
        buffer[1] = line[j+1];
        buffer[2] = '\0'; // Null-terminate to make it a valid string
        j += 2;
        printf("%d\t%s\n", add, buffer);
        fprintf(f2, "%d\t%s\n", add, buffer);
        fflush(f2);
        add++;
    } else if (line[j] == '^') {
        j++;
    } else {
        break; // Exit safely if j exceeds bounds.
    }
}
        fscanf(f1,"%s", line);
    }
}