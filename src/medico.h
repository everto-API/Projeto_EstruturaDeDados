//define medico
typedef struct Medico {

    char Nome[50];
    char crm[7];
    char especialidade[30];     }Medico;
//define o no da lista de medico
typedef struct Medico_List{

    Medico medico;
    struct Medico_List *prox;   }Medico_List;
//aloca o primeiro no da lista
Medico_List * cria_MedicoList();
//libera toda a lista
void libera_medicoList(Medico_List **li);

void cadastro_medico(char nome[] ,char crm[], char especialidade[], Medico_List ** li);
void remover_medico(char nome[], Medico_List ** li);

//exibe os medicos e endeço do no atual e do proximo
// obs: somente debug
void print_medicoList(Medico_List *li);

//ordena a lista
Medico_List *ordernar_medicos(Medico_List *li);

//busca a partir do crm caso não encontre retorna null
Medico_List *buscar_Medico(char cpf[], Medico_List *li);