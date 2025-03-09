#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "code.h"
#include "symboltable.h"
#include "parser.h"


char *dec_to_bin(int dec, char bin_buffer[17]) {
    int i = 15;
    for (;dec!=0;i--) {
        bin_buffer[i] = (char)('0' + dec%2);
        dec /= 2;
    }
    return bin_buffer;
}

char *joels_strcat(char *dest, char *src) {
    while (*dest) dest++;
    while (*dest++= *src++);
    return --dest;
}
char *fname_parse(char *input_name) {
    unsigned long len = strlen(input_name);
    char *output_name = malloc(sizeof(char)*(len+2));
    for (int i=0; i<len; i++) {
        output_name[i] = input_name[i];
        if (input_name[i]=='.') {
            output_name[i+1] = '\0';
            char *p=&output_name[i+1];
            joels_strcat(p, "hack");
            return output_name;
        }
    }
    free(output_name);
    exit(254);
}
//https://www.joelonsoftware.com/2001/12/11/back-to-basics/



int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./assembler.c [prog.asm]\n");
        return 1;
    }
    char *output_name = fname_parse(argv[1]);
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("error: could not open file %s\n", argv[1]);
    }
    FILE *outfile = fopen(output_name, "w");
    free(output_name);
    char buffer[1024];
    int command_count = 0;
    int command_type = 0;
    sym_node **table = ConstructTable();

    readline0: //first pass
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        for (int i=0; i < strlen(buffer); i++) {
            switch (buffer[i]) {
                case ' ':
                    continue;
                case '/': {
                    if (buffer[i+1]=='/'){goto readline0;}
                    break;
                }
                case '\n':
                    goto readline0;
                default: {
                    command_type = commandType(buffer[i]);
                    switch (command_type) {
                        case (C_COMMAND):
                        case (A_COMMAND): {
                            command_count++;
                            goto readline0;
                        }
                        case (L_COMMAND): {
                            char *symbol = parse_symbol(&buffer[i+1], command_type); //skip the (
                            int ROMloc = command_count;
                            AddSymbol(table,symbol,ROMloc);
                            free(symbol);
                            goto readline0;
                        }
                    }
                }
            }
        }
    }
    fseek(file, 0, SEEK_SET);

    //FILE *outfile = fopen("prog.txt", "w");
    int RAMloc = 16;
    //int line_count = 0; testing
    readline: //second pass
    char *dest_term = NULL;
    char *comp_term = NULL;
    char *jump_term = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        //line_count++; testing
        //printf("line %d\n", line_count); testing
        for (int i=0; i < strlen(buffer); i++) {
            switch (buffer[i]) {
                case ' ':
                continue;
                case '/': {
                    if (buffer[i+1]=='/'){goto readline;}
                    break;
                }
                case '\n':
                    goto readline;
                default: {
                    command_type = commandType(buffer[i]);
                    switch (command_type) {
                        case L_COMMAND: {
                            //parse_symbol();
                            //printf("lcommand\n");
                            goto readline;
                        }
                        case A_COMMAND: {
                            char bin_buffer[17] = "0000000000000000";
                            if (isdigit(buffer[i+1])) {

                                char *A_bin = dec_to_bin(atoi(&buffer[i+1]), bin_buffer);
                                fputs(A_bin, outfile);
                                fputc('\n', outfile);
                                //printf("Acommand %s: %s\n", buffer, A_bin); testing
                            }
                            else {
                                char *symbol = parse_symbol(&buffer[i+1], command_type);
                                if (ContainsSymbol(table, symbol)) {
                                    fputs(dec_to_bin(SymbolAddress(table, symbol), bin_buffer), outfile); //A_bin
                                    fputc('\n', outfile);
                                }
                                else {
                                    AddSymbol(table, symbol, RAMloc);
                                    fputs(dec_to_bin(RAMloc, bin_buffer), outfile); //A_bin
                                    fputc('\n', outfile);
                                    RAMloc++;
                                }
                                free(symbol);
                            }
                            goto readline;
                        }
                        case C_COMMAND: {
                            int dest_index=i;
                            int comp_index=strlen(buffer)-1; //last char is \n

                            for (int j=0; j<strlen(buffer); j++) {
                                if (buffer[j] == '=') {
                                    dest_index = j;
                                }
                                //due to asm syntax, if = exists it comes before ;
                                if (buffer[j] == ';') {
                                    comp_index = j;
                                    jump_term = jump(buffer, comp_index+1, strlen(buffer)-1);
                                }
                            }

                            if (dest_index == i) {comp_term = comp(buffer, dest_index, comp_index);}
                            else {
                                comp_term = comp(buffer, dest_index+1, comp_index);
                                dest_term = dest(buffer, i, dest_index); //only initialized if it exists.
                            }
                            //if no dest/= part exists, comp portion starts at i,not dest+1
                            char *temp_comp;
                            char *temp_dest;
                            char *temp_jump;
                            char C_bin[17] = "111";
                            char *p = &C_bin[3];
                            temp_comp = comp_bin(comp_term);
                            temp_dest = dest_bin(dest_term);
                            temp_jump = jump_bin(jump_term);
                            p = joels_strcat(p, temp_comp);
                            p = joels_strcat(p, temp_dest);
                            joels_strcat(p, temp_jump);
                            //printf("Ccommand %s: %s\n", buffer, C_bin); testing
                            fputs(C_bin, outfile);
                            fputc('\n', outfile);
                            if (dest_term != NULL) free(dest_term);
                            free(comp_term);
                            if (jump_term != NULL)free(jump_term);
                            goto readline;
                        }
                    }
                    //add check for invalid commands.
                }
            }
        }
    }
    free_table(table);
    fclose(file);
    fclose(outfile);
}