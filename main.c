#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcode.h"

int getInstructionCode(char *code);

int main (int argc, char** argv){
	int stack[512] = {0};
	char code[3];
	int level = 0, arg = 0, i = 0;
	
	// File name
	if(argc == 2){
		// Opening input
		FILE *input = fopen(argv[1],"r");			
		FILE *output = fopen("output.txt","w");

		if(input != NULL){
			Tinstruction *instructions = malloc(100*sizeof(Tinstruction));

			// Uploading pcode's program
			while(fscanf(input, "%s %d %d", code, &level, &arg) == 3){
				Tinstruction ins;
				ins.operation = getInstructionCode(code);
				ins.level = level;
				ins.argument = arg;
				instructions[i++] = ins;
			}

			// Running pcode machine
			fprintf(output, "%-10s %-7s %-7s %-7s %-7s %-8s %s\n","Inst","Level","Arg","Top","Counter","Base","Stack");
			pcode(instructions,stack,output);
		}else{
			printf ("\'code.txt\' not found.");
		}

		fclose(input);
		fclose(output);
	}	
	return 0;
}

int getInstructionCode(char *code){
    int i;
    char* op[8] = {"LIT","OPR","LOD","STO","CAL","INT","JMP","JPC"};
    for (i = 0; i < 8; i++){
        if(strcmp(op[i],code) == 0){
            return i;
        }
    }
    return -1;
}
