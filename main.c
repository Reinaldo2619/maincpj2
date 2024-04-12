// main.c
#include <stdio.h>
#include "tarefas.h"

int main() {
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  Tarefa tarefas[TOTAL];
  int pos = 0;
  ERROS erro = fs[4](tarefas, &pos); 
  if (erro != OK) {
    printf("Error loading tasks: %d\n", erro);
    return 1;
  }

  int opcao;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    opcao--;
    if (opcao > 2)
      printf("Opcao invalida\n");
    
    else if (opcao >= 0) {
      fs[opcao](tarefas, &pos);
      if (erro != OK) {
        printf("Error executing operation: %d\n", erro);
        return 1;
      }
    } else
      printf("Sair...\n");

  } while (opcao >= 0);

  fs[opcao](tarefas, &pos); // Assuming fs[3] is the 'salvar' function
  if (erro != OK) {
    printf("Error saving tasks: %d\n", erro);
    return 1;
  }

  return 0;
}
