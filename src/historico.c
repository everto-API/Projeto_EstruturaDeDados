#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Historico_pilha * historicoConsultas;

Historico_pilha * cria_pilha(){

    Historico_pilha * pi = malloc(sizeof(Historico_pilha));

    if(pi != NULL){

        *pi = NULL;

    }

    return pi;

};

Historico criar_historico(Consulta c, Medico_List* m){

    Historico h;

    h.consulta = c;
    h.medico = m;
    return h;


}

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

Historico * peek_Historico(Historico_pilha pi){


    if(pi != NULL){

        return &((*pi).historico);

    }
    return NULL;

};

void print_peekHistorico(Historico_pilha pi){

    Historico* peek = peek_Historico(pi);
    if(peek != NULL){

        printf("-----------------------------------------------------\n");
        printf("Codigo        : %s\n", peek->consulta.codigo);
        printf("Paciente      : %s\n", peek->consulta.paciente->paciente.Nome);
        printf("Medico        : %s\n", peek->medico->medico.Nome);
        printf("Especialidade : %s\n", peek->consulta.especialidade);
        printf("-----------------------------------------------------\n\n");


    }else{

        printf("Historico vazio.\n");

    }

}

void print_Historico(Historico_pilha *pi) {
    if (pi == NULL || *pi == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    Elem_Historico *atual = *pi;
    int cont = 1;

    printf("\n=====================================================\n");
    printf("           HISTORICO DE CONSULTAS REALIZADAS        \n");
    printf("=====================================================\n\n");

    while (atual != NULL) {

        printf("Consulta #%d\n", cont++);
        printf("-----------------------------------------------------\n");
        printf("Codigo        : %s\n", atual->historico.consulta.codigo);
        printf("Paciente      : %s\n", 
               atual->historico.consulta.paciente->paciente.Nome);
        printf("Medico        : %s\n", 
               atual->historico.medico->medico.Nome);
        printf("Especialidade : %s\n", 
               atual->historico.consulta.especialidade);
        printf("-----------------------------------------------------\n\n");

        atual = atual->prox;
    }

    printf("============== FIM DO HISTORICO =====================\n");
}