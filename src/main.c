#include <stdio.h>
#include <string.h>
#include "medico.h"
#include "paciente.h"
#include "consulta.h"
#include "historico.h"

Paciente_list *pacientes;
Medico_List *medicos;
//Interface do Medico onde podera visualizar a fila e poderá chamar o proximo
void SetorMedico(Medico_List *medicos,  filaConsulta* CG, filaConsulta* CA, filaConsulta* OR, Historico_pilha *pi) {
    
    filaConsulta* fila;
    Medico_List * medico;
    Consulta* c;
    char crm[7];
    int opt = -1;

    printf("\n    -- Setor Medico --\n\n");
    
    printf("CRM: ");
    scanf(" %6s", crm); while (getchar() != '\n');
    medico = buscar_Medico(crm,medicos);
    if(medico != NULL){
        
        if(strcmp(medico->medico.especialidade, "Ortopedia") == 0){

            fila = OR;

        }else if(strcmp(medico->medico.especialidade, "Cardiologia") == 0){

            fila = CA;

        }else{

            fila = CG;

        }


         do {
        printf("\n    -- Setor Medico --\n\n");
        printf("---------------------------------\n");
        printf("Nome: %s\n", medico->medico.Nome);
        printf("CRM: %s\n", medico->medico.crm);
        printf("Especialidade: %s\n", medico->medico.especialidade);
        printf("---------------------------------\n\n");
        printf("[1] Chamar Proximo da Fila\n");
        printf("[2] Ver Fila\n");
        printf("[0] Voltar ao menu inicial\n\n");
        printf("Digite uma opcao:\n> ");
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n'); // Limpa buffer se nao for numero
            opt = -1;
        }

        switch(opt){
            
            case 1:
                c = peek_Consulta(fila);
                if(c != NULL){
                    
                    push_Historico(pi, c, medicos);
                    dequeue_Consulta(fila);
                    
                }else{

                    printf("\nNao ha pacientes aguardando atendimento.\n");

                }
                break;

            case 2:
                printFilaIntercalada(fila);
                break;
            
            default:
                if (opt != 0) printf("Opcao invalida\n");
                break;
            
        }

    } while (opt != 0);

    }else{

        printf("Cadastro Medico Nao Encontrado.\n");

    }

};// Interface onde irá poder registrar, excluir, verificar qualquer dado relacionado aos médicos
// Mostra o historico de consultas 
void admin(Medico_List** medicos, Historico_pilha *pi){

    char Nome[50];
    char crm[7];
    char especialidade[30];

    int opt = -1;

    do {
        printf("\n    -- Administracao --\n\n");
        printf("[1] Cadastrar Medico\n");
        printf("[2] Buscar Medico (por CRM)\n");
        printf("[3] Imprimir lista de todos os medicos\n");
        printf("[4] Remover Medico\n");
        printf("[5] Historico\n");
        printf("[6] Ultima Consulta\n");
        printf("[0] Voltar ao menu inicial\n\n");
        printf("Digite uma opcao:\n> ");
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n'); // Limpa buffer se nao for numero
            opt = -1;
        }

        switch (opt) {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]", Nome);
                printf("CRM: ");
                scanf(" %6s", crm); while (getchar() != '\n');
                
                printf("Especialidade:\n[1] Clinica Geral\n[2] Ortopedia\n[3] Cardiologia\n> ");
                char opc_esp;
                scanf(" %c", &opc_esp); while (getchar() != '\n');
                
                if (opc_esp == '1') strcpy(especialidade, "Clinica Geral");
                else if (opc_esp == '2') strcpy(especialidade, "Ortopedia");
                else if (opc_esp == '3') strcpy(especialidade, "Cardiologia");
                else strcpy(especialidade, "Clinica Geral"); // Default

                cadastro_medico(Nome, crm, especialidade, medicos);
                salvar_medicos(*medicos);
                break;

            case 2: 
                printf("CRM: ");
                scanf(" %6s", crm); while (getchar() != '\n');
                Medico_List *encontrou = buscar_Medico(crm, *medicos);
                if (encontrou) {
                    printf("Nome: %s\nCRM: %s\nEspecialidade: %s\n", encontrou->medico.Nome, encontrou->medico.crm, encontrou->medico.especialidade);
                } else {
                    printf("Medico nao encontrado\n");
                } 
                break;
            
            case 3:
                print_medicoList(*medicos); 
                break;

            case 4:
                printf("CRM do Medico a remover: ");
                scanf(" %6s", crm); while (getchar() != '\n');
                remover_medico(crm, medicos);
                salvar_medicos(*medicos); 
                break;
            case 5:

                print_Historico(pi);
                break;
            
            case 6:
                
                print_peekHistorico(*pi);
                break;

            default:
                if (opt != 0) printf("Opcao invalida\n");
                break;
        }
    } while (opt != 0);

};
//Cadastro de pacientes / Resgistro de Consulta
void Recepcao(Paciente_list **pacientes, filaConsulta* CG, filaConsulta* CA, filaConsulta* OR) {
    printf("\n    -- Recepcao --\n\n");
    int opt = -1;
    char nome[50];
    char cpf[12];
    int idade;
    Paciente_list *p;
    Consulta c;
    int op;
    int pf;

    do {
        printf("\n\n[1] Cadastrar paciente\n");
        printf("[2] Buscar paciente (por CPF)\n");
        printf("[3] Imprimir lista de todos os pacientes\n");
        printf("[4] Remover Paciente\n");
        printf("[5] Registrar Consulta\n");
        printf("[6] Imprimir fila de Consultas\n");
        printf("[0] Voltar ao menu inicial\n\n");
        printf("Digite uma opcao:\n> ");
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n'); // Limpa buffer se nao for numero
            opt = -1;
        }

        switch (opt) {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("CPF: ");
                scanf(" %11s", cpf); while (getchar() != '\n');
                printf("Idade: ");
                scanf("%d", &idade); while (getchar() != '\n');
                cadastro_paciente(nome, cpf, idade, pacientes);
                salvar_pacientes(*pacientes);
                break;

            case 2: 
                printf("CPF: \n");
                scanf(" %11s", cpf); while (getchar() != '\n');
                Paciente_list *encontrou = buscar_Paciente(cpf, *pacientes);
                if (encontrou) {
                    printf("Nome: %s\nCPF: %s\nIdade: %d\n", encontrou->paciente.Nome, encontrou->paciente.cpf, encontrou->paciente.Idade);} 
                else {printf("Paciente não encontrado\n");} break;
            
            case 3:
                print_pacienteList(*pacientes); break;

            case 4:
                printf("CPF: ");
                scanf(" %11s", cpf); while (getchar() != '\n');
                remover_paciente(cpf, pacientes); 
                salvar_pacientes(*pacientes);
                break;
            
            case 5:
                printf("CPF: ");
                scanf(" %11s", cpf); while (getchar() != '\n');
                p = buscar_Paciente(cpf,*pacientes);
                if(p != NULL){
                    
                    printf("\n\nTIPO DE ATENDIMENTO:\n\n");
                    printf("[1] PREFERENCIAL\n");
                    printf("[2] NORMAL\n");
                    printf("Digite uma opcao:\n> ");
                    scanf("%d", &op);
                    
                    switch (op)
                    {
                    case 1:
                        pf = 1;
                        break;
                    
                    case 2:
                        pf = 0;
                        break;
                    default:
                        pf = 0;
                        break;
                    }

                    printf("\n\nESPECIALIDADE:\n\n");
                    printf("[1] Clinica Geral\n");
                    printf("[2] Cardiologia\n");
                    printf("[3] Ortopedia\n");
                    printf("Digite uma opcao:\n> ");
                    scanf("%d", &op);

                    switch(op){

                        case 1:
                        c = criarConsulta(p, "Clinica Geral",pf);
                        enqueue_Consulta(CG, c);
                        break;

                        case 2:
                        c = criarConsulta(p, "Cardiologia",pf);
                        enqueue_Consulta(CA, c);
                        break;

                        case 3:
                        c = criarConsulta(p, "Ortopedia",pf);
                        enqueue_Consulta(OR, c);
                        break;

                        default:
                         c = criarConsulta(p, "Clinica Geral",pf);
                        enqueue_Consulta(CG, c);
                        break;

                    }

                }else{

                    printf("Paciente nao encontrado.\n");

                }
                break;

            case 6:
                printFilaIntercalada(CG);
                printFilaIntercalada(CA);
                printFilaIntercalada(OR);
                break;
                
            default:
                
                if(opt != 0){printf("Opçao inválida\n");}
                break;
        }
    } while (opt != 0);
}

int main() { // Interface PRINCIPAL

    pacientes = criar_pacienteList();
    medicos = cria_MedicoList();

    fila_CG = criar_filaConsulta();
    fila_OR = criar_filaConsulta();
    fila_CA = criar_filaConsulta();

    historicoConsultas = cria_pilha();

    carregar_pacientes(&pacientes);
    carregar_medicos(&medicos);

    printf("Sistema de Gestao Hospitalar da AlmaViva\n\n");
    int opt = 0;
    do {
        printf("[1] Recepcao\n");
        printf("[2] Setor medico\n");
        printf("[3] Administracao\n");
        printf("[4] Sair\n");
        printf("\nDigite uma opcao:\n> ");
        scanf("%d", &opt);
        switch (opt) {
            case 1 : Recepcao(&pacientes,fila_CG,fila_CA,fila_OR); break;
            case 2 : SetorMedico(medicos,fila_CG,fila_CA,fila_OR,historicoConsultas); break;
            case 3 : admin(&medicos, historicoConsultas); break;}  } while (opt != 4);
            
            salvar_pacientes(pacientes);
            salvar_medicos(medicos);
            libera_pacienteList(&pacientes); //Liberar a alocação de memória ao final do programa
            libera_medicoList(&medicos);
            liberar_Consulta(&fila_CG);
            liberar_Consulta(&fila_CA);
            liberar_Consulta(&fila_OR);
            libera_pilha(historicoConsultas);
    return 0;
}