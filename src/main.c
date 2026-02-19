#include <stdio.h>
#include <string.h>
#include "medico.h"
#include "paciente.h"
#include "consulta.h"
#include "historico.h"

Paciente_list *pacientes;
Medico_List *medicos;
void GerenciarMedicos(Medico_List **medicos) {

    char Nome[50];
    char crm[7];
    char especialidade[30];

    int opt = -1;

    do {
        printf("\n    -- Setor Medico --\n\n");
        printf("[1] Cadastrar Medico\n");
        printf("[2] Buscar Medico (por CRM)\n");
        printf("[3] Imprimir lista de todos os medicos\n");
        printf("[4] Remover Medico\n");
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
                break;
                
            default:
                if (opt != 0) printf("Opcao invalida\n");
        }
    } while (opt != 0);

}; // Interface onde irá poder registrar, excluir, verificar qualquer dado relacionado aos médicos
void GerenciarConsultas() {
    int opt = -1;
    char cpf[12];
    char especialidade[30];
    int pf = 0;

    do {
        printf("\n    -- Administracao de Consultas --\n\n");
        printf("[1] Agendar Consulta\n");
        printf("[2] Realizar Consulta (Chamar Proximo)\n");
        printf("[3] Ver Fila de Espera (Por Especialidade)\n");
        printf("[4] Ver Historico de Consultas\n");
        printf("[0] Voltar ao menu inicial\n\n");
        printf("Digite uma opcao:\n> ");
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n'); // Limpa buffer se nao for numero
            opt = -1;
        }

        switch (opt) {
            case 1: // Agendar
                printf("CPF do Paciente: ");
                scanf(" %11s", cpf); while (getchar() != '\n');
                
                Paciente_list *pNode = buscar_Paciente(cpf, pacientes);
                if (pNode == NULL) {
                    printf("Erro: Paciente nao encontrado. Cadastre-o primeiro.\n");
                    break;
                }

                printf("Especialidade:\n[1] Clinica Geral\n[2] Ortopedia\n[3] Cardiologia\n> ");
                char opc_esp;
                scanf(" %c", &opc_esp); while (getchar() != '\n');
                
                if (opc_esp == '1') strcpy(especialidade, "Clinica Geral");
                else if (opc_esp == '2') strcpy(especialidade, "Ortopedia");
                else if (opc_esp == '3') strcpy(especialidade, "Cardiologia");
                else {
                    printf("Opcao invalida! Definindo como Clinica Geral.\n");
                    strcpy(especialidade, "Clinica Geral");
                }

                // Validacao da especialidade e definicao da fila
                filaConsulta *filaDestino = NULL;
                if (strcmp(especialidade, "Clinica Geral") == 0) filaDestino = fila_CG;
                else if (strcmp(especialidade, "Ortopedia") == 0) filaDestino = fila_OR;
                else if (strcmp(especialidade, "Cardiologia") == 0) filaDestino = fila_CA;

                if (filaDestino == NULL) {
                    printf("Especialidade invalida!\n");
                    break;
                }

                printf("Prioridade? (1 - Sim, 0 - Nao): ");
                scanf("%d", &pf);

                Consulta novaConsulta = criarConsulta(pNode, especialidade, pf);
                enqueue_Consulta(filaDestino, novaConsulta);
                printf("Consulta agendada com sucesso! Codigo: %s\n", novaConsulta.codigo);
                break;

            case 2: // Realizar Consulta
                printf("Qual especialidade atender?\n[1] Clinica Geral\n[2] Ortopedia\n[3] Cardiologia\n> ");
                scanf(" %c", &opc_esp); while(getchar() != '\n');
                
                if (opc_esp == '1') strcpy(especialidade, "Clinica Geral");
                else if (opc_esp == '2') strcpy(especialidade, "Ortopedia");
                else if (opc_esp == '3') strcpy(especialidade, "Cardiologia");
                else {
                    printf("Opcao invalida!\n");
                    break;
                }

                filaConsulta *filaAtender = NULL;
                if (strcmp(especialidade, "Clinica Geral") == 0) filaAtender = fila_CG;
                else if (strcmp(especialidade, "Ortopedia") == 0) filaAtender = fila_OR;
                else if (strcmp(especialidade, "Cardiologia") == 0) filaAtender = fila_CA;

                if (filaAtender != NULL) {
                    // Verifica se tem alguem na fila antes de tentar atender
                    if (filaAtender->inicio_pf == NULL && filaAtender->inicio_normal == NULL) {
                         printf("Fila de %s vazia.\n", especialidade);
                    } else {
                        Consulta cAtendida = peek_Consulta(filaAtender);
                        
                        // Cria registro historico
                        Historico hist;
                        hist.consulta = cAtendida;
                        hist.medico = NULL; // Por enquanto sem medico vinculado
                        
                        push_Historico(historicoConsultas, hist);
                        dequeue_Consulta(filaAtender);
                        
                        printf("Atendendo consulta: %s - %s\n", cAtendida.codigo, cAtendida.paciente->paciente.Nome);
                    }
                } else {
                    printf("Especialidade invalida!\n");
                }
                break;

            case 3: // Ver Fila
                 printf("Qual especialidade visualizar?\n[1] Clinica Geral\n[2] Ortopedia\n[3] Cardiologia\n> ");
                scanf(" %c", &opc_esp); while(getchar() != '\n');
                
                if (opc_esp == '1') strcpy(especialidade, "Clinica Geral");
                else if (opc_esp == '2') strcpy(especialidade, "Ortopedia");
                else if (opc_esp == '3') strcpy(especialidade, "Cardiologia");
                else {
                    printf("Opcao invalida!\n");
                    break;
                }

                if (strcmp(especialidade, "Clinica Geral") == 0) printFilaIntercalada(fila_CG);
                else if (strcmp(especialidade, "Ortopedia") == 0) printFilaIntercalada(fila_OR);
                else if (strcmp(especialidade, "Cardiologia") == 0) printFilaIntercalada(fila_CA);
                else printf("Especialidade invalida!\n");
                break;

            case 4: // Ver Historico
                print_Historico(historicoConsultas);
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida\n");
        }
    } while (opt != 0);
}void GerenciarPacientes(Paciente_list **pacientes) {
    printf("\n    -- Recepcao --\n\n");
    int opt = -1;
    char nome[50];
    char cpf[12];
    int idade;

    do {
        printf("\n\n[1] Cadastrar paciente\n");
        printf("[2] Buscar paciente (por CPF)\n");
        printf("[3] Imprimir lista de todos os pacientes\n");
        printf("[4] Remover Paciente\n");
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
                remover_paciente(cpf, pacientes); break;
                
            default:
                if (opt != 0) printf("Opcao invalida\n");
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
            case 1 : 
                GerenciarPacientes(&pacientes); 
                break;
            case 2 : 
                GerenciarMedicos(&medicos); 
                break;
            case 3 : 
                GerenciarConsultas(); 
                break;
        }  
    } while (opt != 4);
            
            salvar_pacientes(pacientes);
            salvar_medicos(medicos);
            libera_pacienteList(&pacientes); //Liberar a alocação de memória ao final do programa
            libera_medicoList(&medicos);
    return 0;
}