#include "medico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Medico_List * cria_MedicoList(){

    Medico_List * li = malloc(sizeof(Medico_List));

    if (li != NULL)  {
        li->prox = NULL;} 
        // A linha estava incoerente (li = NULL) isto QUEBRA o código, a forma certa é 
        // (li->prox = NULL) - everto
    return li;

};

void libera_medicoList(Medico_List **li){

    Medico_List * no;

    while (*li != NULL)
    {
        no = *li;
        *li = (*li)->prox;
        free(no);
    }
    

};

void cadastro_medico(char nome[],char crm[], char especialidade[], Medico_List ** li){

    if(buscar_Medico(crm, *li) == NULL){

        Medico m;
        Medico_List *no = malloc(sizeof(Medico_List));

        if(no != NULL){

            strcpy(m.Nome, nome);
            strcpy(m.crm, crm);
            strcpy(m.especialidade, especialidade);

            no->medico = m;
            no->prox = *li;
            *li = ordernar_medicos(no);
        }

    }else{

        printf("\nMedico ja cadastrado\n");

    }


};

void remover_medico(char crm[], Medico_List ** li){

     Medico_List * atual, * anterior;

    atual = *li;
    anterior = NULL;

    while(atual != NULL && strcmp(atual->medico.crm, crm) != 0){

        anterior = atual;
        atual = atual->prox;

    }

    if(atual == NULL){
        
        printf("Medico não encontrado\n");
        return;

    }

    if(anterior == NULL){

        *li = atual->prox;

    }else {

        anterior->prox = atual->prox;

    }

    free(atual);
    printf("Medico removido\n");



};

void print_medicoList(Medico_List *li){

    if (li == NULL) {
        printf("Lista de medicos vazia.\n");
        return;
    }

    int i = 1;
    while (li != NULL) {
        printf("\n---- Medico %d ----\n", i);
        printf("Endereco do no: %p\n", (void*)li);
        printf("Nome: %s\n", li->medico.Nome);
        printf("CRM: %s\n", li->medico.crm);
        printf("Especialidade: %s\n", li->medico.especialidade);
        printf("Proximo no: %p\n", (void*)li->prox);
        printf("-------------------\n\n");

        li = li->prox;
        i++;
    }

};

Medico_List *ordernar_medicos(Medico_List *li){

        Medico_List * nova = NULL;

    while (li != NULL){

        Medico_List *atual = li;
        li = li->prox;

         if (nova == NULL || strcmp(atual->medico.Nome, nova->medico.Nome) < 0) {
            atual->prox = nova;
            nova = atual;
        } else {
            Medico_List *p = nova;
            while (p->prox != NULL &&
                   strcmp(p->prox->medico.Nome, atual->medico.Nome) < 0) {
                p = p->prox;
            }
            atual->prox = p->prox;
            p->prox = atual;
        }
    }
    return nova;

};

Medico_List *buscar_Medico(char crm[], Medico_List *li){


    while (li != NULL)
    {
        
        if(strcmp(li->medico.crm, crm) == 0){

            return li;

        }
        li = li->prox;

    }
    return NULL;
        

};

/*

MODIFICAR ESTE MAIN - é obrigatório ter apenas UM único main

A interface principal ocorre em main.c e não tem necessidade de por um em medico.c e paciente.c
em medico.c e paciente.c (para economizar tempo) pode-se já deixar os cadastros dos médicos feitos

aí na hora de rodar, já teremos alguns médicos e pacientes cadastrados

*/ 
int main(){

    Medico_List * medicos = cria_MedicoList();

    cadastro_medico("Luiz", "563478", "clinico geral", &medicos);
    cadastro_medico("Luiz", "563478", "clinico geral", &medicos);
    cadastro_medico("Isaac", "563474", "clinico geral", &medicos);
    cadastro_medico("Louis", "563474", "clinico geral", &medicos);
    cadastro_medico("Abener", "563479", "clinico geral", &medicos);

    print_medicoList(medicos);
    
    remover_medico("563474", &medicos);
    
    print_medicoList(medicos);

    libera_medicoList(&medicos);

    print_medicoList(medicos);



};