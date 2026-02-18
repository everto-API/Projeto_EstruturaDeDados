#include "medico.h"
#include "paciente.h"

// Ainda será produzida
// Para ser feita preciso dos dados de medico.c e paciente.c
// Sem eles não da para fazer a consulta


// simplifiquei a consulta pra facilitar a implementação

// contadores para gerar senhas
int codigo_CG = 0;
int codigo_OR = 0;
int codigo_CA = 0;

int codigo_CGP = 0;
int codigo_ORP = 0;
int codigo_CAP = 0;

//definindo consulta
typedef struct Consulta {
    Paciente_list * paciente;
    char codigo[10];
    char especialidade[30];
    int pf;
}Consulta;

//lista encadeada de consulta
struct elemento
{
    Consulta consulta;
    struct elemento * prox;
};

typedef struct elemento Elem_filaConsulta;

// fila de consulta

    // possui duas filas, uma preferencial e uma normal
    // dessa forma permite a implementação de prioridade
    // prioridade 2 preferencial : 1 normal
typedef struct filaConsulta
{
    int acc; // contador de preferencial

    struct elemento * inicio_pf;
    struct elemento * final_pf;

    struct elemento * inicio_normal;
    struct elemento * final_normal;

    

}filaConsulta;


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

//não implementado ainda talvez nem precise
Elem_filaConsulta * ListarConsultas(filaConsulta *fi);

/*Clínica Geral –.

Cardiologia –.

Ortopedia –*/
// gera uma consulta
Consulta criarConsulta(Paciente_list *Paciente, char especialidade[], int pf);
// gera a senha da consulta
void gerarcodigo( char especialidade[], char codigo[], int pf);
// não implementado
void CancelarConsulta();


