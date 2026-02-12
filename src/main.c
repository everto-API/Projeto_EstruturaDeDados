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

void Incluir() {}; // Cadastrar o Paciente
void Atendimento() {}; // Acho que pro médico dizer pro Paciente oq ele tem?

void BuscarPaciente() {}; // Buscar um paciente em específico pelo ID;
void ListarTodos() {}; // Listar todos os Pacientes cadastrados
void LimparMemoria() {}; // Sujou, a polícia descobriu, apaga tudo!
int main() {}; // a porra toda rola aqui B)
