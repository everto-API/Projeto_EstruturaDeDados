#ifndef HISTORICO_H
#define HISTORICO_H

#include "consulta.h"
#include "medico.h"


//definindo historico
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

extern Historico_pilha * historicoConsultas;
//aloca a memoria
Historico_pilha * cria_pilha();
//cria o historico
Historico criar_historico(Consulta c, Medico_List* m);
//libera memoria
void libera_pilha(Historico_pilha * pi);
//insere na pilha
void push_Historico(Historico_pilha *pi, Historico h);
//remove da pilha
void pop_Historico(Historico_pilha *pi);
//retorna o topo da pilha
Historico* peek_Historico(Historico_pilha pi);
// exibe o topo da pilha
void print_peekHistorico(Historico_pilha pi);
//exibe a pilha inteira
void print_Historico(Historico_pilha *pi);

#endif