#ifndef CONSULTA_H
#define CONSULTA_H

#include "medico.h"
#include "paciente.h"

// contadores para gerar senhas
extern int codigo_CG;
extern int codigo_OR;
extern int codigo_CA;

extern int codigo_CGP;
extern int codigo_ORP;
extern int codigo_CAP;

//Filas por especialidade


//definindo consulta
typedef struct Consulta {
    Paciente_list * paciente;
    char codigo[10];
    char especialidade[30];
    int pf;
}Consulta;

//lista encadeada de consulta
struct elementoFila
{
    Consulta consulta;
    struct elementoFila * prox;
};

typedef struct elementoFila Elem_filaConsulta;

// fila de consulta

    // possui duas filas, uma preferencial e uma normal
    // dessa forma permite a implementação de prioridade
    // prioridade 2 preferencial : 1 normal
typedef struct filaConsulta
{
    int acc; // contador de preferencial

    struct elementoFila * inicio_pf;
    struct elementoFila * final_pf;

    struct elementoFila * inicio_normal;
    struct elementoFila * final_normal;

    

}filaConsulta;

extern filaConsulta * fila_CG;
extern filaConsulta * fila_OR;
extern filaConsulta * fila_CA;

// Aqui tão as funções principais

// aloca a fila
filaConsulta * criar_filaConsulta();
//libera a fila
void liberar_Consulta();

//adiciona na fila normal
void enqueue_ConsultaNormal(filaConsulta *fi, Consulta c);
//adiciona na fila preferencial
void enqueue_ConsultaPF(filaConsulta *fi, Consulta c);
//Verifica se consulta e preferencial ou não e adiciona na fila correspondente
void enqueue_Consulta(filaConsulta *fi, Consulta c);

void dequeue_Consulta(filaConsulta *fi);

Consulta peek_Consulta(filaConsulta *fi);

// gera uma consulta
Consulta criarConsulta(Paciente_list *Paciente, char especialidade[], int pf);
// gera a senha da consulta
void gerarcodigo( char especialidade[], char codigo[], int pf);
// não implementado
void printConsulta(Consulta *c);
void printFilaIntercalada(filaConsulta *f);

#endif