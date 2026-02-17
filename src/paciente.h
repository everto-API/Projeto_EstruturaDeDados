
// Definindo paciente
typedef struct Paciente {
    char Nome[50];
    char cpf[12];
    int Idade;
}Paciente;

//Estrutara dos nós
typedef struct Paciente_list
{
    Paciente paciente;
    struct Paciente_list *prox;
}Paciente_list;

// adiciona um paciente na lista
void cadastro_paciente(char nome[] , char cpf[], int idade,  Paciente_list ** li);

// aloca o primeiro no
Paciente_list *criar_pacienteList();

//libera a memoria da lista inteira
void libera_pacienteList(Paciente_list ** li);

//remove um paciente a partir do seu cpf e libera a memoria
void remover_paciente(char cpf[], Paciente_list ** li);

//exibi todos os pacientes, endereço do no e endereço do proximo no    
//obs: apenas para debug
void print_pacienteList(Paciente_list *li);

//insertion sort 
Paciente_list * ordernar_pacientes(Paciente_list * li);

// busca paciente, caso não existe retorna null
Paciente_list *buscar_Paciente(char cpf[], Paciente_list * li);