#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define TABLE_SIZE 47

typedef struct sym_node {
    int memloc;
    char *symbol;
    struct sym_node *next;
} sym_node;
unsigned int hash_function(const char *symbol);
sym_node **ConstructTable();
void AddSymbol(sym_node* table[], const char *symbol, int mem_loc);
bool ContainsSymbol(sym_node *table[], const char *symbol);
int SymbolAddress(sym_node *table[],const char *symbol);
int chain_lookup(sym_node **head, const char *symbol);
void chain_add(sym_node **head, const char *symbol, int mem_loc);
void node_initialize(sym_node *node);
void free_table(sym_node *table[]);
void chain_free(sym_node **head);
