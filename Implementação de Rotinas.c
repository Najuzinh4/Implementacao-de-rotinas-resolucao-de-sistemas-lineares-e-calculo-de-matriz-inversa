#include <stdio.h>
#include <stdlib.h> 

// Implementação das rotinas <3 
void LeituraSistema() {
    printf("Opção selecionada: Leitura de sistema\n");
    int n; 
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);

    double matriz[n][n];
    double vetor[n];

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Digite o elemento M[%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        printf("Digite o elemento V[%d]: ", i);
        scanf("%lf", &vetor[i]);
    }

    printf("O sistema foi lido com sucesso!\n");
}

void EscritaSistema() {
    printf("Opção selecionada: Escrita de sistema\n");
    // Implemente a escrita do sistema aqui
}

void EscritaSolucao() {
    printf("Opção selecionada: Escrita de solução\n");
    // Implemente a escrita da solução aqui
}

void Gauss() {
    printf("Opção selecionada: Método de Gauss\n");
    // Implemente o Método de Gauss aqui
}

void GaussJordan() {
    printf("Opção selecionada: Método de Gauss-Jordan\n");
    // Implemente o Método de Gauss-Jordan aqui
}

void DecomposicaoLU() {
    printf("Opção selecionada: Método da Decomposição LU\n");
    // Implemente o Método da Decomposição LU aqui
}

void Jacobi() {
    printf("Opção selecionada: Método de Jacobi\n");
    // Implemente o Método de Jacobi aqui
}

void GaussSeidel() {
    printf("Opção selecionada: Método de Gauss-Seidel\n");
    // Implemente o Método de Gauss-Seidel aqui
}

void Determinante() {
    printf("Opção selecionada: Cálculo do determinante\n");
    // Implemente o cálculo do determinante aqui
}

void MatrizInversa() {
    printf("Opção selecionada: Cálculo da matriz inversa\n");
    // Implemente o cálculo da matriz inversa aqui
}

int main() {
    int opcao;

    do {

        printf("MENU PRINCIPAL\n");
        printf("******************************************************");
        printf("1. Ler sistema linear\n");
        printf("2. Escrever sistema linear\n");
        printf("3. Escrever solução do sistema linear\n");
        printf("4. Resolver sistema linear usando o Método de Gauss\n");
        printf("5. Resolver sistema linear usando o Método de Gauss-Jordan\n");
        printf("6. Resolver sistema linear usando o Método da Decomposição LU\n");
        printf("7. Resolver sistema linear usando o Método de Jacobi\n");
        printf("8. Resolver sistema linear usando o Método de Gauss-Seidel\n");
        printf("9. Calcular determinante de uma matriz\n");
        printf("10. Calcular matriz inversa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);


        switch (opcao) {
            case 1:
                LeituraSistema();
                break;
            case 2:
                EscritaSistema();
                break;
            case 3:
                EscritaSolucao();
                break;
            case 4:
                Gauss();
                break;
            case 5:
                GaussJordan();
                break;
            case 6:
                DecomposicaoLU();
                break;
            case 7:
                Jacobi();
                break;
            case 8:
                GaussSeidel();
                break;
            case 9:
                Determinante();
                break;
            case 10:
                MatrizInversa();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}