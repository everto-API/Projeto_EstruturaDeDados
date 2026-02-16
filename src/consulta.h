#include "medico.h"
#include "paciente.h"

// Ainda será produzida
// Para ser feita preciso dos dados de medico.c e paciente.c
// Sem eles não da para fazer a consulta

typedef struct Consulta {
    int IdGeral;
    int IdMedico;
    int IdPaciente;
    char data[11]; // DD/MM/YYYY
    char hora[6]; // HH:00 (para não ter complexidade, ter apenas as horas :P)
    char status[20]; // situação do coitado: [agendado; realizada; cancelada]
    char diagnostico[200]; // Dizer pro cara q ele tá com câncer de próstata
} Consulta;

typedef struct ConsultaPonteiro {
    Consulta consulta;
    struct ConsultaPonteiro *prox;
} ConsultaLista;

// Aqui tão as funções principais

ConsultaLista *criarConsultaLista();
void AgendarConsulta();
void ListarConsultas();
void GerenciarConsultas();
void CancelarConsulta();

