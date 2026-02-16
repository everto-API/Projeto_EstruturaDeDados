#include <stdio.h>
#include "medico.h"
#include "paciente.h"
#include "consulta.h"

void GerenciarMedicos() {}; // Interface onde irá poder registrar, excluir, verificar qualquer dado relacionado aos médicos
void GerenciarPacientes() {}; // A mesma interface de cima mas sobre os pacientes
void GerenciarConsultas() {}; // Verificar as atuais ocorrências

// [17:XX - 16/02/26 - everto] Verificando se vai precisar de mais alguma função

int main() {
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║   Sistema de Gestão Hospitalar da AlmaViva   ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    
    int opt = 0;
    do {
        printf("\n[1] Gerenciar Médicos\n");
        printf("[2] Gerenciar Pacientes\n");
        printf("[3] Gerenciar Consultas\n");
        printf("[4] Sair\n");
        printf("\nDigite uma opção:\n> ");
        scanf("%d", &opt);
        switch (opt) {
            case 1 : GerenciarMedicos(); break;
            case 2 : GerenciarPacientes(); break;
            case 3 : GerenciarConsultas(); break;}  } while (opt != 4);
}; // Interface PRINCIPAL
