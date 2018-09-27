#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>
#include "compartimento_hash.h"

typedef struct Client {
    int clientCode;
    char name[100];
    int status; // 1 used, 0 free
    int pointer;
} Client;

int clientSize() {
    return sizeof(int)  // clientCode
    + sizeof(char) * 100 //clientName
    + sizeof(int) // status
    + sizeof(int); //pointer
}

void readClient(Client * cli, FILE *fileName){
    fread(&cli->clientCode, sizeof(int), 1, fileName);
    fread(cli->name, sizeof(char), sizeof(cli->name), fileName);
    fread(&cli->status, sizeof(int), 1, fileName);
    fread(&cli->pointer, sizeof(int), 1, fileName);
}
// If controlVar = 1 "key found", filePos = Real file Address
// If controlVar = 2  and If filePos = -1 "key not found must be added at the end of the file"
//                    and If filePos != -1 "key not found must be added in filePos"
void findClient(int clientKey, FILE *fileName, int *filePos, int *controlVar){
    Client * client = (Client*) malloc(sizeof(Client));
    
    *controlVar = 0;
    
    int j = -1; // J is the first free position of the client chain
    
    while (controlVar == 0) {
        fseek(fileName, *filePos * clientSize() , SEEK_SET);
        readClient(client, fileName);
        // if client position is free
        if(client->status == 0){
            j = *filePos;
        }
        //key found
        if(client->clientCode = clientKey && client->status == 1){
            *controlVar = 1;
        }
        else{
            // key not found
            if(client->pointer == -1){ // the end of the list
                *controlVar = 2;
                *filePos = j;
            }
            else{
                *filePos = client->pointer;
            }
        }
    }
}

void insertClient(Client *client, FILE *fileName, FILE *hashFile){
    int hash = hashFunction(client->clientCode, HASH_SIZE);
    int filePos = checkPosition(hashFile, hash);
    
    if(filePos == -1){
        fseek(fileName, 0, SEEK_END);
        fwrite(
    }
}





// Imprime funcionario
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
