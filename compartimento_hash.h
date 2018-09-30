#ifndef COMPARTIMENTO_HASH_H
#define COMPARTIMENTO_HASH_H

#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 7

// Imprime funcionario
void createHash(int size, char *fileName){
    FILE* hashfile;
    hashfile=fopen(fileName, "w+b");
    rewind(hashfile);
    int a=-1;
    for(int i=0; i<size;i++){
        fwrite(&a, sizeof(int), 1, hashfile);
    }
    fclose(hashfile);
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
    fwrite(&pointer, sizeof(int), 1, hashFile);
}

void printHash(FILE * hashFile){
    int pointer, i = 0;
    rewind(hashFile);
    while(fread(&pointer, sizeof(int), 1, hashFile) > 0){
        printf("\n-----------------\n");
        printf("Bucket %d: pointer: %d\n",i, pointer);
        i++;
    }
}


#endif
