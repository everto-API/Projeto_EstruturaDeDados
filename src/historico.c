#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Historico_pilha * cria_pilha(){

    Historico_pilha * pi = malloc(sizeof(Historico_pilha));

    if(pi != NULL){

        *pi = NULL;

    }

    return pi;

};

void libera_pilha(Historico_pilha * pi){

    if(pi != NULL){

        Elem_Historico * no;

        while (*pi != NULL)
        {
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);

    }


};

void push_Historico(Historico_pilha *pi, Historico h){

    if(pi == NULL) return;

    Elem_Historico * no = malloc(sizeof(Elem_Historico));

    if(no != NULL){

        no->historico = h;
        no->prox = (*pi);
        *pi = no;


    }

};
void pop_Historico(Historico_pilha *pi){

    if(pi == NULL) return;

        
    if((*pi) != NULL){
            
        Elem_Historico * no;
        no = (*pi);
        *pi = (*pi)->prox;
        free(no);


    }


};

void print_Historico(Historico_pilha *pi) {
    if (pi == NULL || *pi == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    Elem_Historico *atual = *pi;
    printf("\n=== Historico de Consultas Realizadas ===\n");
    while (atual != NULL) {
        printf("Codigo: %s | Paciente: %s | Especialidade: %s\n", 
            atual->historico.consulta.codigo, 
            atual->historico.consulta.paciente->paciente.Nome,
            atual->historico.consulta.especialidade);
        atual = atual->prox;
    }
    printf("=========================================\n");
}