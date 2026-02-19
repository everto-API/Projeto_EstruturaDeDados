# Nome do executável
TARGET = bin/main.exe

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Arquivos fonte
SRC = src/main.c \
      src/paciente.c \
      src/medico.c \
      src/consulta.c \
      src/historico.c

# Arquivos objeto (agora vão para bin/)
OBJ = $(SRC:src/%.c=bin/%.o)

# Regra principal
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Regra para compilar .c em .o dentro de bin/
bin/%.o: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos compilados
clean:
	rm -rf bin
