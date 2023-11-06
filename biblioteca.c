//
// Created by Pedro Satoru on 12/09/2023.
//

#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100


// Função para salvar todas as tarefas em um arquivo binário
void salvarTarefas(struct tarefa tarefas[], int numTarefas) {
    FILE *arquivo = fopen("tarefas.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tarefas para escrita.\n");
        return;
    }

    fwrite(tarefas, sizeof(struct tarefa), numTarefas, arquivo);
    fclose(arquivo);
}

// Função para carregar todas as tarefas de um arquivo binário
int carregarTarefas(struct tarefa tarefas[]) {
    FILE *arquivo = fopen("tarefas.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de tarefas nao encontrado. Criando novo arquivo.\n");
        return 0;
    }

    int numTarefas = 0;
    while (fread(&tarefas[numTarefas], sizeof(struct tarefa), 1, arquivo) == 1) {
        numTarefas++;
    }
    fclose(arquivo);
    return numTarefas;
}

// Função para cadastrar uma nova tarefa
void cadastrarTarefa(struct tarefa tarefas[], int *numTarefas) {
    if (*numTarefas >= MAX_TAREFAS) {
        printf("Limite maximo de tarefas atingido.\n");
        return;
    }

    struct tarefa novaTarefa;
    printf("Prioridade da tarefa (0 a 10): ");
    scanf("%d", &novaTarefa.prioridade);

    printf("Descricao da tarefa (ate 300 letras): ");
    getchar(); // Lê o caractere de nova linha pendente
    fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);

    printf("Categoria da tarefa (ate 100 letras): ");
    fgets(novaTarefa.categoria, sizeof(novaTarefa.categoria), stdin);

    printf("Andamento da tarefa ('completo' / 'em andamento'/ 'nao iniciado'): ");// criação de uma nova parte da lista de funçoes (andamento)
    fgets(novaTarefa.andamento, sizeof(novaTarefa.andamento), stdin);


    tarefas[*numTarefas] = novaTarefa;
    (*numTarefas)++;
    salvarTarefas(tarefas, *numTarefas); // Salva a tarefa no arquivo
    printf("Tarefa cadastrada com sucesso!\n");
}

// Função para listar todas as tarefas
void listarTarefas(struct tarefa tarefas[], int numTarefas) {
    printf("Lista de Tarefas:\n");
    for (int i = 0; i < numTarefas; i++) {
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Descricao:  %s", tarefas[i].descricao);
        printf("Categoria:  %s", tarefas[i].categoria);
        printf("Andamento:  %s", tarefas[i].andamento);

        printf("\n");
    }
}

// Função para deletar uma tarefa por prioridade e categoria
void deletarTarefa(struct tarefa tarefas[], int *numTarefas) {
    int tarefaEncontrada = 0;
    if (numTarefas > 0) {
        int prioridade;
        printf("Digite a prioridade da tarefa a ser deletada: ");
        scanf("%d", &prioridade);

        char categoria[100];

        printf("Digite a categoria da tarefa: ");
        getchar(); // Lê o caractere de nova linha pendente
        fgets(categoria, sizeof(categoria), stdin);

        for (int i = 0; i < *numTarefas; i++) {
            if (tarefas[i].prioridade == prioridade &&
                strcmp(tarefas[i].categoria, categoria) == 0) {
                tarefaEncontrada = 1;

                // Remover a tarefa movendo as tarefas seguintes para uma posição anterior
                for (int j = i; j < *numTarefas - 1; j++) {
                    tarefas[j] = tarefas[j + 1];
                }
                (*numTarefas)--;
                salvarTarefas(tarefas, *numTarefas); // Salva as tarefas atualizadas no arquivo
                printf("Tarefa com prioridade %d e categoria '%s' deletada com sucesso!\n", prioridade, categoria);
                break;
            }
        }

        if (!tarefaEncontrada) {
            printf("Tarefa nao encontrada.\n");
        }
    }
}
