#ifndef HASHTABLE.H
#define HASHTABLE.H

#include<stdio.h>
#include<stdlib.h>
#include "Node.h"
#define MAX_BUCKETS 500000

struct HashTable{
    struct Node * nodes[MAX_BUCKETS]; /*Total de palavras do arquivo ascii  307855*/
    unsigned int buckets;
    unsigned int words;
};
#endif
