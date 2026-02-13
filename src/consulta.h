#include "paciente.h"

typedef struct Consulta {
    Paciente paciente;
    char especialidade[30];
    char preferencial;
}Consulta;