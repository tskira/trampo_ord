/*
 * Funcoes para manipulacao e manutencao da led
 * A led sao os 2 primeiros bytes do registro
 * Indica a cabeca da LED
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "led.h"
 #include "importacao.h"

	/*
	 *Funcao para visualizacao da led
	 */
	void PrintLed()
	{
		short prox;
		short tamanho;

		arquivo_registro = fopen(OUTPUT_FILE, "r");
		printf("\nLED: ");
		fread(&prox, sizeof(short), 1, arquivo_registro);
		printf(" %d", prox);
		while(prox != -1)
		{
			fseek(arquivo_registro, prox, SEEK_SET);
			fread(&tamanho, sizeof(short), 1, arquivo_registro);
			printf("(%d)", tamanho);
			fseek(arquivo_registro, 2, SEEK_CUR);
			fread(&prox, sizeof(short), 1, arquivo_registro);
			printf(" -> %d", prox);
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
			if(espaco_livre >= tamanho) break;
			fseek(arquivo_registro, 2, SEEK_CUR);
		}

		fclose(arquivo_registro);
		return(prox);
	}

	/*
	 * Funcao para remocao de determinado espaco disponivel da led
	 *
	 * @param
	 * offset_alvo: e o byte offset da posicao a ser removida
	 */
	void RemoveLed(short offset_alvo)
	{
		short offset_atual;
		short prox;
		int encontrou = 0;

		arquivo_registro = fopen(OUTPUT_FILE, "r+");
		fseek(arquivo_registro, offset_alvo + 4, SEEK_SET);
		fread(&prox, sizeof(short), 1, arquivo_registro);
		rewind(arquivo_registro);
		while(fread(&offset_atual, sizeof(short), 1, arquivo_registro))
		{
			encontrou = offset_atual == offset_alvo;
			if (encontrou)
			{
				fseek(arquivo_registro, -2, SEEK_CUR);
				fwrite(&prox, sizeof(short), 1, arquivo_registro);
				break;
			}
			fseek(arquivo_registro, offset_atual + 4, SEEK_SET);
		}
		fclose(arquivo_registro);

	}

	/*
	 * Funcao para devolver sobra de espaco para a led apos uma insercao
	 * verifica o espaco disponivel e o tamanho do novo registro
	 * atualiza o novo campo gerado, arrumando sua posicao e inserindo-o na led
	 * devolve a byte offset onde o novo registro deve ser inserido
	 * Caso a sobra seja menor ou igual a 14, sera gerada fragmantacao
	 * O espaco resultante sai da led
	 *
	 * @param
	 * offset_alvo: o espaco alvo para a nova insercao
	 * tamanho_registro: espaco a ser ocupado
	 *
	 * @returns
	 * retorna o byte offset onde o novo registro deve ser inserido
	 */
	short DevolveEspacoLed(short offset_alvo, short tamanho_registro)
	{
		short tamanho_espaco_livre;
		short tamanho_sobra;

		arquivo_registro = fopen(OUTPUT_FILE, "r+");
		fseek(arquivo_registro, offset_alvo, SEEK_SET);
		fread(&tamanho_espaco_livre, sizeof(short), 1, arquivo_registro);
		tamanho_sobra = tamanho_espaco_livre - tamanho_registro - 2;//2 byte para o tamanho do novo registro + 1 do "|"
		fseek(arquivo_registro, -2, SEEK_CUR);
		fwrite(&tamanho_sobra, sizeof(short), 1, arquivo_registro);
		fclose(arquivo_registro);
		if(tamanho_sobra <= 14) RemoveLed(offset_alvo);
		return(offset_alvo + tamanho_sobra + 1);
	}
