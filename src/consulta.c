#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Ainda será produzida
// Para ser feita preciso dos dados de medico.c e paciente.c
// Sem eles não da para fazer a consulta


filaConsulta *criar_filaConsulta(){

    filaConsulta *fila = malloc(sizeof(filaConsulta));
    fila->acc = 0;
    if(fila != NULL){

        fila->inicio_normal = NULL;
        fila->inicio_pf = NULL;
        fila->final_normal = NULL;
        fila->final_pf = NULL;

    }
    return fila;
};

void liberar_Consulta(filaConsulta **fila){

    if(*fila != NULL){

        
        Elem_filaConsulta * no1;
        Elem_filaConsulta * no2;

        while ((*fila)->inicio_normal != NULL || (*fila)->inicio_pf != NULL)
        {
            if((*fila)->inicio_normal != NULL){

                no1 = (*fila)->inicio_normal;
                (*fila)->inicio_normal = (*fila)->inicio_normal->prox;
                free(no1);

            }
            if((*fila)->inicio_pf != NULL){

                no2 = (*fila)->inicio_pf;
                (*fila)->inicio_pf = (*fila)->inicio_pf->prox;
                free(no2);

            }
            
        }
        
        free(*fila);

    }


};

void enqueue_ConsultaNormal(filaConsulta *fi, Consulta c){

    if(fi != NULL){

        Elem_filaConsulta *no = malloc(sizeof(Elem_filaConsulta));

        if(no != NULL){

            no->consulta = c;
            no->prox = NULL;

            if(fi->inicio_normal == NULL){

                fi->inicio_normal = no;
                fi->final_normal = no;

            }else {

                fi->final_normal->prox = no;
                fi->final_normal = no;


            }


        }


    }

};

void enqueue_ConsultaPF(filaConsulta *fi, Consulta c){

     if(fi != NULL){

        Elem_filaConsulta *no = malloc(sizeof(Elem_filaConsulta));

        if(no != NULL){

            no->consulta = c;
            no->prox = NULL;

            if(fi->inicio_pf == NULL){

                fi->inicio_pf = no;
                fi->final_pf = no;

            }else {

                fi->final_pf->prox = no;
                fi->final_pf = no;


            }


        }


    }

};

void enqueue_Consulta(filaConsulta *fi, Consulta c){

    if(c.pf == 1){

        enqueue_ConsultaPF(fi, c);

    }else{

        enqueue_ConsultaNormal(fi, c);

    }


};

void dequeue_Consulta(filaConsulta *fi){

    Elem_filaConsulta *no = malloc(sizeof(Elem_filaConsulta));
    if(no != NULL){

        if(fi->inicio_pf != NULL && fi->acc < 2){
            
            no = fi->inicio_pf;
            fi->inicio_pf = fi->inicio_pf->prox;
            free(no);
            fi->acc ++;
    
        }else if (fi->inicio_normal != NULL)
        {
            no =  fi->inicio_normal;
            fi->inicio_normal = fi->inicio_normal->prox;
            free(no);
            fi->acc = 0;
        }
        

        
    }

};

Elem_filaConsulta * ListarConsultas(filaConsulta *fi);
/*Clínica Geral –.

Cardiologia –.

Ortopedia –*/

Consulta criarConsulta(Paciente_list *Paciente, char especialidade[], int pf){

    Consulta c;
    c.paciente = Paciente;
    c.pf = pf;
    strcpy(c.especialidade,especialidade);
    gerarcodigo(especialidade, c.codigo, pf);
    
    return c;

};

void gerarcodigo( char especialidade[], char codigo[], int pf){

    if(pf == 1){

        if(strcmp(especialidade, "Clínica Geral") == 0){

        codigo_CGP ++;
        sprintf(codigo,"CGP%03d",codigo_CGP);
        

        }else if(strcmp(especialidade, "Cardiologia") == 0){

            codigo_CAP ++;
            sprintf(codigo,"CAP%03d",codigo_CAP);
            

        
        }else if(strcmp(especialidade, "Ortopedia") == 0){

            codigo_ORP ++;
            sprintf(codigo,"ORP%03d",codigo_ORP);
            

        }
    }else{


        if(strcmp(especialidade, "Clínica Geral") == 0){
    
            codigo_CG ++;
            sprintf(codigo,"CG%03d",codigo_CG);
            
    
        }else if(strcmp(especialidade, "Cardiologia") == 0){
    
            codigo_CA ++;
            sprintf(codigo,"CA%03d",codigo_CA);
            
    
        
        }else if(strcmp(especialidade, "Ortopedia") == 0){
    
            codigo_OR ++;
            sprintf(codigo,"OR%03d",codigo_OR);
            
    
        }


    }


};

// Função para imprimir uma consulta individual
void printConsulta(Consulta *c) {
    if (c == NULL) return;

    printf("Código da Consulta: %s\n", c->codigo);
    printf("Especialidade: %s\n", c->especialidade);
    printf("Paciente: %s\n", c->paciente->paciente.Nome); 
    printf("-------------------------\n");
}
// imprimi a fila utilizando a regra de prioridade
void printFilaIntercalada(filaConsulta *f) {
    if (f == NULL) return;

    Elem_filaConsulta *pf = f->inicio_pf;
    Elem_filaConsulta *normal = f->inicio_normal;

    int cont_pf = f->acc;
    int pos = 1;

    printf("=== Fila de Atendimento (2 Prioridade : 1 Normal) ===\n");

    while (pf != NULL || normal != NULL) {

        // imprime até 2 da prioritária
        if (pf != NULL && cont_pf < 2) {
            printf("[%d] (PRIORIDADE)\n", pos++);
            printConsulta(&pf->consulta);
            pf = pf->prox;
            cont_pf++;
        }
        // depois de 2 PF, imprime 1 normal
        else if (normal != NULL) {
            printf("[%d] (NORMAL)\n", pos++);
            printConsulta(&normal->consulta);
            normal = normal->prox;
            cont_pf = 0; // reseta contador
        }
        // se não tem mais normal, continua só PF
        else {
            printf("[%d] (PRIORIDADE)\n", pos++);
            printConsulta(&pf->consulta);
            pf = pf->prox;
        }
    }

    printf("=== Fim da Fila ===\n");
}


void CancelarConsulta();

int main(){

     filaConsulta * fila = criar_filaConsulta();
     Paciente_list * pacientes = criar_pacienteList();
     
     cadastro_paciente("thyerry", "122222222", 22, &pacientes);
     
     Consulta c = criarConsulta(buscar_Paciente("122222222",pacientes),"Clínica Geral", 1);
     Consulta c2 = criarConsulta(buscar_Paciente("122222222",pacientes),"Clínica Geral", 1);
     Consulta c3 = criarConsulta(buscar_Paciente("122222222",pacientes),"Clínica Geral", 1);
     Consulta c4 = criarConsulta(buscar_Paciente("122222222",pacientes),"Clínica Geral", 0);
     Consulta c5 = criarConsulta(buscar_Paciente("122222222",pacientes),"Clínica Geral", 0);

    //printConsulta(&c);
    //printConsulta(&c2);
    //printConsulta(&c3);

    enqueue_Consulta(fila, c);
    enqueue_Consulta(fila, c2);
    enqueue_Consulta(fila, c3);
    enqueue_Consulta(fila, c4);
    enqueue_Consulta(fila, c5);

    printFilaIntercalada(fila);
    dequeue_Consulta(fila);
    printFilaIntercalada(fila);
    dequeue_Consulta(fila);
    printFilaIntercalada(fila);
    dequeue_Consulta(fila);
    printFilaIntercalada(fila);

}
