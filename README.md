# Sistema de Gestão Hospitalar - Estrutura de Dados

Este projeto é uma aplicação em C desenvolvida para gerenciar o fluxo de um hospital, incluindo cadastro de pacientes, médicos e agendamento de consultas. O foco principal é a **aplicação prática de Estruturas de Dados clássicas** para resolver problemas reais de organização e acesso à informação.

## Estruturas de Dados Utilizadas

O sistema implementa três estruturas de dados fundamentais, cada uma escolhida para atender a requisitos específicos do problema:

### 1. Listas Encadeadas (Linked Lists)
utilizadas para **Pacientes** (`paciente.c`) e **Médicos** (`medico.c`).
*   **Por que?** Permite a inserção dinâmica de novos registros sem tamanho fixo pré-definido (diferente de vetores).
*   **Implementação:** Lista simplesmente encadeada ordenada alfabeticamente. A inserção percorre a lista para encontrar a posição correta, mantendo os dados sempre organizados.

### 2. Filas (Queues)
Utilizadas para o **Agendamento de Consultas** (`consulta.c`).
*   **Por que?** O atendimento segue a lógica **FIFO (First-In, First-Out)**: o primeiro a chegar é o primeiro a ser atendido.
*   **Destaque:** Implementação de uma **Fila de Prioridade**. O sistema intercala atendimentos, priorizando pacientes preferenciais (a cada 2 atendimentos prioritários, 1 normal é chamado), garantindo fluxo contínuo sem travar a fila normal ("starvation").

### 3. Pilhas (Stacks)
Utilizadas para o **Histórico de Consultas** (`historico.c`).
*   **Por que?** O histórico segue a lógica **LIFO (Last-In, First-Out)**. A consulta mais recente realizada é a primeira a ser exibida no topo da lista, facilitando a visualização dos últimos eventos.

## Como Compilar e Executar

Para rodar o projeto, é necessário ter o compilador GCC instalado.

### 🔹 Usando GCC diretamente

1.  **Compilar**:  
    Execute o comando abaixo na raiz do projeto para gerar o executável:
    ```powershell
    gcc src/main.c src/paciente.c src/medico.c src/consulta.c src/historico.c -o main.exe
    ```

2.  **Executar**:
    ```powershell
    ./main.exe
    ```

---

### 🔹 Usando Makefile (Recomendado)

O projeto possui um **Makefile** que automatiza o processo de compilação.

1.  **Compilar**:
    ```powershell
    make
    ```

    O executável será gerado na pasta `bin/`.

2.  **Executar**:
    ```powershell
    make run
    ```

3.  **Limpar arquivos compilados**:
    ```powershell
    make clean
    ```


## Funcionalidades

*   **Recepção**:
    *   **Cadastro**: Cadastrar, Buscar e Remover Pacientes (Ordenado por Nome).
    *   **Agendamento**: Insere paciente na Fila (Normal ou Prioritária).
    *   **Ver Fila**: Visualiza a ordem de atendimento.

*   **Setor Médico**:
    *   **Realizar Consulta**: Remove da Fila e insere na Pilha de Histórico.
    *   **Ver Fila**: Visualiza a ordem de atendimento.

*   **Administração**:
    *   **Cadastro**: Cadastrar e Remover Médicos; Buscar por CRM.
    *   **Histórico**: Visualiza as últimas consultas realizadas.

*   **Persistência**:
    *   Os dados de Pacientes e Médicos são salvos automaticamente na pasta `data/` ao sair.
