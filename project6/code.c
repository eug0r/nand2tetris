#include "code.h"


char *dest_bin(char *dest_term) {
    if (dest_term == NULL) {return "000";}
    if (!strcmp(dest_term, "M")) return "001";
    if (!strcmp(dest_term, "D")) return "010";
    if (!strcmp(dest_term, "A")) return "100";
    if (!strcmp(dest_term, "DM")) return "011";
    if (!strcmp(dest_term, "MD")) return "011";
    if (!strcmp(dest_term, "AM")) return "101";
    if (!strcmp(dest_term, "AD")) return "110";
    if (!strcmp(dest_term, "ADM")) return "111";
    if (!strcmp(dest_term, "AMD")) return "111";
}
char *comp_bin(char *comp_term) {
    if (!strcmp(comp_term, "0")) return "0101010";
    if (!strcmp(comp_term, "1")) return "0111111";
    if (!strcmp(comp_term, "-1")) return "0111010";
    if (!strcmp(comp_term, "D")) return "0001100";
    if (!strcmp(comp_term, "A")) return "0110000";
    if (!strcmp(comp_term, "!D")) return "0001101";
    if (!strcmp(comp_term, "!A")) return "0110001";
    if (!strcmp(comp_term, "-D")) return "0001111";
    if (!strcmp(comp_term, "-A")) return "0110011";
    if (!strcmp(comp_term, "D+1")) return "0011111";
    if (!strcmp(comp_term, "A+1")) return "0110111";
    if (!strcmp(comp_term, "D-1")) return "0001110";
    if (!strcmp(comp_term, "A-1")) return "0110010";
    if (!strcmp(comp_term, "D+A")) return "0000010";
    if (!strcmp(comp_term, "D-A")) return "0010011";
    if (!strcmp(comp_term, "A-D")) return "0000111";
    if (!strcmp(comp_term, "D&A")) return "0000000";
    if (!strcmp(comp_term, "D|A")) return "0010101";

    if (!strcmp(comp_term, "M")) return "1110000";
    if (!strcmp(comp_term, "!M")) return "1110001";
    if (!strcmp(comp_term, "-M")) return "1110011";
    if (!strcmp(comp_term, "M+1")) return "1110111";
    if (!strcmp(comp_term, "M-1")) return "1110010";
    if (!strcmp(comp_term, "D+M")) return "1000010";
    if (!strcmp(comp_term, "D-M")) return "1010011";
    if (!strcmp(comp_term, "M-D")) return "1000111";
    if (!strcmp(comp_term, "D&M")) return "1000000";
    if (!strcmp(comp_term, "D|M")) return "1010101";


}
char *jump_bin(char *jump_term) {
    if (jump_term == NULL){return "000";}
    if (!strcmp(jump_term, "JGT")) return  "001";
    if (!strcmp(jump_term, "JEQ")) return  "010";
    if (!strcmp(jump_term, "JGE")) return  "011";
    if (!strcmp(jump_term, "JLT")) return  "100";
    if (!strcmp(jump_term, "JNE")) return  "101";
    if (!strcmp(jump_term, "JLE")) return  "110";
    if (!strcmp(jump_term, "JMP")) return  "111";
    else exit(-1);
}
