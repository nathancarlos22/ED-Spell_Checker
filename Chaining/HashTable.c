#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "HashTable.h"
#include "Node.h"

//Funcão de hash djb2
unsigned int hash(char *word, int M){
    unsigned int value = 5381;//

    int i=0;
    for (i = 0; i < M; i++){
        value = value * 33  + word[i];
    }
    return value;
}
//Funcao de busca de palavra no dicionário
int chaining_word_search(char* word, struct HashTable *hash_table){

    unsigned int a = hash(word,strlen(word))%hash_table->buckets;//Hash da palavra

    struct Node *aux = (struct Node*) malloc(sizeof(struct Node));
    aux->word = (char*) malloc(sizeof(char)*(strlen(word)+1)); //criando auxiliar

    aux = hash_table->nodes[a];

    if(aux == NULL){
        return 1;
    }else{
        while(aux != NULL){
            if(strcmp(aux->word, word) == 0){
                return 0;
            }else{ //se nao achar a palavra, vai para a proxima encadeada
                aux = aux->next;
            }
        }
        return 1;
    }
}
void chaining_search(struct HashTable *table, char* path){
    FILE * stream = NULL;
    stream = fopen(path,"r");
    char * token = NULL;

    if(stream == NULL){
        printf("Nao foi possivel abrir o arquivo!!\n");
        fclose(stream);
        return;
    }else{
        unsigned int fails = 0;
        unsigned int cont = 0;//Contador de palavras do texto
        const char *s = " ()\n";//Caracteres que vou ignorar na leitura
        char line[1024];//tamanho máximo de uma linha no bloco de notas

        while(fgets(line, sizeof(line),stream) != NULL){
            token = strtok(line,s);//Transforma a linha em um array de strings
            while(token != NULL){
                ++cont;
                //printf("%s\n",token);
                //pesquisa palavra no dicionário e marca palavras erradas
                if(chaining_word_search(token,table) == 0){

                }else{
                    ++fails;
                }

                token = strtok(NULL,s);
            }
            token = NULL;
        }
        fclose(stream);

        printf("Terminou o arquivo\n");
        printf("Palavras que falharam: %i, total de palavras %i\n", fails,cont);
    }
}
//Funçã para carregar o dicionário na memoria ram
void load_hash_table(struct HashTable *table, char* path){
    FILE * stream = NULL;
    stream = fopen(path,"r");

    if(stream == NULL){
        printf("Nao foi possivel abrir o arquivo!!\n");
        fclose(stream);
        return;
    }else{
        char string[47];//46 é o tamanho da maior palavra do dicionário
        while(fscanf(stream,"%s",string)!=EOF){

            unsigned int indice = hash(string, strlen(string))%table->buckets;//hash da string e mod do hash

            struct Node * new_node = (struct Node*) malloc(sizeof(struct Node));
            new_node->word = (char*) malloc(sizeof(char)*(strlen(string)+1));

            strcpy(new_node->word,string);
            new_node->next = NULL;

            //verifica se a posição está vaiza
            if(table->nodes[indice] == NULL){
                table->nodes[indice] = new_node;
            }else{//Se não estiver vazia, encadeia
                struct Node *aux = (struct Node*) malloc(sizeof(struct Node)); //criando uma auxiliar
                aux->word = (char*) malloc(sizeof(char)*(strlen(string)+1));

                strcpy(aux->word, string);
                aux->next = table->nodes[indice]; //colocando a palavra no começo
                table->nodes[indice] = aux; //encadeando
            }
        }
        return 1;
    }
    fclose(stream);
}

//Funcao print dos elementos do dicionário
void print_hash_table(struct HashTable *hash_table){
    unsigned int i = 0;
    unsigned int cont = 0;
    unsigned int cont2 =0;
    for (i = 0; i<hash_table->buckets;i++){
        if(hash_table->nodes[i]==NULL){
            cont++;
        }else{
            cont2++;
        }
    }
    printf("Contagem nulos %i nao nulos %i  total %i\n",cont,cont2, cont+cont2);
}
