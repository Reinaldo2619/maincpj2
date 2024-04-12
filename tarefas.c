//    git add README.md
//    git commit -m "escreva"
//    git push -u origin main

#include <stdio.h>
#include <string.h>
#include "tarefas.h"

// Implementação da função para criar uma nova tarefa
ERROS criar(Tarefa tarefas[], int *pos){
    // Verifica se o limite de tarefas foi atingido
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer(); // Limpa o buffer do teclado

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, TAM_CATEGORIA, stdin); // Lê a categoria da tarefa

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, TAM_DESCRICAO, stdin); // Lê a descrição da tarefa

    *pos = *pos + 1; // Incrementa a posição atual no vetor de tarefas

    return OK; // Retorna OK para indicar sucesso na criação da tarefa
}

// Implementação da função para deletar uma tarefa
ERROS deletar(Tarefa tarefas[], int *pos){
    // Verifica se existem tarefas a serem deletadas
    if(*pos == 0)
        return SEM_TAREFAS;

    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // Ajusta a posição para o índice do array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO; // Retorna NAO_ENCONTRADO se a posição for inválida

    // Desloca as tarefas para preencher o espaço da tarefa deletada
    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1; // Decrementa a posição atual no vetor de tarefas

    return OK; // Retorna OK para indicar que a tarefa foi deletada com sucesso
}

// Implementação da função para listar as tarefas
ERROS listar(Tarefa tarefas[], int *pos){
    // Verifica se existem tarefas para listar
    if(*pos == 0)
        return SEM_TAREFAS;

    char categoria[TAM_CATEGORIA];
    // Solicita a categoria para listar as tarefas correspondentes
    printf("Digite a categoria para listar  ");
    fgets(categoria, TAM_CATEGORIA, stdin);
    if (categoria[0] == '\n') {
        // Lista todas as tarefas se a categoria estiver vazia
        for(int i=0; i<*pos; i++){
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
        }
    } else {
        // Lista as tarefas da categoria especificada
        int encontradas = 0;
        for(int i=0; i<*pos; i++){
            if (strcmp(tarefas[i].categoria, categoria) == 0) {
                printf("Prioridade: %d\t", tarefas[i].prioridade);
                printf("Categoria: %s\t", tarefas[i].categoria);
                printf("Descrição: %s\n", tarefas[i].descricao);
                encontradas++;
            }
        }
        // Se não encontrou nenhuma tarefa para a categoria especificada, exibe uma mensagem
        if (encontradas == 0) {
            printf("Nenhuma tarefa encontrada para a categoria '%s'\n", categoria);
        }
    }

    return OK; // Retorna OK para indicar sucesso na listagem das tarefas
}

// Implementação da função para exportar as tarefas para um arquivo de texto
// Implementação da função para exportar as tarefas para outras categorias
ERROS exportar(Tarefa tarefas[], int *pos) {
    // Verifica se existem tarefas para exportar
    if (*pos == 0)
        return SEM_TAREFAS;

    int indice_tarefa;
    printf("Entre com a posição da tarefa a ser exportada: ");
    scanf("%d", &indice_tarefa);
    indice_tarefa--; // Ajusta a posição para o índice do array
    if (indice_tarefa >= *pos || indice_tarefa < 0)
        return NAO_ENCONTRADO; // Retorna NAO_ENCONTRADO se a posição for inválida

    char nova_categoria[TAM_CATEGORIA];
    printf("Entre com a nova categoria para a tarefa: ");
    getchar(); // Limpa o buffer do teclado
    fgets(nova_categoria, TAM_CATEGORIA, stdin);

    // Remove a quebra de linha do final da categoria
    nova_categoria[strcspn(nova_categoria, "\n")] = 0;

    // Atualiza a categoria da tarefa selecionada
    strcpy(tarefas[indice_tarefa].categoria, nova_categoria);

    // Retorna OK para indicar sucesso na exportação da tarefa
    return OK;
}

// Implementação da função para salvar as tarefas em um arquivo binário
ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR; // Retorna ABRIR se houver erro ao abrir o arquivo

    // Escreve as tarefas no arquivo
    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER; // Retorna ESCREVER se houver erro ao escrever no arquivo

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER; // Retorna ESCREVER se houver erro ao escrever no arquivo

    if(fclose(f))
        return FECHAR; // Retorna FECHAR se houver erro ao fechar o arquivo

    return OK; // Retorna OK para indicar sucesso ao salvar as tarefas
}

// Implementação da função para carregar as tarefas de um arquivo binário
ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR; // Retorna ABRIR se houver erro ao abrir o arquivo

    // Lê as tarefas do arquivo
    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER; // Retorna LER se houver erro ao ler do arquivo

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER; // Retorna LER se houver erro ao ler do arquivo

    if(fclose(f))
        return FECHAR; // Retorna FECHAR se houver erro ao fechar o arquivo

    return OK; // Retorna OK para indicar sucesso ao carregar as tarefas do arquivo
}

// Função auxiliar para limpar o buffer do teclado
void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}