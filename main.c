#include <stdio.h>
#include "biblioteca.h"



//Pedro Henrique Satoru Lima Takahashi RA:22.123.019-6
//Gabriel Machado da Silva RA:22.123.005-5
int main() {
    struct tarefa tarefas[MAX_TAREFAS];
    int numTarefas = carregarTarefas(tarefas); // Carrega tarefas do arquivo binário

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Deletar Tarefa\n");
        printf("4. Modificar Tarefa\n");
        printf("5. Filtrar por prioridade\n");
        printf("6. Filtrar por andamento\n");
        printf("7. Filtrar por categoria\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &numTarefas);
                break;
            case 2:
                listarTarefas(tarefas, numTarefas);
                break;
            case 3:
                deletarTarefa(tarefas, &numTarefas);
                break;

            case 4:
                modificarTarefa(tarefas,numTarefas);
                break;
            case 5:
                FiltrarTarefa_Prioridade(tarefas, numTarefas);
                break;
            case 6:
                FiltrarTarefa_andamento(tarefas, numTarefas);
                break;
            case 7:
                FiltrarTarefa_categoria(tarefas, numTarefas);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 12);

    return 0;
}
