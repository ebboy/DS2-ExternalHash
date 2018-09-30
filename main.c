#include <stdio.h>
#include <stdlib.h>
#include "compartimento_hash.h"
#include "cliente.h"
#include "string.h"


int main(int argc, char const *argv[]) {
    createHash(HASH_SIZE, "hashteste.dat");
    FILE * hash = fopen("hashteste.dat", "r+b");
    FILE * clienteFile = fopen("clienteTeste.dat", "w+b");

    Client * teste1 = (Client*) malloc(sizeof(Client));
    teste1->clientCode = 1;
    strcpy(teste1->name,"joaoalbino");
    teste1->pointer = -1;
    teste1->status = 1;

    Client * teste2 = (Client*) malloc(sizeof(Client));
    teste2->clientCode = 1;
    strcpy(teste2->name,"joaoalbino2");
    teste2->pointer = -1;
    teste2->status = 1;

    Client * teste3 = (Client*) malloc(sizeof(Client));
    teste3->clientCode = 5;
    strcpy(teste3->name,"joaoalbino3");
    teste3->pointer = -1;
    teste3->status = 1;

    Client * teste4 = (Client*) malloc(sizeof(Client));
    teste4->clientCode = 12;
    strcpy(teste4->name,"joaoalbino4COLISAO");
    teste4->pointer = -1;
    teste4->status = 1;

    insertClient(teste1, clienteFile, hash);
    insertClient(teste2, clienteFile, hash);
    insertClient(teste3, clienteFile, hash);
    insertClient(teste4, clienteFile, hash);

    rewind(clienteFile);

    printClients(clienteFile);


    fclose(hash);
    fclose(clienteFile);

    return 0;
}
