#include "paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Paciente_list *criar_pacienteList(){

    Paciente_list * li = (Paciente_list*) malloc(sizeof(Paciente_list));
        if(li != NULL){

            li = NULL;
        }
        return li;

}
void libera_pacienteList(Paciente_list ** li){

    if(*li != NULL){

        Paciente_list* no;

        while (*li != NULL){
        
            no = *li;
            *li = (*li) -> prox;
            free(no);
        }
        
    }
};

Paciente_list *buscar_Paciente(char cpf[], Paciente_list * li){

    while (li != NULL){
            if( strcmp(li->paciente.cpf, cpf) == 0){
                return li;
            }
            li = li -> prox;
        }

    return NULL;

};

void cadastro_paciente(char nome[] , char cpf[], int idade, Paciente_list ** li){

    if(buscar_Paciente(cpf, *li) == NULL){

        Paciente p;
        Paciente_list* no = malloc(sizeof(Paciente_list));
        if(no != NULL){

            strcpy(p.Nome, nome);
            strcpy(p.cpf, cpf);
            p.Idade = idade;
           
            no ->paciente = p;
            no ->prox = *li;
        
            *li = ordernar_pacientes(no);

        }

    }else{

        printf("\nPaciente ja cadastrado\n");

    }



};

void remover_paciente(char cpf[], Paciente_list ** li){

    Paciente_list * atual, * anterior;

    atual = *li;
    anterior = NULL;

    while(atual != NULL && strcmp(atual->paciente.cpf, cpf) != 0){

        anterior = atual;
        atual = atual->prox;

    }

    if(atual == NULL){
        
        printf("Paciente não encontrado\n");
        return;

    }

    if(anterior == NULL){

        *li = atual->prox;

    }else {

        anterior->prox = atual->prox;

    }

    free(atual);
    printf("Paciente removido\n");

};

Paciente_list * ordernar_pacientes(Paciente_list * li){

    Paciente_list * nova = NULL;

    while (li != NULL){

        Paciente_list *atual = li;
        li = li->prox;

         if (nova == NULL || strcmp(atual->paciente.Nome, nova->paciente.Nome) < 0) {
            atual->prox = nova;
            nova = atual;
        } else {
            Paciente_list *p = nova;
            while (p->prox != NULL &&
                   strcmp(p->prox->paciente.Nome, atual->paciente.Nome) < 0) {
                p = p->prox;
            }
            atual->prox = p->prox;
            p->prox = atual;
        }
    }
    return nova;
        

};


void print_pacienteList(Paciente_list *li) {
    int i = 0;

    if (li == NULL) {
        printf("Lista de pacientes vazia.\n");
        return;
    }

    while (li != NULL) {
        printf("Paciente %d\n", i);
        printf("  Endereco do no: %p\n", (void*) li);
        printf("  Nome: %s\n", li->paciente.Nome);
        printf("  CPF: %s\n", li->paciente.cpf);
        printf("  Idade: %d\n", li->paciente.Idade);
        printf("  Proximo: %p\n", (void*) li->prox);
        printf("-----------------------------\n");

        li = li->prox;
        i++;
    }
}

int main(){

    Paciente_list * pacientes = criar_pacienteList();

    cadastro_paciente("thyerry", "122222222", 22, &pacientes);
    cadastro_paciente("thyerry", "122222222", 22, &pacientes);
    cadastro_paciente("claudio", "122222", 22, &pacientes);
    cadastro_paciente("luiz", "072529", 22, &pacientes);
    cadastro_paciente("luiz", "072529", 22, &pacientes);
    cadastro_paciente("abner", "12221122", 22, &pacientes);
    
    
    print_pacienteList(pacientes);
    
    remover_paciente("072529", &pacientes);
    
    print_pacienteList(pacientes);
    libera_pacienteList(&pacientes);
    printf("\n\n");
    print_pacienteList(pacientes);

}