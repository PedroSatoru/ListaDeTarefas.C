//
// Created by Pedro Satoru on 30/10/2023.
//

#ifndef PROJETO3_1_BIBLIOTECA_H
#define PROJETO3_1_BIBLIOTECA_H

#define MAX_TAREFAS 100
struct tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char andamento[20];
};

void salvarTarefas(struct tarefa tarefas[], int numTarefas);

int carregarTarefas(struct tarefa tarefas[]);

void cadastrarTarefa(struct tarefa tarefas[], int *numTarefas);

void listarTarefas(struct tarefa tarefas[], int numTarefas);

void deletarTarefa(struct tarefa tarefas[], int *numTarefas);

void modificarTarefa(struct tarefa tarefas[], int numTarefas);

void FiltrarTarefa_Prioridade(struct tarefa tarefas[], int numTarefas);

#endif //PROJETO3_1_BIBLIOTECA_H
