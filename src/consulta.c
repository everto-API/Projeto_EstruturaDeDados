#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
// Ainda será produzida
// Para ser feita preciso dos dados de medico.c e paciente.c
// Sem eles não da para fazer a consulta


ConsultaLista *criarConsultaLista(){
    return NULL;
};
void AgendarConsulta(ConsultaLista **lista){
     ConsultaLista *novo = (ConsultaLista*) malloc(sizeof(ConsultaLista));

    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("ID Geral: ");
    scanf("%d", &novo->consulta.IdGeral);

    printf("ID do Medico: ");
    scanf("%d", &novo->consulta.IdMedico);

    printf("ID do Paciente: ");
    scanf("%d", &novo->consulta.IdPaciente);

    printf("Data (DD/MM/AAAA): ");
    scanf(" %10s", novo->consulta.data);

    printf("Hora (HH:MM): ");
    scanf(" %5s", novo->consulta.hora);

    strcpy(novo->consulta.status, "agendado");

    novo->prox = *lista;
    *lista = novo;

    printf("Consulta agendada com sucesso!\n");
};
void ListarConsultas(ConsultaLista *lista){
    if (lista == NULL) {
        printf("Nenhuma consulta cadastrada.\n");
        return;
    }

    ConsultaLista *aux = lista;

    while (aux != NULL) {

        printf("\nID: %d\n", aux->consulta.IdGeral);
        printf("Medico: %d\n", aux->consulta.IdMedico);
        printf("Paciente: %d\n", aux->consulta.IdPaciente);
        printf("Data: %s\n", aux->consulta.data);
        printf("Hora: %s\n", aux->consulta.hora);
        printf("Status: %s\n", aux->consulta.status);

        aux = aux->prox;
    }
};
void GerenciarConsultas(ConsultaLista **consultas){
      int op;

    do {
        printf("\n1 - Agendar Consulta\n");
        printf("2 - Listar Consultas\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);

        switch(op) {
            case 1: AgendarConsulta(consultas); break;
            case 2: ListarConsultas(*consultas); break;
            case 3: CancelarConsulta(*consultas); break;
        }

    } while(op != 0);
};
void CancelarConsulta(ConsultaLista *lista){
    if (lista == NULL) {
        printf("Nenhuma consulta cadastrada.\n");
        return;
    }

    int id;
    printf("Digite o ID da consulta que deseja cancelar: ");
    scanf("%d", &id);

    ConsultaLista *aux = lista;

    while (aux != NULL) {

        if (aux->consulta.IdGeral == id) {

            strcpy(aux->consulta.status, "cancelada");
            printf("Consulta cancelada com sucesso!\n");
            return;
        }

        aux = aux->prox;
    }

    printf("Consulta nao encontrada.\n");
};