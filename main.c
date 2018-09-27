#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

void insere_5_funcionarios(FILE *out) {
    printf("Inserindo 5 funcionários no arquivo...");
    
    Funcionario *f1 = funcionario(1, "Ana", "000.000.000-00", "01/01/1980", 3000);
    salva(f1, out);
    free(f1);
    Funcionario *f2 = funcionario(2, "Carlos", "111.111.111-11", "01/01/1990", 500);
    salva(f2, out);
    free(f2);
    Funcionario *f3 = funcionario(3, "Fátima", "222.222.222-22", "02/02/1980", 1000);
    salva(f3, out);
    free(f3);
    Funcionario *f4 = funcionario(4, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
    salva(f4, out);
    free(f4);
    Funcionario *f5 = funcionario(5, "Silvia", "444.444.444-44", "04/04/1980", 900);
    salva(f5, out);
    free(f5);       
}

void le_funcionarios(FILE *in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    Funcionario *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

void le_segundo_funcionario(FILE *in) {
    printf("\n\nLendo segundo funcionário do arquivo...\n\n");
    //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro 
    //(vamos pular o primeiro e nos posicionar no início do segundo)
    //** ATENÇÃO: não usar sizeof(Funcionario), pois ele pode retornar valor maior que o tamanho ocupado em disco, 
    //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))
    //SEEK_SET indica o início do arquivo
    //ao final, o cursor estará posicionado em 0 + tamanho() +1
    fseek(in, tamanho(), SEEK_SET);
    Funcionario *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

void adiciona_funcionario(FILE *in) {
    printf("\n\nAdicionando funcionário no final do arquivo...\n\n");
    //pula 5 registros para posicionar no início do final do arquivo
    fseek(in, tamanho() * 5, SEEK_SET);
    Funcionario *f = funcionario(6, "Bruna", "666.666.666-66", "06/06/1980", 2500);
    salva(f, in);
    free(f);
    
    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 5, SEEK_SET);
    Funcionario *f6 = le(in);
    if (f6 != NULL) {
        imprime(f6);
        free(f6);
    }    
}

void sobrescreve_quarto_funcionario(FILE *in) {
    printf("\n\nSobrescrevendo quarto funcionário do arquivo...\n\n");
    //pula primeiros 3 registros para posicionar no início do quarto registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Funcionario *f4 = funcionario(7, "Catarina", "777.777.777-77", "07/07/1990", 5000);
    salva(f4, in);
    free(f4);
    
    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Funcionario *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

void main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        //insere funcionários
        insere_5_funcionarios(out);
        //volta ao início do arquivo e lê os funcionários inseridos
        le_funcionarios(out);
        //volta ao início do arquivo e lê o segundo funcionário
        le_segundo_funcionario(out);
        //grava mais um funcionário no final do arquivo
        adiciona_funcionario(out);
        //sobrescreve quarto funcionário
        sobrescreve_quarto_funcionario(out);
        //lendo o arquivo todo novamente
        le_funcionarios(out);
        
        //fecha arquivo
        fclose(out);    
    }
}

