#include "symboltable.h"


unsigned int hash_function(const char *symbol){
    if (symbol==NULL){exit(0);}
    unsigned int hash = 0;
    unsigned int len;
    hash+= len = strlen(symbol);
    hash *= symbol[0];
    hash *= symbol[len-1];
    return hash%TABLE_SIZE;
}

//struct sym_node *head;
sym_node **ConstructTable() {
    sym_node **hash_table = malloc(sizeof(sym_node*)*TABLE_SIZE);
    if (hash_table==NULL)exit(-1);

    for (int i = 0; i<TABLE_SIZE;i++) {
        hash_table[i] = NULL;
    }
    AddSymbol(hash_table,"SP", 0);
    AddSymbol(hash_table,"LCL", 1);
    AddSymbol(hash_table,"ARG", 2);
    AddSymbol(hash_table,"THIS", 3);
    AddSymbol(hash_table,"THAT", 4);
    AddSymbol(hash_table,"R0", 0);
    AddSymbol(hash_table,"R1", 1);
    AddSymbol(hash_table,"R2", 2);
    AddSymbol(hash_table,"R3", 3);
    AddSymbol(hash_table,"R4", 4);
    AddSymbol(hash_table,"R5", 5);
    AddSymbol(hash_table,"R6", 6);
    AddSymbol(hash_table,"R7", 7);
    AddSymbol(hash_table,"R8", 8);
    AddSymbol(hash_table,"R9", 9);
    AddSymbol(hash_table,"R10", 10);
    AddSymbol(hash_table,"R11", 11);
    AddSymbol(hash_table,"R12", 12);
    AddSymbol(hash_table,"R13", 13);
    AddSymbol(hash_table,"R14", 14);
    AddSymbol(hash_table,"R15", 15);
    AddSymbol(hash_table,"SCREEN", 16384);
    AddSymbol(hash_table,"KBD", 24576);
    return hash_table;
}
void AddSymbol(sym_node *table[], const char *symbol, int mem_loc) {
    //ContainsSymbol(table, symbol);
    unsigned int hash = hash_function((symbol));
    if (table[hash] == NULL) {
        table[hash] = malloc(sizeof(sym_node));
        node_initialize(table[hash]);
        table[hash]->memloc=mem_loc;
        table[hash]->symbol = malloc(sizeof(char)*(strlen(symbol)+1));
        strcpy(table[hash]->symbol,symbol);
    }
    else {
        chain_add(&table[hash], symbol, mem_loc);
    }
}
bool ContainsSymbol(sym_node *table[],const char *symbol) {
    unsigned int hash = hash_function((symbol));
    if (table[hash] == NULL) {
        return false;
    }
    else {
        if (chain_lookup(&table[hash], symbol)==-1) return false;
        else return true;
    }
}
int SymbolAddress(sym_node *table[],const char *symbol) {
    unsigned int hash = hash_function((symbol));
    return chain_lookup(&table[hash], symbol);
    //this doubles the lookups, gotta optimize it
}
int chain_lookup(sym_node **head, const char *symbol) {
    sym_node *current = *head;
    while (current!=NULL) {
        if (!(strcmp(current->symbol,symbol))) {
            return current->memloc;
        }
        current=current->next;
    }
    return -1;
}//lookup down the linked-list.

void chain_add(sym_node **head, const char *symbol, int mem_loc) {
    sym_node *current = *head;
    while (current->next!=NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(sym_node));
    current = current->next;
    node_initialize(current);
    current->memloc = mem_loc;
    current->symbol = malloc(sizeof(char)*(strlen(symbol)+1));
    strcpy(current->symbol, symbol);
    current->next = NULL;
}//add to linked-list

void node_initialize(sym_node *node) {
    node->memloc = -1;
    node->symbol = NULL;
    node->next = NULL;
}

void free_table(sym_node *table[]) {
    //int filled=0; testing
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i]!=NULL) {
            //printf("no of filled entries: %d\n",++filled); testing
            chain_free(&table[i]);
            free(table[i]->symbol);
            free(table[i]); //terrible implementation
        }
    }
    free(table);
}
void chain_free(sym_node **head) {
    sym_node *current = (*head)->next;
    //int chain_length=0; testing
    while (current != NULL) {
        sym_node *tmp = current;
        current = current->next;
        free(tmp->symbol);
        free(tmp);
        //chain_length++; testing
    }
    //printf("chain length: %d\n", ++chain_length); testing
}