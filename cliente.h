#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>
#include "compartimento_hash.h"

#define HASH_SIZE 7


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

int readClient(Client * cli, FILE *fileName){
    return (fread(&cli->clientCode, sizeof(int), 1, fileName) &&
    fread(cli->name, sizeof(char), sizeof(cli->name), fileName) &&
    fread(&cli->status, sizeof(int), 1, fileName) &&
    fread(&cli->pointer, sizeof(int), 1, fileName));

}

void writeClient(Client *cli, FILE *fileName, int filePos, int size){
    fseek(fileName, filePos * size, SEEK_SET);
    fwrite(&cli->clientCode, sizeof(int), 1, fileName);
    fwrite(cli->name, sizeof(char), sizeof(cli->name), fileName);
    fwrite(&cli->status, sizeof(int), 1, fileName);
    fwrite(&cli->pointer, sizeof(int), 1, fileName);
}
// If controlVar = 1 "key found", filePos = Real file Address
// If controlVar = 2  key not found, filePos is the last client of the chain
void findClient(int clientKey, FILE *fileName, int *filePos, int *controlVar){
    Client * client = (Client*) malloc(sizeof(Client));
    printf("hahahahah\n" );
    *controlVar = 0;
    printf("parei no control var\n" );
    int j = -1; // J is the first free position of the client chain

    while (*controlVar == 0) {
        printf("fseek deu pau\n" );
        fseek(fileName, *filePos * clientSize() , SEEK_SET);
        printf("fseek\n" );
        readClient(client, fileName);
        printf("readcliente\n");
        printf("%d\n",client->clientCode );
        printf("%s\n",client->name );
        if(client->status != 1 ){
            printf("Error: Inactive client is still in the list\n" );
            exit(1);
        }
        if(client->clientCode == clientKey){
            *controlVar = 1;
            break;
        }
        else if(client->clientCode != clientKey && client->pointer != -1){
            *filePos = client->pointer;

        }
        else if(client->pointer == -1){
            *controlVar = 2;
        }

    }
}
/*This function searches for the first free line.
  The free line can be an unused line or an used line with a free status flag. */
int findFreeLine(FILE *fileName, int structure_size){
    Client * client = (Client*) malloc(sizeof(Client));
    rewind(fileName);
    int fileIterator = 0;
    int j = 0;
    while(1){
        fileIterator = j * structure_size;
        // if it happen, it's the end of the file. (no written line)
        if(!readClient(client, fileName)){
            fileIterator = -1;
            break;
        }

        // found a free client. Line must be overwritten
        if(client->status == 0){
            break;
        }
        j++;

    }
    // Return the free position.
    return fileIterator;

}


void insertClient(Client *client, FILE *fileName, FILE *hashFile){
    rewind(fileName);
    int hash;
    hash = hashFunction(client->clientCode, HASH_SIZE);
    int filePos;
    filePos = checkPosition(hashFile, hash);
    int insertControl = 0;
    int *controlVar = 0;
    Client * previousClient = (Client*) malloc(sizeof(Client));
    int previousClientPos;

    // CheckPosition returns -1 when hash position is free.
    // We must find a free position in the client.dat file in order to add another client.
    // if filePos == -1, it means that the client isnt in the hash tabler neither in the client.dat
    if(filePos == -1){
        printf("teste\n" );
        filePos = findFreeLine(fileName, clientSize()) / clientSize();
        printf("%d\n", filePos);
        writeClient(client, fileName, filePos, clientSize());
        insertPointer(hashFile, filePos, hash *sizeof(int));
    }
    else{
        findClient(client->clientCode, fileName, &filePos, controlVar);
        if(*controlVar == 1){
            printf("Dumb user!. Client already inserted\n" );
        }
        else{
            previousClientPos = filePos;
            filePos = findFreeLine(fileName, clientSize()) / clientSize();
            // Changing previousClient pointer.
            fseek(fileName, (previousClientPos * clientSize()) + clientSize() - sizeof(int), SEEK_SET);
            fwrite(&filePos, sizeof(int), 1, fileName);
            //Writing new client
            fseek(fileName, filePos * clientSize(), SEEK_SET);
            writeClient(client, fileName, filePos, clientSize());
        }
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
