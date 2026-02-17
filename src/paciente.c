#include "paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//aloca o primeiro no da lista
Paciente_list *criar_pacienteList(){

    Paciente_list * li = (Paciente_list*) malloc(sizeof(Paciente_list));
        if(li != NULL){

            li = NULL;
            // A linha estava incoerente (li = NULL) isto QUEBRA o código, a forma certa é 
            // (li->prox = NULL) - everto
            // dessa forma não tava alocando o primeiro no corretamente tinha lixo de memoria
            //retornei como tava -luiz
        }
        return li;

}
//libera toda a lista
void libera_pacienteList(Paciente_list ** li){

    if(*li != NULL){

        Paciente_list* no;

        while (*li != NULL){
        
            no = *li;
            *li = (*li) -> prox;
            free(no);
        }
        
    }
};
//busca por cpf caso não encontre retorna null
Paciente_list *buscar_Paciente(char cpf[], Paciente_list * li){

    while (li != NULL){
            if( strcmp(li->paciente.cpf, cpf) == 0){
                return li;
            }
            li = li -> prox;
        }

    return NULL;

};

//cadastro de pacientes
void cadastro_paciente(char nome[] , char cpf[], int idade, Paciente_list ** li){

    //verifica se o paciente ja foi cadastrado
    if(buscar_Paciente(cpf, *li) == NULL){

        //aloca memoria
        Paciente p;
        Paciente_list* novo = malloc(sizeof(Paciente_list));
        if(novo == NULL) return;

        //insere os dados do paciente
        strcpy(p.Nome, nome);
        strcpy(p.cpf, cpf);
        p.Idade = idade;

        novo->paciente = p;
        
        // insere no lugar correto da lista de forma ordenada por ordem alfabetica

          // Caso 1: lista vazia ou entra no início
        if (*li == NULL || strcmp(novo->paciente.Nome, (*li)->paciente.Nome) < 0) {
            novo->prox = *li;
            *li = novo;
            return;
        }

        // Caso 2: procurar posição
        Paciente_list *atual = *li;
        while (atual->prox != NULL &&
            strcmp(atual->prox->paciente.Nome, novo->paciente.Nome) < 0) {
            atual = atual->prox;
        }

        novo->prox = atual->prox;
        atual->prox = novo;     
        

    }else{

        printf("\nPaciente ja cadastrado\n");

    }



};

// remove paciente da lista e libera memoria
void remover_paciente(char cpf[], Paciente_list ** li){

    Paciente_list * atual, * anterior;

    atual = *li;
    anterior = NULL;

    while(atual != NULL && strcmp(atual->paciente.cpf, cpf) != 0){

        anterior = atual;
        atual = atual->prox;

    }

    if(atual == NULL){
        
        printf("Paciente não encontrado\n");
        return;

    }

    if(anterior == NULL){

        *li = atual->prox;

    }else {

        anterior->prox = atual->prox;

    }

    free(atual);
    printf("Paciente removido\n");

};

//ordena a lista
Paciente_list * ordernar_pacientes(Paciente_list * li){

    Paciente_list * nova = NULL;

    while (li != NULL){

        Paciente_list *atual = li;
        li = li->prox;

         if (nova == NULL || strcmp(atual->paciente.Nome, nova->paciente.Nome) < 0) {
            atual->prox = nova;
            nova = atual;
        } else {
            Paciente_list *p = nova;
            while (p->prox != NULL &&
                   strcmp(p->prox->paciente.Nome, atual->paciente.Nome) < 0) {
                p = p->prox;
            }
            atual->prox = p->prox;
            p->prox = atual;
        }
    }
    return nova;
        

};

// exibe as informações do paciente e endereço do no e do proximo do no
//obs: utilizado para debug
void print_pacienteList(Paciente_list *li) {
    int i = 0;

    if (li == NULL) {
        printf("Lista de pacientes vazia.\n");
        return;
    }

    while (li != NULL) {
        printf("Paciente %d\n", i);
        printf("  Endereco do no: %p\n", (void*) li);
        printf("  Nome: %s\n", li->paciente.Nome);
        printf("  CPF: %s\n", li->paciente.cpf);
        printf("  Idade: %d\n", li->paciente.Idade);
        printf("  Proximo: %p\n", (void*) li->prox);
        printf("-----------------------------\n");

        li = li->prox;
        i++;
    }
}

/*

MODIFICAR ESTE MAIN - é obrigatório ter apenas UM único main

A interface principal ocorre em main.c e não tem necessidade de por um em medico.c e paciente.c
em medico.c e paciente.c (para economizar tempo) pode-se já deixar os cadastros dos médicos feitos

aí na hora de rodar, já teremos alguns médicos e pacientes cadastrados

*/
int main(){

    Paciente_list * pacientes = criar_pacienteList();

    cadastro_paciente("thyerry", "122222222", 22, &pacientes);
    cadastro_paciente("thyerry", "122222222", 22, &pacientes);
    cadastro_paciente("claudio", "122222", 22, &pacientes);
    cadastro_paciente("luiz", "072529", 22, &pacientes);
    cadastro_paciente("luiz", "072529", 22, &pacientes);
    cadastro_paciente("abner", "12221122", 22, &pacientes);
    
    
    print_pacienteList(pacientes);
    
    remover_paciente("072529", &pacientes);
    
    print_pacienteList(pacientes);
    libera_pacienteList(&pacientes);
    printf("\n\n");
    print_pacienteList(pacientes);

}