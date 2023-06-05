#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* 
		ALUNAS:
		EMINNY FERREIRA
		JÚLIA GRIMALDI
		ANA JÚLIA GASPAR
		LETICIA NAKAHARA   */


// 01 ROTINA DETERMINANTE  
int calculaDeterminante(int ordem, double** matriz) {
    int det = 0, sinal = 1;

    if (ordem == 1) {
        return matriz[0][0];
    }

    if (ordem == 2) {
        return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    }

    for (int i = 0; i < ordem; i++) {
        double** matriz_aux = (double**)malloc((ordem - 1) * sizeof(double*));
        for (int j = 0; j < ordem - 1; j++) {
            matriz_aux[j] = (double*)malloc((ordem - 1) * sizeof(double));
        }

        int aux_i = 0;
        for (int j = 1; j < ordem; j++) {
            int aux_j = 0;
            for (int k = 0; k < ordem; k++) {
                if (k != i) {
                    matriz_aux[aux_i][aux_j] = matriz[j][k];
                    aux_j++;
                }
            }
            aux_i++;
        }

        det = det + (sinal * matriz[0][i] * calculaDeterminante(ordem - 1, matriz_aux));
        sinal = -sinal;

        for (int j = 0; j < ordem - 1; j++) {
            free(matriz_aux[j]);
        }
        free(matriz_aux);
    }

    return det;
}


int DecomposicaoLU(int ordem, double** coeficientes) {
    double sol[ordem];
    int j, cont = 1;
    double termos[ordem];
    printf("Digite os termos:\n");
    for (j = 0; j < ordem; j++) {
        printf("[%d]:", j + 1);
        scanf("%lf", &termos[j]);
        printf("\n");
    }

    // Verificar convergencia
    int det; 
	int r;
    int i = 0;
    int L = 0;
    int U = 0;
    int p, q;
    double soma;
    double** Uij = (double**)malloc(ordem * sizeof(double*));
    double** Lij = (double**)malloc(ordem * sizeof(double*));
    double* y = (double*)malloc(ordem * sizeof(double));
    double* x = (double*)malloc(ordem * sizeof(double));
    for (i = 0; i < ordem; i++) {
        Uij[i] = (double*)malloc(ordem * sizeof(double));
        Lij[i] = (double*)malloc(ordem * sizeof(double));
    }
    
	i=0;

    do {
        if (i == 0) {
            det = coeficientes[0][0];
            printf("det A1 = %d\n", det);
        } 
		if (i == 1) {
            det = coeficientes[0][0] * coeficientes[1][1] - coeficientes[0][1] * coeficientes[1][0];
            printf("det A2 = %d\n", det);
    
        }
		if (i!=1 && i!=0){
            det = calculaDeterminante(ordem, coeficientes);
            printf("det A%d = %d\n", i+1, det);
        
        }
		
		
        if (det == 0) {
            printf("nao converge");
            return 0;
        }
        i++;

    }while (i < ordem && det > 0);

    // Determinar L e U

    do {
        printf("Resolvendo %d linha de U\n", U);
        for (p = U ; p < ordem; p++) {
            for (q = 0; q <=U - 1; q++) {
                soma = soma + (Lij[U][q] * Uij[q][p]);
                }
            if (U == 0) {
                Uij[U][p] = coeficientes[U][p];
                printf("Uij [%d] [%d] = %.4lf\n", U, p, Uij[U][p]);
                } 
			else {
                Uij[U][p] = coeficientes[U][p] - soma;
                printf("Uij [%d] [%d] = %.4lf\n", U, p, Uij[U][p]);
                }
            soma = 0;
          
			}
		U++;
        cont++;
		
		if(L==ordem-1){
			break;
		}
		else{
        printf("Resolvendo %d coluna de L\n", L);
        for (p = L+1; p < ordem; p++) {
            for (q = 0; q <=L - 1; q++) {
                soma = soma + Lij[p][q] * Uij[q][L];
                }
            if (L == 0) {
                Lij[p][L] = coeficientes[p][L] / Uij[L][L];
                printf("Lij [%d] [%d] = %.4lf\n", p, L, Lij[p][L]);
            } else {
                Lij[p][L] = (coeficientes[p][L] - soma) / Uij[L][L];
                printf("Lij [%d] [%d] = %.4lf\n", p, L, Lij[p][L]);
                soma = 0;
                }
            }
            L++;
        }
    } while (cont <=ordem);

    // Resolver sistema triangular
    printf("\nResolvendo sistema triangular:\n");

    int t = 0;

    do {  // Ly=b
        if (t == 0) {
            y[t] = termos[t] / 1;
        } 
		else {
            for (q = 0; q <= t - 1; q++) {
                if (t > q) {
                    soma = soma + Lij[t][q] * y[q];
                }
            }
            y[t] = (termos[t] - soma) / 1;
            soma = 0;
        }
        t++;
    } while (t < ordem);
	soma=0;
    t = ordem-1;
    do {  // Ux=y
        if (t == ordem-1) {
            x[t] = y[t] / Uij[t][t];//qnd xo e x1 são 0
        } 
		else {
            for (q = t + 1; q <ordem; q++) {
                soma = soma + Uij[t][q] * x[q];
            
            }
            x[t] = (y[t] - soma) / Uij[t][t];
            soma = 0;
        }
        t--;
    } while (t < ordem && t >=0);

    for (r = 0; r < ordem; r++) {
        sol[r] = x[r];
        printf("\nx[%d]= %.4lf\n",r, sol[r]);
    }

    // liberar memória
    for (i = 0; i < ordem; i++) {
        free(Uij[i]);
        free(Lij[i]);
    }
    free(Uij);
    free(Lij);
    free(y);
    free(x);
}

void cholesky(int ordem, double** coeficientes) {
    int i, j, k;
    double *sol, *termos, soma = 0.0;
    int det;
    printf("Digite os termos:\n");
    termos = (double*)malloc(ordem * sizeof(double));
    for (j = 0; j < ordem; j++) {
        printf("[%d]:", j);
        scanf("%lf", &termos[j]);
        printf("\n");
    }
    
    double* y = (double*)malloc(ordem * sizeof(double));
    double** transposta = (double**)malloc(ordem * sizeof(double*));
    double** L = (double**)malloc(ordem * sizeof(double*));

    for (i = 0; i < ordem; i++) {
        L[i] = (double*)malloc(ordem * sizeof(double));
        transposta[i] = (double*)malloc(ordem * sizeof(double));
    }

    i = 0;
    do {
        if (i == 0) {
            det = coeficientes[0][0];
            printf("det A1 = %d\n", det);
        } if (i == 1) {
            det = coeficientes[0][0] * coeficientes[1][1] - coeficientes[0][1] * coeficientes[1][0];
            printf("det A2 = %d\n", det);
        } 
		if (i!=1 && i!=0){
            det = calculaDeterminante(ordem, coeficientes);
            printf("det A%d = %d\n", i+1, det);
        
        }

        if (det == 0) {
            printf("nao converge.\n");
            return;
        }
        i++;
    } while (i < ordem && det != 0);

    printf("\nResolvendo matriz L:\n");

    // Definir a matriz L
    for (j = 0; j < ordem; j++) { // coluna
        for (i = 0; i < ordem; i++) {
            if (i >= j) {
                if (i == j) {
                    for (k = 0; k < i; k++) {
                        soma = soma + pow(L[i][k], 2);
                    }
                    if (i == 0 && j == 0) {
                        L[i][j] = sqrt(coeficientes[i][j]);
                        printf("L[%d][%d] = %.4lf\n", i, j, L[i][j]);
                    } else {
                        L[i][j] = sqrt(coeficientes[i][j] - soma);
                        printf("L[%d][%d] = %.4lf\n", i, j, L[i][j]);
                    }
                    soma = 0;
                } else {
                    soma = 0;
                    for (k = 0; k < j; k++) {
                        soma = soma + L[i][k] * L[j][k];
                    }
                    if (coeficientes[i][j] == 0 && soma == 0) {
                        L[i][j] = 0;
                        printf("L[%d][%d] = %.4lf\n", i, j, L[i][j]);
                    } else {
                        L[i][j] = (coeficientes[i][j] - soma) / L[j][j];
                        printf("L[%d][%d] = %.4lf\n", i, j, L[i][j]);
                    }
                }
            } else {
                L[i][j] = 0;
            }
        }
    }

    // Matriz transposta
    for (int l = 0; l < ordem; l++) {
        for (int c = 0; c < ordem; c++) {
                transposta[c][l]=  L[l][c];
            	printf("\ntransposta: [%d][%d] = %lf\n", c,l, transposta[c][l]);
            
        }
    }

    // Resolver sistema triangular Ly = b
    printf("\nResolvendo sistema triangular:\n");

    for (i = 0; i < ordem; i++) {
        if (i == 0) {
            y[i] = termos[i] / L[i][i];
        } else {
            soma = 0;
            for (j = 0; j < i; j++) {
                soma += L[i][j] * y[j];
            }
            y[i] = (termos[i] - soma) / L[i][i];
        }
        printf("y[%d] = %.4lf\n", i, y[i]);
    }

    // Resolver sistema triangular Ux = y
    printf("\nResolvendo sistema triangular:\n");

    sol = (double*)malloc(ordem * sizeof(double));
    for (i = ordem - 1; i >= 0; i--) {
        if (i == ordem - 1) {
            sol[i] = y[i] / transposta[i][i];
        } else {
            soma = 0;
            for (j = i + 1; j < ordem; j++) {
                soma += transposta[i][j] * sol[j];
            }
            sol[i] = (y[i] - soma) / transposta[i][i];
        }
        printf("x[%d] = %.4lf\n", i, sol[i]);
    }

    // Liberar memória
    for (i = 0; i < ordem; i++) {
        free(L[i]);
        free(transposta[i]);
    }
    free(L);
    free(transposta);
    free(y);
    free(sol);
    free(termos);
}

void imprimirMatriz(int ordem, double** matriz) {
    printf("    Matriz %dx%d: \n\n", ordem,ordem);
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%lf\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void exibeDeterminante(int ordem, double** matriz) {
	
	system ("cls"); 
    imprimirMatriz(ordem, matriz);
    int determinante = calculaDeterminante(ordem, matriz);
    printf ("\n"); 
	printf("Determinante: %d\n", determinante);
	printf ("\n"); 
	
    for (int i = 0; i < ordem; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
}


// 02 ROTINA SistemaTriangularInferior 
void triangularInferior(int tam, double** matriz, double* b, double* x) {
    x[0] = b[0] / matriz[0][0];

    for (int i = 1; i < tam; i++) {
        double soma = 0.0;
        for (int j = 0; j < i; j++) {
            soma += matriz[i][j] * x[j];
        }
        x[i] = (b[i] - soma) / matriz[i][i];
    }
}
//03 ROTINA SistemaTriangularSuperior
void triangularSuperior(int tam, double** matriz, double* b, double* x) {
    x[tam-1] = b[tam-1] / matriz[tam-1][tam-1];

    for (int i = tam-2; i >= 0; i--) {
        double soma = 0.0;
        for (int j = i+1; j < tam; j++) {
            soma += matriz[i][j] * x[j];
        }
        x[i] = (b[i] - soma) / matriz[i][i];
    }
}

void imprimirSolucao(int tam, double* x) {
    printf("Solucao:\n");
    for (int i = 0; i < tam; i++) {
        printf("x%d = %.2lf\n", i+1, x[i]);
    }
}

void trocarLinhas(double** matriz, int linha1, int linha2, int colunas) {
    for (int i = 0; i < colunas; i++) {
        double temp = matriz[linha1][i];
        matriz[linha1][i] = matriz[linha2][i];
        matriz[linha2][i] = temp;
    }
}

void escalonarLinha(double** matriz, int linha, double fator, int colunas) {
    for (int i = 0; i < colunas; i++) {
        matriz[linha][i] *= fator;
    }
}

void subtrairLinhas(double** matriz, int linha1, int linha2, double fator, int colunas) {
    for (int i = 0; i < colunas; i++) {
        matriz[linha1][i] -= fator * matriz[linha2][i];
    }
}

int gaussJordan(int ordem, double** matriz, double* vetor) {
    double determinante = 1.0;
    for (int k = 0; k < ordem - 1; k++) {
        if (matriz[k][k] == 0) {
            printf("Erro: O sistema nao possui solucao unica.\n");
            return 0;
        }
        determinante *= matriz[k][k];
    }

    // Gauss-Jordan
    for (int k = 0; k < ordem; k++) {
        // Verifica pivô
        if (matriz[k][k] == 0) {
            printf("Erro: O sistema nao possui solucao unica.\n");
            return 0;
        }

        // Escalona o pivô para 1
        double pivo = matriz[k][k];
        escalonarLinha(matriz, k, 1.0 / pivo, ordem);
        vetor[k] /= pivo;

        // Zera os elementos acima e abaixo do pivô
        for (int i = 0; i < ordem; i++) {
            if (i != k) {
                double fator = matriz[i][k];
                subtrairLinhas(matriz, i, k, fator, ordem);
                vetor[i] -= fator * vetor[k];
            }
        }
    }

    return 1;
}

void gaussCompacto(int ordem, double **coeficientes) {
  double det;
double soma;
double *termos, *solucao;
int i, j, k, t, U, L=0, cont = 0;
double **aux, **Uij, **Lij;
double *y, *x, *sol;
aux = (double**)malloc((ordem+1) * sizeof(double*));
for (i = 0; i < ordem+1; i++) {
    aux[i] = (double*)malloc((ordem+1) * sizeof(double));
}
Uij = (double**)malloc(ordem * sizeof(double*));
for (i = 0; i < ordem; i++) {
    Uij[i] = (double*)malloc(ordem * sizeof(double));
}
Lij = (double**)malloc(ordem * sizeof(double*));
for (i = 0; i < ordem; i++) {
    Lij[i] = (double*)malloc(ordem * sizeof(double));
}
termos = (double*)malloc(ordem * sizeof(double));
y = (double*)malloc(ordem * sizeof(double));
x = (double*)malloc(ordem * sizeof(double));
sol = (double*)malloc(ordem * sizeof(double));

    printf("Digite os termos:\n");
    termos = (double *)malloc(ordem * sizeof(double));
    for (j = 0; j < ordem; j++) {
        printf("[%d]:", j);
        scanf("%lf", &termos[j]);
        printf("\n");
    }

    i = 0;
    do {
        if (i == 0) {
            det = coeficientes[0][0];
            printf("det A1 = %lf\n", det);
        } else if (i == 1) {
            det = coeficientes[0][0] * coeficientes[1][1] - coeficientes[0][1] * coeficientes[1][0];
            printf("det A2 = %lf\n", det);
        } else {
            det = calculaDeterminante(ordem, coeficientes);
            printf("det A%d = %lf\n", i + 1, det);
        }

        if (det == 0) {
            printf("nao converge.\n");
            return;
        }
        i++;
    } while (i < ordem && det != 0);

	printf("Montagem da matriz ampliada\n");
    for (int l = 0; l < ordem ; l++) {
        for (int c = 0; c < ordem + 1; c++) {
            if (c == ordem) {
                aux[l][c] = termos[l];
                printf("aux[%d][%d]= %lf\n", l, c, termos[l]);
            } else {
                aux[l][c] = coeficientes[l][c];
                printf("aux[%d][%d]= %lf\n", l, c, coeficientes[l][c]);
            }
        }
    }
	U=0;
    do {
        printf("Resolvendo %d linha de U\n", U);
        for (int p = U; p <=ordem; p++) {
            soma = 0;
            for (int q = 0; q <= U - 1; q++) {
                soma += Lij[U][q] * Uij[q][p];
            }
            if (U == 0) {
                Uij[U][p] = aux[U][p];
                printf("Uij [%d] [%d] = %.4lf\n", U, p, Uij[U][p]);
            } else {
                Uij[U][p] = aux[U][p] - soma;
                printf("Uij [%d] [%d] = %.4lf\n", U, p, Uij[U][p]);
            }
        }
        U++;
        cont++;
		
        if (L == ordem) {
            break;
        } else {
            printf("Resolvendo %d coluna de L\n", L);
            for (int p = L + 1; p < ordem; p++) {
                soma = 0;
                for (int q = 0; q <= L - 1; q++) {
                    soma += Lij[p][q] * Uij[q][L];
                }
                if (L == 0) {
                    Lij[p][L] = aux[p][L] / Uij[L][L];
                    printf("Lij [%d] [%d] = %.4lf\n", p, L, Lij[p][L]);
                } else {
                    Lij[p][L] = (aux[p][L] - soma) / Uij[L][L];
                    printf("Lij [%d] [%d] = %.4lf\n", p, L, Lij[p][L]);
                    soma = 0;
                }
            }
            L++;
        }
    } while (cont < ordem);

    for (int k = 0; k < ordem; k++) {
        y[k] = Uij[k][ordem];
        printf("\n\n%lf\n\n", y[k]);
    }

    printf("Resolvendo sistema triangular\n");
    soma = 0;
    t = ordem - 1;
    do {  // Ux=y
        if (t == ordem - 1) {
            x[t] = y[t] / Uij[t][t];
        } else {
            for (int q = t + 1; q < ordem; q++) {
                soma += Uij[t][q] * x[q];
            }
            x[t] = (y[t] - soma) / Uij[t][t];
            soma = 0;
        }
        t--;
    } while (t >= 0);

    for (int r = 0; r < ordem; r++) {
        sol[r] = x[r];
        printf("\nx[%d]= %.4lf\n", r, sol[r]);
    }
}

void GaussSeidel(int ordem, double** matriz, double* vetor, double* aproximacao, double precisao, int maxIteracoes, double* solucao, int* numIteracoes) {
    printf("Implementando o Metodo de Gauss-Seidel...\n");
    // Verificação da diagonal dominância estrita
    for (int i = 1; i <= ordem; i++) {
        double soma = 0.0;
        double diagonal = fabs(matriz[i][i]);

        for (int j = 1; j <= ordem; j++) {
            if (j != i) {
                soma += fabs(matriz[i][j]);
            }
        }

        if (diagonal <= soma) {
            printf("A matriz de coeficientes nao satisfaz a diagonal dominancia estrita.\n");
            printf("O metodo de Gauss-Seidel pode nao convergir corretamente.\n");
            return;
        }
    }

    // Implementação do Método de Gauss-Seidel
    int iteracao = 0;
    double norma = 0.0;
    double normaAnterior = 0.0;

    do {
        normaAnterior = norma;
        norma = 0.0;

        for (int i = 1; i <= ordem; i++) {
            double soma = 0.0;

            for (int j = 1; j <= ordem; j++) {
                if (j != i) {
                    soma += matriz[i][j] * solucao[j];
                }
            }

            solucao[i] = (vetor[i] - soma) / matriz[i][i];

            double diferenca = solucao[i] - aproximacao[i];
            norma += diferenca * diferenca;
        }

        norma = sqrt(norma);
        iteracao++;
    } while (norma > precisao && iteracao < maxIteracoes);

    // Atribuição da solucao e numero de iteracoes
    for (int i = 1; i <= ordem; i++) {
        aproximacao[i] = solucao[i];
    }
    *numIteracoes = iteracao;

    // Exibicao da solucao
    printf("\nSolucao do sistema linear:\n");
    for (int i = 1; i <= ordem; i++) {
        printf("x[%d] = %.4f\n", i, solucao[i]);
    }
}


void MatrizInversa() {
    printf("Opcao selecionada: Calculo da matriz inversa\n");

    // Implementação do cálculo da matriz inversa
    int n;
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);

    double matriz[n][n];
    double identidade[n][n];

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Digite o elemento [%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }

    // Verificação se a matriz é quadrada
    if (n <= 0) {
        printf("Erro: a matriz deve ser quadrada!\n");
        return;
    }

    // Inicialização da matriz identidade
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                identidade[i][j] = 1.0;
            } else {
                identidade[i][j] = 0.0;
            }
        }
    }

    // Cálculo da matriz inversa usando o método da decomposição LU
    double aux;
    for (int k = 0; k < n; k++) {
        aux = matriz[k][k];
        for (int j = 0; j < n; j++) {
            matriz[k][j] /= aux;
            identidade[k][j] /= aux;
        }
        for (int i = 0; i < n; i++) {
            if (i != k) {
                aux = matriz[i][k];
                for (int j = 0; j < n; j++) {
                    matriz[i][j] -= matriz[k][j] * aux;
                    identidade[i][j] -= identidade[k][j] * aux;
                }
            }
        }
    }

    // Exibição da matriz inversa
    printf("\nMatriz inversa:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.4f ", identidade[i][j]);
        }
        printf("\n");
    }
}

void Jacobi(int ordem, double** matriz, double* vetor, double* aproximacao, float precisao, double* solucao, int* numIteracoes) {
    int iteracao = 0;
    double norma = 0.0;
    double normaAnterior = 0.0;

    do {
        normaAnterior = norma;
        norma = 0.0;

        for (int i = 1; i <= ordem; i++) {
            solucao[i] = vetor[i];

            for (int j = 1; j <= ordem; j++) {
                if (j != i) {
                    solucao[i] -= matriz[i][j] * aproximacao[j];
                }
            }

            solucao[i] /= matriz[i][i];

            double diferenca = solucao[i] - aproximacao[i];
            norma += diferenca * diferenca;
        }

        norma = sqrt(norma);
        iteracao++;
    } while (norma > precisao && iteracao < 100);

    // Atribuição da solução e número de iterações
    for (int i = 1; i <= ordem; i++) {
        aproximacao[i] = solucao[i];
    }
    *numIteracoes = iteracao;

    printf("\nSolucao do sistema linear:\n");
    for (int i = 1; i <= ordem; i++) {
        printf("x[%d] = %.4f\n", i, solucao[i]);
    }
}

int main() {
    int escolha = 0;
    int tam;
    double** matriz;
    double* b;
    double* x;
    int ordem;

    while (1) {
    	printf("\n\n");
        printf("---------------------- MENU ---------------------- \n\n");
        printf("1. Calcular determinante de uma matriz\n");
        printf("2. Resolver sistema triangular inferior\n");
        printf("3. Resolver sistema triangular superior\n");
        printf("4. Resolver sistema usando o metodo de Decomposicao LU\n");
        printf("5. Resolver sistema usando o metodo de Cholesky\n");
        printf("6. Resolver sistema usando o metodo de Gauss-Jordan\n");
        printf("7. Resolver sistema usando o metodo de Gauss-Compacto\n");
        printf("8. Resolver sistema usando o metodo de Gauss-Seidel\n");
        printf("9. Resolver sistema usando o metodo de Gauss-Jacobi\n");
        printf("10. Resolver Matriz inversa\n");
        printf("11. Sair\n\n");
        printf("--------------------------------------------------\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1: {
                printf("Digite a ordem da matriz: ");
                scanf("%d", &ordem);
                printf("\n");
                matriz = (double**)malloc(ordem * sizeof(double*));
                for (int i = 0; i < ordem; i++) {
                    matriz[i] = (double*)malloc(ordem * sizeof(double));
                    for (int j = 0; j < ordem; j++) {
                        printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                        scanf("%lf", &matriz[i][j]);
                    }
                }
                exibeDeterminante(ordem, matriz);

                char resposta;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta);
				system ("cls");
                if (resposta == 's' || resposta == 'S') {
                } else {
                    printf("\n");
                    printf("Saindo...\n");
                    exit(0);
                }
                break;
			}
            case 2: {
		
                printf("Digite o tamanho da matriz triangular inferior: ");
                scanf("%d", &tam);
				
                matriz = (double**)malloc(tam * sizeof(double*));
                for (int i = 0; i < tam; i++) {
                    matriz[i] = (double*)malloc(tam * sizeof(double));
                }

                b = (double*)malloc(tam * sizeof(double));
                x = (double*)malloc(tam * sizeof(double));
				
				printf("\n");
                printf("Digite os elementos da matriz triangular inferior:\n");
                printf ("\n");
                for (int i = 0; i < tam; i++) {
                    for (int j = 0; j < tam; j++) {
                        if (j <= i) {
                            printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                            scanf("%lf", &matriz[i][j]);
                        } else {
                            matriz[i][j] = 0.0;
                        }
                    }
                }
                printf ("\n");
                printf("Digite os elementos do vetor b:\n");
                for (int i = 0; i < tam; i++) {
                    scanf("%lf", &b[i]);
                }

                triangularInferior(tam, matriz, b, x);
                printf("\nSistema resolvido.\n\n");
                imprimirSolucao(tam, x);

                for (int i = 0; i < tam; i++) {
                    free(matriz[i]);
                }
                free(matriz);
                free(b);
                free(x);

                char resposta_2;
                printf("\n");
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_2);

                if (resposta_2 == 's' || resposta_2 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }
                break;
			}
            case 3: {
			
                printf("Digite o tamanho da matriz triangular superior: ");
                scanf("%d", &tam);

                matriz = (double**)malloc(tam * sizeof(double*));
                for (int i = 0; i < tam; i++) {
                    matriz[i] = (double*)malloc(tam * sizeof(double));
                }

                b = (double*)malloc(tam * sizeof(double));
                x = (double*)malloc(tam * sizeof(double));
                
				printf("\n");
                printf("Digite os elementos da matriz triangular superior:\n\n");
                for (int i = 0; i < tam; i++) {
                    for (int j = 0; j < tam; j++) {
                        if (j >= i) {
                        
                            printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                            scanf("%lf", &matriz[i][j]);
                        } else {
                            matriz[i][j] = 0.0;
                        }
                    }
                }
				printf("\n");
                printf("Digite os elementos do vetor b:\n");
                for (int i = 0; i < tam; i++) {
                    scanf("%lf", &b[i]);
                }

                triangularSuperior(tam, matriz, b, x);
                printf("Sistema resolvido.\n\n");
                imprimirSolucao(tam, x);

                for (int i = 0; i < tam; i++) {
                    free(matriz[i]);
                }
                free(matriz);
                free(b);
                free(x);

                char resposta_3;
                printf("\n");
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_3);

                if (resposta_3 == 's' || resposta_3 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }

                break;
			}
            case 4: {
			
                printf("Digite a ordem da matriz: ");
                scanf("%d", &ordem);

                matriz = (double**)malloc(ordem * sizeof(double*));
                for (int i = 0; i < ordem; i++) {
                    matriz[i] = (double*)malloc(ordem * sizeof(double));
                }

                printf("Digite os elementos da matriz:\n");
                for (int i = 0; i < ordem; i++) {
                    for (int j = 0; j < ordem; j++) {
                        printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                        scanf("%lf", &matriz[i][j]);
                    }
                }

                DecomposicaoLU(ordem, matriz);
                char resposta_4;
                printf("\n");
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_4);

                if (resposta_4 == 's' || resposta_4 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }

                break;
}
            case 5:{
			
                printf("Digite a ordem da matriz: ");
                scanf("%d", &ordem);

                matriz = (double**)malloc(ordem * sizeof(double*));
                for (int i = 0; i < ordem; i++) {
                    matriz[i] = (double*)malloc(ordem * sizeof(double));
                }

                printf("Digite os elementos da matriz:\n");
                for (int i = 0; i < ordem; i++) {
                    for (int j = 0; j < ordem; j++) {
                        printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                        scanf("%lf", &matriz[i][j]);
                    }
                }

                cholesky(ordem, matriz);
                char resposta_5;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_5);

                if (resposta_5 == 's' || resposta_5 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }

                break;
}
            case 6:{
			
                double* vetor;
                printf("Digite a ordem do sistema: ");
                scanf("%d", &ordem);

                matriz = (double**)malloc(ordem * sizeof(double*));
                vetor = (double*)malloc(ordem * sizeof(double));
                for (int i = 0; i < ordem; i++) {
                    matriz[i] = (double*)malloc(ordem * sizeof(double));
                    for (int j = 0; j < ordem; j++) {
                        printf("Digite o coeficiente da linha %d, coluna %d: ", i + 1, j + 1);
                        scanf("%lf", &matriz[i][j]);
                    }
                    printf("Digite o termo independente da linha %d: ", i + 1);
                    scanf("%lf", &vetor[i]);
                }

                // Verifica convergência e resolve com Gauss-Jordan
                int convergente = gaussJordan(ordem, matriz, vetor);
                if (convergente) {
                    printf("Solucao:\n");
                    for (int i = 0; i < ordem; i++) {
                        printf("x%d = %.2lf\n", i + 1, vetor[i]);
                    }
                }

                for (int i = 0; i < ordem; i++) {
                    free(matriz[i]);
                }
                free(matriz);
                free(vetor);
                char resposta_6;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_6);

                if (resposta_6 == 's' || resposta_6 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }
                break;
                break;
}

			case 7: {
				printf("Digite a ordem da matriz: ");
                scanf("%d", &ordem);

                matriz = (double**)malloc(ordem * sizeof(double*));
                for (int i = 0; i < ordem; i++) {
                    matriz[i] = (double*)malloc(ordem * sizeof(double));
                }

                printf("Digite os elementos da matriz:\n");
                for (int i = 0; i < ordem; i++) {
                    for (int j = 0; j < ordem; j++) {
                        printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
                        scanf("%lf", &matriz[i][j]);
                    }
                }
				gaussCompacto(ordem, matriz);
				char resposta_7;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_7);

                if (resposta_7 == 's' || resposta_7 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }

				break;
			}
			case 8:{
				int ordem;
		    printf("Digite o tamanho da matriz: ");
		    scanf("%d", &ordem);
		
		    // Alocação dinâmica da matriz
		    matriz = (double**)malloc((ordem + 1) * sizeof(double*));
		    for (int i = 1; i <= ordem; i++) {
		        matriz[i] = (double*)malloc((ordem + 1) * sizeof(double));
		    }
		
		    double* vetor = (double*)malloc((ordem + 1) * sizeof(double));
		    double* aproximacao = (double*)malloc((ordem + 1) * sizeof(double));
		
		    printf("Digite os elementos da matriz:\n");
		    for (int i = 1; i <= ordem; i++) {
		        for (int j = 1; j <= ordem; j++) {
		            printf("Digite o elemento [%d][%d]: ", i, j);
		            scanf("%lf", &matriz[i][j]);
		        }
		    }
		
		    printf("Digite os elementos do vetor:\n");
		    for (int i = 1; i <= ordem; i++) {
		        printf("Digite o elemento [%d]: ", i);
		        scanf("%lf", &vetor[i]);
		    }
		
		    printf("Digite a aproximação inicial:\n");
		    for (int i = 1; i <= ordem; i++) {
		        printf("Digite o elemento X[%d]: ", i);
		        scanf("%lf", &aproximacao[i]);
		    }
		
		    double precisao;
		    printf("Digite o criterio de precisao: ");
		    scanf("%lf", &precisao);
		
		    int maxIteracoes;
		    printf("Digite o numero maximo de iteracoes: ");
		    scanf("%d", &maxIteracoes);
		
		    double* solucao = (double*)malloc((ordem + 1) * sizeof(double));
		    int numIteracoes = 0;  // Inicialização da variável numIteracoes
		
		    GaussSeidel(ordem, matriz, vetor, aproximacao, precisao, maxIteracoes, solucao, &numIteracoes);
		
		    printf("\nNumero de iteracoes realizadas: %d\n", numIteracoes);
		
		    // Liberação da memória alocada
		    for (int i = 1; i <= ordem; i++) {
		        free(matriz[i]);
		    }
		    free(matriz);
		    free(vetor);
		    free(aproximacao);
		    free(solucao);
	
		    char resposta_8;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_8);

                if (resposta_8 == 's' || resposta_8 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }
    
			break;
			}
			
			case 9:{
				int ordem;
                system("cls");
                printf("Digite o tamanho da matriz: ");
                scanf("%d", &ordem);

                // Alocação dinâmica da matriz
                double** matriz = (double**)malloc((ordem + 1) * sizeof(double*));
                for (int i = 1; i <= ordem; i++) {
                    matriz[i] = (double*)malloc((ordem + 1) * sizeof(double));
                }

                double* vetor = (double*)malloc((ordem + 1) * sizeof(double));
                double* aproximacao = (double*)malloc((ordem + 1) * sizeof(double));
				
				printf ("\n");
                printf("Digite os elementos da matriz:\n\n");
                for (int i = 1; i <= ordem; i++) {
                    for (int j = 1; j <= ordem; j++) {
                        printf("Digite o elemento [%d][%d]: ", i, j);
                        scanf("%lf", &matriz[i][j]);
                    }
                }
				printf ("\n");
                printf("Digite os elementos do vetor:\n\n");
                for (int i = 1; i <= ordem; i++) {
                    printf("Digite o elemento [%d]: ", i);
                    scanf("%lf", &vetor[i]);
                }
				printf ("\n");
                printf("Digite a aproximacao inicial:\n\n");
                for (int i = 1; i <= ordem; i++) {
                    printf("Digite o elemento X[%d]: ", i);
                    scanf("%lf", &aproximacao[i]);
                }

                float precisao;
                printf ("\n");
                printf("Digite o criterio de precisao: ");
                scanf("%f", &precisao);

                int numIteracoes;
                double* solucao = (double*)malloc((ordem + 1) * sizeof(double));

                Jacobi(ordem, matriz, vetor, aproximacao, precisao, solucao, &numIteracoes);

                printf("\nNumero de iteracoes realizadas: %d\n", numIteracoes);
				
                // Liberação da memória alocada
                for (int i = 1; i <= ordem; i++) {
                    free(matriz[i]);
                }
                free(matriz);
                free(vetor);
                free(aproximacao);
                free(solucao);
                char resposta_9;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_9);

                if (resposta_9 == 's' || resposta_9 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }
                break;

                break;
			}
			
			case 10:{
				MatrizInversa();
				char resposta_10;
                printf("Deseja retornar ao menu? (s/n): ");
                scanf(" %c", &resposta_10);

                if (resposta_10 == 's' || resposta_10 == 'S') {
                    system("cls");
                } else {
                    printf("Saindo...\n");
                    exit(0);
                }
                break;
				break;
			}
			
			
            case 11:{
                printf("\n");
                printf("Saindo...\n");
                return 0;
	}
            default:{
			
                printf("\n");
                printf("Opcao invalida!\n");
                break;}
        }
    }

    return 0;
}

