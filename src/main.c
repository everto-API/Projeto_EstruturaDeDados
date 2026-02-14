#include <stdio.h>

typedef struct Paciente {
    char Nome[50];
    char cpf[11];
    int Idade;
}Paciente;

typedef struct Medico {
    char Nome[50];
    char crm[6];
    char especialidade[30];
}Medico;

typedef struct Consulta {
    Paciente paciente;
    char especialidade[30];
    char preferencial;
}Consulta;
typedef struct Emergencia {
    Paciente paciente;
    int prioridade;
}Emergencia;
Paciente *listaPacientes = NULL;
int quantidade = 0;
void Incluir() {
   
    quantidade++; // aumenta a quantidade
    listaPacientes = realloc(listaPacientes, quantidade * sizeof(Paciente));
    if (listaPacientes == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
     printf("Nome: ");
    scanf(" %[^\n]", listaPacientes[quantidade - 1].Nome);

    printf("CPF: ");
    scanf(" %s", listaPacientes[quantidade - 1].cpf);

    printf("Idade: ");
    scanf("%d", &listaPacientes[quantidade - 1].Idade);

}; // Cadastrar o Paciente
void Atendimento() {}; // Acho que pro médico dizer pro Paciente oq ele tem?

void BuscarPaciente(){
     if (quantidade == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    char cpfBusca[11];

    printf("Digite o CPF para buscar: ");
    scanf("%s", cpfBusca);

    for (int i = 0; i < quantidade; i++) {

        if (strcmp(listaPacientes[i].cpf, cpfBusca) == 0) {

            printf("\nPaciente encontrado!\n");
            printf("Nome: %s\n", listaPacientes[i].Nome);
            printf("CPF: %s\n", listaPacientes[i].cpf);
            printf("Idade: %d\n", listaPacientes[i].Idade);

            return;
        }
    }
}
 ; // Buscar um paciente em específico pelo CPF;
void ListarTodos() {}; // Listar todos os Pacientes cadastrados
void LimparMemoria() {}; // Sujou, a polícia descobriu, apaga tudo!
int main() {}; // a porra toda rola aqui B)
