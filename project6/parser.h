#define  L_COMMAND (-93124)
#define C_COMMAND  (-93125)
#define A_COMMAND (-93126)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int commandType(char init_char);
char *parse_symbol(char *buffer, int command_type);
char * dest(char buffer[], int start, int end);
char * comp(char buffer[], int start, int end);
char * jump(char buffer[], int start, int end);