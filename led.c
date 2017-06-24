/*
 * Funcoes para manipulacao e manutencao da led
 * A led sao os 2 primeiros bytes do registro
 * Indica a cabeca da LED
 */

 #include <stdio.h>
 #include <stdlib.h>

 #include "led.h"
 #include "importacao.h"

	/*
	 *Funcao para visualizacao da led
	 */
	void PrintLed()
	{
		short prox;

		arquivo_registro = fopen(OUTPUT_FILE, "r");
		printf("\nLED: ");
		fread(&prox, sizeof(short), 1, arquivo_registro);
		printf(" %d", prox);
		while(prox != -1)
		{
			fseek(arquivo_registro, prox + 4, SEEK_SET);
			fread(&prox, sizeof(short), 1, arquivo_registro);
			printf("-> %d", prox);
		}
		printf("\n");
		fclose(arquivo_registro);

	}

	/*
	 * Funcao para buscar um determinado espaco na led
	 * Percorre a led ate encontrar um tamanho maior ou igual ao requisitado
	 *
	 * @param
	 * tamanho: tamanho desejado para a insercao
	 *
	 * @returns
	 * retorna o byte offset do espaco, caso disponivel
	 * retorna -1 se nao houver tal espaco
	 */
	short ProcuraEspaco(short tamanho)
	{
		short prox;
		short espaco_livre;

		arquivo_registro = fopen(OUTPUT_FILE, "r");
		while(prox != -1)
		{
			fread(&prox, sizeof(short), 1, arquivo_registro);
			fseek(arquivo_registro, prox, SEEK_SET);
			fread(&espaco_livre, sizeof(short), 1, arquivo_registro);
			if(tamanho <= espaco_livre) break;
			fseek(arquivo_registro, 2, SEEK_CUR);
		}

		fclose(arquivo_registro);
		return(prox);
	}
