typedef struct Paciente {
    char Nome[50];
    char cpf[11];
    int Idade;
}Paciente;

typedef struct Paciente_list
{
    Paciente paciente;
    struct Paciente_list *prox;
}Paciente_list;

void cadastro_paciente(char nome[] , char cpf[], int idade,  Paciente_list ** li);

Paciente_list *criar_pacienteList();

void libera_pacienteList(Paciente_list * li);

void remover_paciente(char cpf[], Paciente_list ** li);

void print_pacienteList(Paciente_list *li);

Paciente_list * ordernar_pacientes(Paciente_list * li);

Paciente_list *buscar_Paciente(char cpf[], Paciente_list * li);