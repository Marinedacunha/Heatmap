#include <stdio.h>
#include <stdlib.h> // Usado para system("cls")

// --- Constantes para deixar o código mais legível e fácil de mudar ---
#define DIAS 7
#define BAIRROS 2

int main() {
    // --- Declaração da Matriz e Vetores ---
    float chuvas[DIAS][BAIRROS];
    float total_por_bairro[BAIRROS] = {0}; // Vetor para guardar o total de cada bairro
    
    // Variáveis de controle
    int i, j;
    int retorno_scanf; // Para validar a entrada do usuário

    // Variáveis para análise de dados
    float maior_chuva_geral = -1.0;
    int dia_maior_chuva = 0;

    // --- Bloco de Entrada de Dados com Validação ---
    system("cls");
    printf("--- CADASTRO DE CHUVAS (em mm) ---\n");
    printf("--- ControleChuvaPro v1.0 ---\n\n");

    for (i = 0; i < DIAS; i++) {
        for (j = 0; j < BAIRROS; j++) {
            
            // Loop para garantir que a entrada seja válida
            do {
                printf("Digite a chuva para o Dia %d no Bairro %d: ", i + 1, j + 1);
                retorno_scanf = scanf("%f", &chuvas[i][j]);

                // Estrutura if/else para tratar bugs e dados inválidos
                if (retorno_scanf != 1) {
                    // Se o retorno for diferente de 1, o usuário não digitou um número
                    printf("\nERRO: Entrada invalida. Por favor, digite apenas numeros.\n\n");
                    // Limpa o buffer de entrada para evitar um loop infinito
                    while(getchar() != '\n'); 
                
                // MUDANÇA AQUI: Adicionado um 'else if' para checar números negativos
                } else if (chuvas[i][j] < 0) {
                    // Se o número for válido, mas negativo, exibe um erro
                    printf("\nERRO: O valor da chuva nao pode ser negativo. Tente novamente.\n\n");
                    // Forçamos o 'retorno_scanf' para um valor diferente de 1 para que o loop repita
                    retorno_scanf = 0; 
                }

            } while (retorno_scanf != 1); // Repete enquanto a entrada não for um número válido e positivo
        }
    }

    // --- Bloco de Processamento ---
    // Objetivo: Calcular o total de chuva por bairro e encontrar o dia de pico.
    for (j = 0; j < BAIRROS; j++) {
        for (i = 0; i < DIAS; i++) {
            // Soma a chuva do dia atual no total do bairro correspondente
            total_por_bairro[j] += chuvas[i][j];

            // Verifica se a chuva deste dia é a maior já registrada
            if (chuvas[i][j] > maior_chuva_geral) {
                maior_chuva_geral = chuvas[i][j];
                dia_maior_chuva = i + 1; // Guarda o número do dia (i+1)
            }
        }
    }


    // --- Bloco de Saída de Dados (Relatório) ---
    system("cls");
    printf("\n--- RELATORIO DE CHUVAS ---\n");
    printf("\nLEGENDA DO MAPA DE CALOR (HEATMAP):\n");
    printf("  . Chuva Fraca   (0 a 10 mm)\n");
    printf("  * Chuva Moderada(10.1 a 30 mm)\n");
    printf("  # Chuva Forte   (acima de 30 mm)\n\n");

    // --- Cabeçalho da tabela ---
    printf("        "); 
    for (j = 0; j < BAIRROS; j++) {
        char header[20];
        sprintf(header, "Bairro %d", j + 1); 
        printf("%-18s", header);
    }
    printf("\n");
    printf("---------------------------------------------\n");

    // --- Corpo da tabela ---
    for (i = 0; i < DIAS; i++) {
        printf(" Dia %-4d|", i + 1); 
        for (j = 0; j < BAIRROS; j++) {
            float chuva_atual = chuvas[i][j];
            char heatmap_symbol; 

            if (chuva_atual > 30) {
                heatmap_symbol = '#';
            } else if (chuva_atual > 10) {
                heatmap_symbol = '*';
            } else {
                heatmap_symbol = '.';
            }
            
            printf("  (%c) %7.1f mm  ", heatmap_symbol, chuva_atual);
        }
        printf("\n"); 
    }
    printf("---------------------------------------------\n"); 

    // --- Bloco de Resumo e Análise ---
    printf("\n--- ANALISE DO PERIODO ---\n");
    for (j = 0; j < BAIRROS; j++) {
        printf("Total de chuva no Bairro %d: %.1f mm\n", j + 1, total_por_bairro[j]);
    }
    printf("\n-> O dia de pico de chuva foi o Dia %d, com %.1f mm registrados.\n", dia_maior_chuva, maior_chuva_geral);


    return 0;
}
