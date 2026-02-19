#ifndef HISTORICO_H
#define HISTORICO_H

#include "consulta.h"
#include "medico.h"



typedef struct Historico
{
    Consulta consulta;
    Medico_List* medico;
}Historico;

struct elemento
{
    Historico historico;
    struct elemento * prox;
    
};

typedef struct elemento Elem_Historico;

typedef struct elemento* Historico_pilha;

Historico_pilha * historicoConsultas;

Historico_pilha * cria_pilha();

void libera_pilha(Historico_pilha * pi);

void push_Historico(Historico_pilha *pi, Historico h);

void pop_Historico(Historico_pilha *pi);
Historico_pilha peek_Historico(Historico_pilha pi);
void print_Historico(Historico_pilha *pi);

#endif