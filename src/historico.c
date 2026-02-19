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