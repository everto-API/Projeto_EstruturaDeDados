typedef struct Medico {
    char Nome[50];
    char crm[7];
    char especialidade[30];
}Medico;

typedef struct Medico_List
{
    Medico medico;
    struct Medico_List *prox;

}Medico_List;

Medico_List * cria_MedicoList();

void libera_medicoList(Medico_List **li);

void cadastro_medico(char nome[] ,char crm[], char especialidade[], Medico_List ** li);

void remover_medico(char nome[], Medico_List ** li);

void print_medicoList(Medico_List *li);

Medico_List *ordernar_medicos(Medico_List *li);

Medico_List *buscar_Medico(char cpf[], Medico_List *li);