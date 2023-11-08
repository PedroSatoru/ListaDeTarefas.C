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
// Função para modificar uma tarefa existente
void modificarTarefa(struct tarefa tarefas[], int numTarefas) {
    int prioridade;
    printf("Digite a prioridade da tarefa a ser modificada: ");
    scanf("%d", &prioridade);

    char categoria[100];
    printf("Digite a categoria da tarefa: ");
    getchar(); // Lê o caractere de nova linha pendente
    fgets(categoria, sizeof(categoria), stdin);

    char andamento[100];
    printf("Digite o andamento da tarefa: ");
    fgets(andamento, sizeof(andamento), stdin);

    int tarefaEncontrada=0;

    int escolha;
    printf("1. Prioridade \n2.Descricao \n3. Categoria \n4. Andamento \n  Digite o campo que vc deseja alterar: ");
    scanf("%d",&escolha);

    for (int i = 0; i < numTarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0 && strcmp(tarefas[i].andamento, andamento) == 0 && escolha==1) {
            tarefaEncontrada = 1;

            printf("Nova prioridade da tarefa (0 a 10): ");
            scanf("%d", &tarefas[i].prioridade);

            salvarTarefas(tarefas, numTarefas); // Salva as tarefas atualizadas no arquivo
            printf("Tarefa modificada com sucesso!\n");
            break;

        }

    }
    for (int i = 0; i < numTarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0 && strcmp(tarefas[i].andamento, andamento) == 0 && escolha==2) {
            tarefaEncontrada = 2;

            printf("Nova descricao da tarefa (ate 300 letras): ");
            getchar(); // Lê o caractere de nova linha pendente
            fgets(tarefas[i].descricao, sizeof(tarefas[i].descricao), stdin);

            salvarTarefas(tarefas, numTarefas); // Salva as tarefas atualizadas no arquivo
            printf("Tarefa modificada com sucesso!\n");
            break;

        }

    }

    for (int i = 0; i < numTarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0 && strcmp(tarefas[i].andamento, andamento) == 0 && escolha==3) {
            tarefaEncontrada = 3;

            printf("Nova categoria da tarefa (ate 100 letras): ");
            getchar();
            fgets(tarefas[i].categoria, sizeof(tarefas[i].categoria), stdin);

            salvarTarefas(tarefas, numTarefas); // Salva as tarefas atualizadas no arquivo
            printf("Tarefa modificada com sucesso!\n");
            break;

        }

        for (int i = 0; i < numTarefas; i++) {
            if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0 && strcmp(tarefas[i].andamento, andamento) == 0 && escolha==4) {
                tarefaEncontrada = 4;

                printf("Novo andamento da tarefa ('completo' / 'em andamento'/ 'nao iniciado'): ");
                getchar();
                fgets(tarefas[i].andamento, sizeof(tarefas[i].andamento), stdin);

                salvarTarefas(tarefas, numTarefas); // Salva as tarefas atualizadas no arquivo
                printf("Tarefa modificada com sucesso!\n");
                break;

            }

        }

    }

    if (!tarefaEncontrada) {
        printf("Tarefa nao encontrada.\n");
    }
}
//Funcao para filtrar tarefas por prioridade
void FiltrarTarefa_Prioridade(struct tarefa tarefas[], int numTarefas){
    int prioridadeFiltro;
    printf("Digite a prioridade que voce deseja filtrar : ");
    scanf("%d", &prioridadeFiltro);

    int tarefaEncontrada=0;

    for(int i= 0; i<numTarefas; i++ ){
        if( tarefas[i].prioridade == prioridadeFiltro){
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao : %s", tarefas[i].descricao);
            printf("Categoria : %s", tarefas[i].categoria);
            printf("Andamento : %s\n", tarefas[i].andamento);
            tarefaEncontrada= 1 ;
        }
    }
    if(!tarefaEncontrada){
        printf("Nenhuma tarefa com a prioridade: %d foi encontrada", prioridadeFiltro);
    }
}

//Funcao para filtrar tarefas por andamento
void FiltrarTarefa_andamento(struct tarefa tarefas[], int numTarefas){
    char andamento[20];
    printf("Digite o andamento da tarefa: ");
    getchar();
    fgets(andamento, sizeof(andamento), stdin);

    int tarefaEncontrada=0;

    for(int i= 0; i<numTarefas; i++ ){
        if (strcmp(tarefas[i].andamento, andamento) == 0) {
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao : %s", tarefas[i].descricao);
            printf("Categoria : %s", tarefas[i].categoria);
            printf("Andamento : %s\n", tarefas[i].andamento);
            tarefaEncontrada= 1 ;
        }
    }
    if(!tarefaEncontrada){
        printf("Nenhuma tarefa com o andamento: %s foi encontrada", andamento);
    }
}

//Funcao para filtrar tarefas por categoria
void FiltrarTarefa_categoria(struct tarefa tarefas[], int numTarefas){
    char categoria_filtro[100];
    printf("Digite a categoria da tarefa: ");
    getchar();
    fgets(categoria_filtro, sizeof(categoria_filtro), stdin);

    int tarefaEncontrada=0;

    for(int i= 0; i<numTarefas; i++ ){
        if (strcmp(tarefas[i].categoria, categoria_filtro) == 0) {
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao : %s", tarefas[i].descricao);
            printf("Categoria : %s", tarefas[i].categoria);
            printf("Andamento : %s\n", tarefas[i].andamento);
            tarefaEncontrada= 1 ;
        }
    }
    if(!tarefaEncontrada){
        printf("Nenhuma tarefa com a categoria: %s foi encontrada", categoria_filtro);
    }
}

//Funcao para filtrar tarefas por prioridade e categoria
void FiltrarTarefa_prioridade_e_categoria(struct tarefa tarefas[], int numTarefas){

    int prioridadeFiltro;
    printf("Digite a prioridade que voce deseja filtrar : ");
    scanf("%d", &prioridadeFiltro);

    char categoria_filtro[100];
    printf("Digite a categoria da tarefa: ");
    getchar();
    fgets(categoria_filtro, sizeof(categoria_filtro), stdin);

    int tarefaEncontrada=0;

    for(int i= 0; i<numTarefas; i++ ){
        if ((strcmp(tarefas[i].categoria, categoria_filtro) == 0) && tarefas[i].prioridade == prioridadeFiltro){
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao : %s", tarefas[i].descricao);
            printf("Categoria : %s", tarefas[i].categoria);
            printf("Andamento : %s\n", tarefas[i].andamento);
            tarefaEncontrada= 1 ;
        }
    }
    if(!tarefaEncontrada){
        printf("Nenhuma tarefa com a prioridade: %d e categoria: %s foi encontrada",prioridadeFiltro, categoria_filtro);
    }
}

void exportarPorPrioridade(struct tarefa tarefas[], int numTarefas) {
    int prioridadeDesejada;
    printf("Digite a prioridade que deseja filtrar: ");
    scanf("%d", &prioridadeDesejada);

    FILE *arquivo = fopen("tarefas_prioridade.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tarefas por prioridade para escrita.\n");
        return;
    }

    int tarefasExportadas = 0;

    for (int i = 0; i < numTarefas; i++) {
        if (tarefas[i].prioridade == prioridadeDesejada) {
            fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s", tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s", tarefas[i].categoria);
            fprintf(arquivo, "Andamento: %s\n", tarefas[i].andamento);
            fprintf(arquivo, "\n");
            tarefasExportadas++;
        }
    }

    fclose(arquivo);

    if (tarefasExportadas > 0) {
        printf("Tarefas com prioridade %d exportadas para o arquivo 'tarefas_prioridade.txt'\n", prioridadeDesejada);
    } else {
        printf("Nenhuma tarefa encontrada com a prioridade %d para exportar.\n", prioridadeDesejada);
    }
}

void exportarPorCategoria(struct tarefa tarefas[], int numTarefas) {
    char categoria_filtro[100];
    printf("Digite a categoria da tarefa para ser exportada: ");
    getchar();
    fgets(categoria_filtro, sizeof(categoria_filtro), stdin);

    FILE *arquivo = fopen("tarefas_categoria.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tarefas por prioridade para escrita.\n");
        return;
    }

    int tarefasExportadas = 0;

    for (int i = 0; i < numTarefas; i++) {
        if (strcmp(tarefas[i].categoria, categoria_filtro) == 0) {
            fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s", tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s", tarefas[i].categoria);
            fprintf(arquivo, "Andamento: %s\n", tarefas[i].andamento);
            fprintf(arquivo, "\n");
            tarefasExportadas++;
        }
    }

    fclose(arquivo);

    if (tarefasExportadas > 0) {
        printf("Tarefas com categoria %s exportadas para o arquivo 'tarefas_prioridade.txt'\n", categoria_filtro);
    } else {
        printf("Nenhuma tarefa encontrada com a categoria %s para exportar.\n", categoria_filtro);
    }
}

void exportarPorPrioridade_e_Categoria(struct tarefa tarefas[], int numTarefas) {

    int prioridadeDesejada;
    printf("Digite a prioridade que deseja filtrar: ");
    scanf("%d", &prioridadeDesejada);


    char categoria_filtro[100];
    printf("Digite a categoria da tarefa para ser exportada: ");
    getchar();
    fgets(categoria_filtro, sizeof(categoria_filtro), stdin);

    FILE *arquivo = fopen("tarefas_propriedade_e_categoria.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tarefas por prioridade para escrita.\n");
        return;
    }

    int tarefasExportadas = 0;

    for (int i = 0; i < numTarefas; i++) {
        if ((strcmp(tarefas[i].categoria, categoria_filtro) == 0) && tarefas[i].prioridade == prioridadeDesejada){
            fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
            fprintf(arquivo, "Descricao: %s", tarefas[i].descricao);
            fprintf(arquivo, "Categoria: %s", tarefas[i].categoria);
            fprintf(arquivo, "Andamento: %s\n", tarefas[i].andamento);
            fprintf(arquivo, "\n");
            tarefasExportadas++;
        }
    }

    fclose(arquivo);

    if (tarefasExportadas > 0) {
        printf("Tarefas com prioridade %d e categoria %s exportadas para o arquivo 'tarefas_prioridade.txt'\n",prioridadeDesejada, categoria_filtro);
    } else {
        printf("Nenhuma tarefa encontrada com a prioridade %d e categoria %s para exportar.\n",prioridadeDesejada, categoria_filtro);
    }
}

