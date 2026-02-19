#include "medico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Medico_List * cria_MedicoList(){

    Medico_List * li = malloc(sizeof(Medico_List));

    if (li != NULL)  {

        li = NULL;} 
        // A linha estava incoerente (li = NULL) isto QUEBRA o código, a forma certa é 
        // (li->prox = NULL) - everto 
        // dessa forma não tava alocando o primeiro no corretamente tinha lixo de memoria
        //retornei como tava -luiz
    return li;

};

//libera toda a lista
void libera_medicoList(Medico_List **li){

    Medico_List * no;

    while (*li != NULL)
    {
        no = *li;
        *li = (*li)->prox;
        free(no);
    }
    

};
//cadastra o medico
void cadastro_medico(char nome[],char crm[], char especialidade[], Medico_List ** li){

    //verifica se o medico ja foi cadastrado
    if(buscar_Medico(crm, *li) == NULL){


        Medico m;
        //aloca memoria
        Medico_List *novo = malloc(sizeof(Medico_List));

        if(novo != NULL){

            //insere as informações do medico
            strcpy(m.Nome, nome);
            strcpy(m.crm, crm);
            strcpy(m.especialidade, especialidade);

             novo->medico = m;
            
             // insere na lista no lugar correto de forma ordenada por ordem alfabetica
            // Caso 1: lista vazia ou entra no início
            if (*li == NULL || strcmp(novo->medico.Nome, (*li)->medico.Nome) < 0) {
                novo->prox = *li;
                *li = novo;
                return;
            }

            // Caso 2: procurar posição
            Medico_List *atual = *li;
            while (atual->prox != NULL &&
                strcmp(atual->prox->medico.Nome, novo->medico.Nome) < 0) {
                atual = atual->prox;
            }

            novo->prox = atual->prox;
            atual->prox = novo;     
            }

    }else{

        printf("\nMedico ja cadastrado\n");

    }


};
//remove da lista a partir do crm e libera a memoria
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

// exibe as informações do medico e endereço do no atual e do proximo
// obs: apenas debug
void print_medicoList(Medico_List *li){

    if (li == NULL) {
        printf("Lista de medicos vazia.\n");
        return;
    }

    int i = 1;
    while (li != NULL) {
        printf("\n---- Medico %d ----\n", i);
        printf("Nome: %s\n", li->medico.Nome);
        printf("CRM: %s\n", li->medico.crm);
        printf("Especialidade: %s\n", li->medico.especialidade);
        printf("-------------------\n\n");

        li = li->prox;
        i++;
    }

};
// ordena a lista
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

// busca o medico a partir do crm caso não encontre retorna null
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

void salvar_medicos(Medico_List *li) {

    FILE *f = fopen("./data/medicos.dat", "wb");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de medicos.\n");
        return;
    }

    while (li != NULL) {
        fwrite(&li->medico, sizeof(Medico), 1, f);
        li = li->prox;
    }

    fclose(f);
}
void carregar_medicos(Medico_List **li) {

    FILE *f = fopen("./data/medicos.dat", "rb");
    if (f == NULL) {
        return;
    }

    Medico temp;

    while (fread(&temp, sizeof(Medico), 1, f) == 1) {

        cadastro_medico(temp.Nome, temp.crm, temp.especialidade, li);
    }

    fclose(f);
}