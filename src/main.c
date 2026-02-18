#include <stdio.h>
#include <string.h>
#include "medico.h"
#include "paciente.h"
#include "consulta.h"

static Paciente_list *PacienteListaAuxiliar; // Para enviar os dados (paciente.c) é necessário uma lista auxiliar

void GerenciarMedicos() {}; // Interface onde irá poder registrar, excluir, verificar qualquer dado relacionado aos médicos
void GerenciarConsultas();
void GerenciarPacientes(Paciente_list **pacientes) {
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
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("CPF: ");
                scanf(" %11s", cpf); while (getchar() != '\n');
                printf("Idade: ");
                scanf("%d", &idade); while (getchar() != '\n');
                cadastro_paciente(nome, cpf, idade, pacientes);
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
                printf("Opção inválida\n");
        }
    } while (opt != 0);
}

int main() { // Interface PRINCIPAL

    Paciente_list *pacientes = NULL;
    Paciente_list *pacientes = NULL;
    Medico_List *medicos = NULL;

    carregar_pacientes(&pacientes);
    carregar_medicos(&medicos);

    printf("Sistema de Gestao Hospitalar da AlmaViva\n\n");
    int opt = 0;
    do {
        printf("[1] Recepcao\n");
        printf("[2] Setor medico\n");
        printf("[3] Gerenciar Consultas\n");
        printf("[4] Sair\n");
        printf("\nDigite uma opcao:\n> ");
        scanf("%d", &opt);
        switch (opt) {
            case 1 : GerenciarPacientes(&pacientes); break;
            case 2 : GerenciarMedicos(); break;
            case 3 : GerenciarConsultas(); break;}  } while (opt != 4);
            
            salvar_pacientes(pacientes);
            salvar_medicos(medicos);
            libera_pacienteList(&pacientes); //Liberar a alocação de memória ao final do programa
            libera_medicoList(&medicos);
    return 0;

}
