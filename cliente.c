#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Print Client
void print(Cliente *cli) {
    printf("**********************************************");
    printf("\nClient code:");
    printf("%d", cli->clientCode);
    printf("\nName: ");
    printf("%s", cli->name);
    printf("\n**********************************************");
}

// Cria funcionario. Lembrar de usar free(func)
Client *client(int clientCode, char *name) {
    Client *cli = (Client *) malloc(sizeof(Client));
    //inicializa espaço de memória com ZEROS
    if (cli) memset(cli, 0, sizeof(Client));
    //copia valores para os campos de func
    cli->clientCode = clientCode;
    strcpy(cli->name, name);
    cli->status = 1;
    cli->pointer = -1;

    return cli;
}


// Salva funcionario no arquivo out, na posicao atual do cursor
void save(Client *cli, FILE *out) {
    fwrite(&cli->clientCode, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(cli->name, sizeof(char), sizeof(cli->name), out);
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Client *read(FILE *in) {
    Client *cli = (Client *) malloc(sizeof(Client));
    if (0 >= fread(&cli->clientCode, sizeof(int), 1, in)) {
	free(cli);
	return NULL;
    }
    fread(cli->name, sizeof(char), sizeof(cli->name), in);
    return cli;
}

// Retorna tamanho do funcionario em bytes
int size() {
    return sizeof(int)  //cod
            + sizeof(char) * 100; //nome
}
