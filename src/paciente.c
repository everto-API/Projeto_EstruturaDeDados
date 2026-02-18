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
        printf("\nPaciente %d\n", i);
        printf("  Endereco do no: %p\n", (void*) li);
        printf("  Nome: %s\n", li->paciente.Nome);
        printf("  CPF: %s\n", li->paciente.cpf);
        printf("  Idade: %d\n", li->paciente.Idade);
        printf("  Proximo: %p\n", (void*) li->prox);
        printf("-----------------------------\n");

        li = li->prox;
        i++;
    }
    void salvar_pacientes(Paciente_list *li) {

    FILE *f = fopen("pacientes.dat", "wb");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de pacientes.\n");
        return;
    }

    while (li != NULL) {
        fwrite(&li->paciente, sizeof(Paciente), 1, f);
        li = li->prox;
    }

    fclose(f);
}
void carregar_pacientes(Paciente_list **li) {

    FILE *f = fopen("pacientes.dat", "rb");
    if (f == NULL) {
        return; // Se não existir, ok
    }

    Paciente temp;

    while (fread(&temp, sizeof(Paciente), 1, f) == 1) {

        cadastro_paciente(temp.Nome, temp.cpf, temp.Idade, li);
    }

    fclose(f);
}

}