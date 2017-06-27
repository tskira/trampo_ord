/*
 * Modulo para a insercao de novos registros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "insercao.h"
#include "importacao.h"
#include "busca.h"
#include "led.h"

	void InsereRegistro(char* novo_registro)
	{
		short tamanho_registro = strlen(novo_registro);
		short offset_alvo;
		short posicao_insercao;

		offset_alvo = ProcuraEspaco(tamanho_registro);
		if (offset_alvo == -1)
		{
			arquivo_registro = fopen(OUTPUT_FILE, "a+");
			fwrite(&tamanho_registro, sizeof(short), 1, arquivo_registro);
			fwrite(novo_registro, strlen(novo_registro), 1, arquivo_registro);
			fclose(arquivo_registro);
			printf("\n ##### REGISTRO INSERIDO ####");
		}
		else
		{
			//RemoveLed(offset_alvo);
			posicao_insercao = DevolveEspacoLed(offset_alvo, tamanho_registro);
			arquivo_registro = fopen(OUTPUT_FILE,"r+");
			fseek(arquivo_registro, posicao_insercao, SEEK_SET);
			fwrite("|", sizeof(char), 1, arquivo_registro);
			fwrite(&tamanho_registro, sizeof(short), 1, arquivo_registro);
			fwrite(novo_registro, sizeof(char), tamanho_registro, arquivo_registro);
			printf("\n #### REGISTRO INSERIDO #### ");
			fclose(arquivo_registro);
		}

	}
