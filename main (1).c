#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// Variáveis globais
int num_cidades; // número de cidades
int **matriz_distancias; // matriz de distâncias entre as cidades
int *melhor_rota; // melhor caminho encontrado
int custo_minimo = INT_MAX; // melhor custo encontrado

// Função para calcular o custo total de uma rota
int calcular_custo_total(int *rota) {
    int custo_total = 0;
    for (int i = 0; i < num_cidades - 1; i++) {
        custo_total += matriz_distancias[rota[i]][rota[i+1]];
    }
    // Adiciona o custo de retorno à cidade inicial
    custo_total += matriz_distancias[rota[num_cidades-1]][rota[0]];
    return custo_total;
}

// Função de Branch-and-Bound recursiva para testar TODAS as permutações
void branch_and_bound_completo(int *rota_atual, bool *cidades_visitadas, int posicao) {
    // Se preenchemos toda a rota, verificamos seu custo
    if (posicao == num_cidades) {
        int custo_atual = calcular_custo_total(rota_atual);
        
        // Atualiza a melhor rota se encontrarmos um custo menor
        if (custo_atual < custo_minimo) {
            custo_minimo = custo_atual;
            
            // Copia a rota atual para a melhor rota
            for (int i = 0; i < num_cidades; i++) {
                melhor_rota[i] = rota_atual[i];
            }
        }
        return;
    }

    // Tenta adicionar cada cidade não visitada na próxima posição
    for (int i = 0; i < num_cidades; i++) {
        if (!cidades_visitadas[i]) {
            // Marca a cidade como visitada
            cidades_visitadas[i] = true;
            rota_atual[posicao] = i;

            // Chamada recursiva para a próxima posição
            branch_and_bound_completo(rota_atual, cidades_visitadas, posicao + 1);

            // Backtrack: desmarca a cidade
            cidades_visitadas[i] = false;
        }
    }
}

// Função para medir o tempo de execução do Branch-and-Bound
void measureExecutionTime() {
    // Prepara as estruturas para a busca
    int *rota_atual = malloc(num_cidades * sizeof(int));
    bool *cidades_visitadas = calloc(num_cidades, sizeof(bool));

    clock_t start, end;
    double cpu_time_used;
    
    start = clock(); // Marca o início do tempo
    branch_and_bound_completo(rota_atual, cidades_visitadas, 0); // Chama o algoritmo
    end = clock();   // Marca o final do tempo
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    // Libera memória temporária
    free(rota_atual);
    free(cidades_visitadas);
}

int main() {
    int i, j;

    // Leitura da entrada
    scanf("%d", &num_cidades); // Lê o número de cidades

    // Aloca memória para a matriz de distâncias
    matriz_distancias = (int**)malloc(num_cidades * sizeof(int*));
    for (i = 0; i < num_cidades; i++) {
        matriz_distancias[i] = (int*)malloc(num_cidades * sizeof(int));
        for (j = 0; j < num_cidades; j++) {
            if (i == j) {
                matriz_distancias[i][j] = 0; // A distância de uma cidade para ela mesma é 0
            } else {
                matriz_distancias[i][j] = INT_MAX; // Inicialmente, não há caminho
            }
        }
    }

    // Lê as distâncias entre as cidades
    int A, B, T;
    for (i = 0; i < num_cidades * (num_cidades - 1) / 2; i++) {
        scanf("%d %d %d", &A, &B, &T);
        A--; B--; // Ajusta para índice 0
        matriz_distancias[A][B] = T;
        matriz_distancias[B][A] = T; // A distância é simétrica
    }

    // Aloca memória para armazenar o melhor caminho
    melhor_rota = (int*)malloc(num_cidades * sizeof(int));

    // Chama a função para medir o tempo de execução do Branch-and-Bound
    measureExecutionTime();

    // Exibe o melhor custo encontrado e o melhor caminho
    printf("Custo mínimo: %d\n", custo_minimo);
    printf("Melhor caminho: ");
    for (i = 0; i < num_cidades; i++) {
        printf("%d ", melhor_rota[i] + 1); // Ajusta para imprimir a cidade de 1 a N
    }
    printf("\n");

    // Libera memória
    for (i = 0; i < num_cidades; i++) {
        free(matriz_distancias[i]);
    }
    free(matriz_distancias);
    free(melhor_rota);

    return 0;
}