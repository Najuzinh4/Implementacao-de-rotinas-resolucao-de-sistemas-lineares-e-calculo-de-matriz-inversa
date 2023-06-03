#include <stdio.h>
#include <stdlib.h> 

// Implementação das rotinas <3 
int calculaDeterminante(int ordem, double matriz[ordem][ordem]) {
    int det = 0;
	int sinal;
	int r;
    int i, j, k;
    if (ordem == 2) {
        det = (matriz[1][1] * matriz[2][2]) - (matriz[1][2] * matriz[2][1]);
    }
    else{

    for (i = 1; i <= ordem; i++) {
        if (i % 2 == 0) {
            sinal = 1;
        } else {
            sinal = -1;
        }

        double matriz_aux[ordem - 1][ordem - 1];
        int aux_i = 1;
        
		int aux_j = 1;
        // Criando a matriz auxiliar// colocar aux_j =0
        for (j = 2; j <= ordem; j++) {
            for ( k = 1; k <= ordem; k++) {
                if (k != i) {
                    matriz_aux[aux_i][aux_j] = matriz[j][k];
                    aux_j++;
                }
            }
            aux_i++;
            int aux_j = 1;
        }
		r = calculaDeterminante(ordem - 1, matriz_aux);
        det = det + (sinal * matriz[1][i] * r);

    }
}

    return det;
}



void exibeDeterminante(int ordem, double matriz[ordem][ordem]) {

    int determinante = calculaDeterminante(ordem, matriz);
    printf("Determinante: %d\n", determinante);
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

int DecomposicaoLU(int ordem, double coeficientes[ordem][ordem]){
	double *sol[ordem];
	int j;
	double termos[ordem];
	printf("digite os termos:\n");
	for(j=1; j<=ordem; j++){
		printf("[%d]:",j);
		scanf("%lf", &termos[j]);
		printf("\n");
	}
	
	//verificar convergencia
	int det, r;
	int i=1;
	int L=1, U=1;
	int p,q,soma;
	double Uij[ordem][ordem], Lij[ordem][ordem];
	int t=1, y[ordem], x[ordem];
	do{
	if(i==1){
		det=coeficientes[1][1];
		printf("det A1 = %d\n", det);
	}
	if(i==2){
	det=(coeficientes[1][1]*coeficientes[2][2]-coeficientes[1][2]*coeficientes[2][1]);
	printf("det A2 = %d\n", det);
}
	if(i!= 1 && i!= 2){
		det = calculaDeterminante(ordem, coeficientes);
		printf("det A%d = %d\n", i, det);
	}
	
	if(det==0){
		printf("nao converge");
		return 0;
	}
	i++;
	
	}while(i<=ordem && det !=0);
	
	//determinar L e U
	
	do{
		do{
		printf("%d linha de U", U);
		for(p=U; p<=ordem; p++){
			for(q=1; q<=U-1; q++){
				soma= soma + (Lij[U][q] * Uij[q][p]);
			} 
			Uij[U][p]= coeficientes[U][p] - soma;
			soma=0;
		}
		U++;
	}while (U<=ordem);
	
		do{
		printf("%d coluna de L", &L);
		for(p=L+1; p<=ordem; p++){
			for(q=1; q<=L-1; q++){
				soma= soma + Lij[p][q] * Uij[q][L];
			}
			
			Lij[p][L]= (coeficientes[p][L] - soma)/ Uij[L][L];
			soma=0;
		}
		L++;
	}while (U<=ordem);
}while(U != ordem || U == ordem);

//resolver sistema triangular

do{//Ly=b
	if(t=1){
		y[t]= termos[t]/1;
	}
	else{
		for(q=1; q<=t-1; q++){
			if(t>q){
				soma=soma + Lij[t][q]*y[q];
			}
		}
		y[t]=(termos[t]-soma)/1;
		soma=0;
	}
	t++;
}while(t != ordem || t == ordem);

t=1;
do{//Ux=y
	if(t=ordem){
		x[t]= termos[t]/Uij[t][t];
	}
	else{
		for(q=t+1; q<=ordem; q++){
			if(t<=q){
				soma=soma + Uij[t][q]*x[q];
			}

		}
		x[t]=(termos[t]-soma)/Uij[t][t];
		soma=0;
	}
	t++;
}while(t != ordem || t == ordem);

for(r=1; r<=ordem; r++){
	*sol[r]=x[r];
}
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
    int ordem;
	int i, j;
    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);
    double matriz[ordem][ordem];

    printf("Digite os elementos da matriz:\n");
    for (i = 1; i <= ordem; i++) {
        for (j = 1; j <= ordem; j++) {
            printf("Digite o elemento [%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }
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