//    git add README.md
//    git commit -m "escreva"
//    git push -u origin main

#include <stdio.h>
#include "tarefas.h"

#define TAM_CATEGORIA 100
#define TAM_DESCRICAO 300
#define TOTAL 100

int main() {
    funcao fs[] = {criar, deletar, listar, exportar, salvar, carregar};
    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[5](tarefas, &pos); // Carrega as tarefas do arquivo binário
    if (erro != OK)
        pos = 0; // Define a posição como 0 se houver erro ao carregar as tarefas

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas\n"); // Opção para exportar as tarefas para um arquivo de texto
        printf("5 - Salvar tarefas\n");
        printf("6 - Carregar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        opcao--;

        if (opcao < 0 || opcao > 5) {
            printf("Opcao invalida\n");
            continue;
        }

        ERROS resultado = fs[opcao](tarefas, &pos);
        if (resultado != OK) {
            printf("Erro: ");
            switch (resultado) {
                case MAX_TAREFA:
                    printf("Limite de tarefas atingido.\n");
                    break;
                case SEM_TAREFAS:
                    printf("Nao ha tarefas.\n");
                    break;
                case NAO_ENCONTRADO:
                    printf("Tarefa nao encontrada.\n");
                    break;
                case ABRIR:
                    printf("Erro ao abrir arquivo.\n");
                    break;
                case FECHAR:
                    printf("Erro ao fechar arquivo.\n");
                    break;
                case ESCREVER:
                    printf("Erro ao escrever no arquivo.\n");
                    break;
                case LER:
                    printf("Erro ao ler do arquivo.\n");
                    break;
            }
        }
    } while (opcao >= 0);

    fs[4](tarefas, &pos); // Salva as tarefas antes de sair

    return 0;
}