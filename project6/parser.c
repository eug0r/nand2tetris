
#include "parser.h"
int commandType(char init_char) {
    switch (init_char) {
        case '(':
            return L_COMMAND;
        case '@':
            return A_COMMAND;
        default:
            return C_COMMAND;
    }
};
char *parse_symbol(char *buffer, int command_type) {
    unsigned int len;
    char *symbol = malloc(sizeof(char)*(len = strlen(buffer)+1));
    switch (command_type) {
        case L_COMMAND: {
            for (int i = 0; i < len; i++) {
                if (buffer[i]!=')') {
                    symbol[i] = buffer[i];
                    continue;
                }
                symbol[i]='\0';
                return symbol;
            }
        }
        default: //A_COMMAND
        {
            for (int i = 0; i < len; i++) {
                if (buffer[i]!=' ' && buffer[i]!='\n') {
                    symbol[i] = buffer[i];
                    continue;
                }
                symbol[i]='\0';
                return symbol;
            }
        }
    }

};
char * dest(char buffer[], int start, int end) {
    //char temp[end - start + 1];
    char *temp = malloc(sizeof(char)*(end-start+1));
    memcpy(temp, &buffer[start], sizeof(char)*(end - start));
    temp[end - start] = '\0';

    return temp;
};
char * comp(char buffer[], int start, int end) {
    char *temp = malloc(sizeof(char)*(end-start+1));
    //memcpy(temp, &buffer[start], sizeof(char)*(end-start));
    //temp[end - start] = '\0';
    int i;
    for (i = 0; i<(end-start+1);i++) {
        if (buffer[start+i] != ' ' && buffer[start+i] != '\n' && buffer[start+i]!= ';') {
            temp[i] = buffer[start+i];
            continue;
        }
        temp[i] = '\0';
        return temp;
    }
    temp[i] = '\0';
    return temp;
};
char * jump(char buffer[], int start, int end) {
    char *temp = malloc(sizeof(char)*(end-start+1));
    //memcpy(temp, &buffer[start], sizeof(char)*(end-start));
    //temp[end - start] = '\0';
    int i;
    for (i = 0; i<(end-start+1);i++) {
        if (buffer[start+i] != ' ' && buffer[start+i] != '\n') {
            temp[i] = buffer[start+i];
            continue;
        }
        temp[i] = '\0';
        return temp;
    }
    temp[i] = '\0';
    return temp;
};