#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix {
	int tamanho;
	float *matA;
	float *matB;
	float *matC;
};

float* ler_matriz(char n, char *arquivo) {
	FILE *f = fopen(arquivo, "r"); //abre arquivo con nome dado no segundo argumento em modo leitura
	if (f == 0) { //checa se o arquivo foi aberto com sucesso
   		printf("Erro: nao foi possivel abrir arquivo!");
   		exit(0);
   	}

	printf("Lendo matriz%c de %s\n", n, arquivo);
	int i, j, tam;
	fscanf(f, "%d\n", &tam); //lê o tamanho da matriz do arquivo
  	float *matriz = (float *) malloc(tam * tam * sizeof(float)); //aloca memoria para a matriz

  	for (i = 0; i < tam; i++) {
   		for (j = 0; j < tam; j++) {
       		if (!fscanf(f, "%f:", &matriz[i*tam + j])) //lê a matriz do arquivo
       			break;
   		}
  	}

	fclose(f); //fecha o arquivo
	return matriz;
}

int ler_tamanho_matriz(char *arquivo) {
	FILE *f = fopen(arquivo, "r"); //abre arquivo con nome dado no segundo argumento em modo leitura
	if (f == 0) { //checa se o arquivo foi aberto com sucesso
   		printf("Erro: nao foi possivel abrir arquivo!");
   		exit(0);
   	}

	int tamanho;
	fscanf(f, "%d\n", &tamanho); //lê o tamanho da matriz do arquivo
	fclose(f); //fecha o arquivo
	return tamanho;
}

int main(int argc, char *argv[]) {
	//para exibir o tempo real de execução
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	//checa se os argumentos com o nome dos arquivos foram inseridos na execução
	if(argc != 4){
		printf("Argumentos insuficientes. Insira os arquivos contendo as matrizes e o arquivo em que sera salvo o resultado da multiplicação.\n");
		return 2;
	}

	float soma = 0; //para a mutiplicação das matrizes
	int i, j, k; //para armazenar o tamanho das matrizes
	struct matrix matrizes;
		matrizes.tamanho = matrizes.tamanho = ler_tamanho_matriz(argv[1]); //lê o tamanho da matriz resultado do arquivo
  		matrizes.matA = ler_matriz('A', argv[1]); //lê matrizA
  		matrizes.matB = ler_matriz('B', argv[2]); //lê matrizB
		matrizes.matC = (float *) malloc(matrizes.tamanho * matrizes.tamanho * sizeof(float)); //aloca memoria para matrizC

	FILE *f = fopen(argv[3], "w"); //abre ou cria o arquivo com o nome do quarto argumento

	fprintf(f, "%d\n", matrizes.tamanho); //armazena o tamanho da matriz no arquivo
	printf("Tamanho da matriz %d salvo no arquivo.\n", matrizes.tamanho);
	printf("Calculando o produto de Matrizes...\n");

	for (i = 0; i < matrizes.tamanho; i++) {
		for(j = 0; j < matrizes.tamanho; j++) {
			soma = 0;
			for(k = 0; k < matrizes.tamanho; k++) {
				soma += matrizes.matA[i*matrizes.tamanho + k] * matrizes.matB[k + j*matrizes.tamanho];
			}
			matrizes.matC[i*matrizes.tamanho + j] = soma; //guarda o valor da multiplicação na matriz c
			fprintf(f, "%.1f:", matrizes.matC[i*matrizes.tamanho + j]); //armazena o resultado no arquivo
		}
		fprintf(f, "\n");
	}

	printf("Matriz Resultante salva em %s\n", argv[3]);
	fclose(f); //fecha o arquivo
	printf("Arquivo %s fechado.\n", argv[3]);

	free(matrizes.matA); //libera memoria da matriz A
	free(matrizes.matB); //libera memoria da matriz B
	free(matrizes.matC); //libera memoria da matriz C

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Tempo gasto: %lf segundos.\n", elapsed);

	return 0;
}