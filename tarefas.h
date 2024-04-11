//    git add README.md
//    git commit -m "escreva"
//    git push -u origin main

#ifndef TAREFAS_H
#define TAREFAS_H

#define TAM_CATEGORIA 100
#define TAM_DESCRICAO 300
#define TOTAL 100

typedef struct {
  int prioridade;
  char descricao[TAM_DESCRICAO];
  char categoria[TAM_CATEGORIA];
} Tarefa;

typedef enum {
  OK,
  MAX_TAREFA,
  SEM_TAREFAS,
  NAO_ENCONTRADO,
  ABRIR,
  FECHAR,
  ESCREVER,
  LER
} ERROS;

// Definição de um tipo de ponteiro para função
typedef ERROS (*funcao)(Tarefa[], int *);

// Protótipos das funções
ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS exportar(
    Tarefa tarefas[],
    int *pos); // Função para exportar as tarefas para um arquivo de texto
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
void clearBuffer();

#endif /* TAREFAS_H */