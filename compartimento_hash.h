#ifndef COMPARTIMENTO_HASH_H
#define COMPARTIMENTO_HASH_H

#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 7

// Imprime funcionario
void createHash(int size, FILE *fileName){
    FILE* fileName;
    fileName=fopen("tabHash.h", "w+b");
    rewind(fileName);
    int a=-1;
    for(int i=0; i<size;i++){
        fwrite(&a, sizeof(int), 1, fileName);
    }
    fclose(fileName);
}

int hashFunction(int clientKey, int hashSize){
    return clientKey % hashSize;
}

int checkPosition(FILE * fileName, int hashPos){
    fseek(fileName, hashPos * sizeof(int), SEEK_SET);
    int readItem;
    fread(&readItem, sizeof(int), 1, fileName);

    return readItem;
}

void insertPointer(FILE *hashFile, int pointer, int bucket){
    fseek(hashFile, bucket, SEEK_SET);
    fwrite(&pointer, sizeof(int), 1, fileName);
}

void print(Client * cc);

// Cria funcionario. Lembrar de usar free(funcionario)
Client *client(int clientCode, char *name);

// Salva funcionario no arquivo out, na posicao atual do cursor
void save(Client *cli, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Client *read(FILE *in);

// Retorna tamanho do funcionario em bytes
int size();

#endif
