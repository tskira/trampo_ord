/*
 * Funcoes para implementacao do modulo de romocao de registro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "busca.h"
#include "importacao.h"
#include "remocao.h"


	/*
	 * Funcao para remocao do registro e atualizacao da led
	 *
	 * Utiliza a funcao BuscaRegistro para encontrar o byte offset
	 * do registro alvo
	 * Apos a remocao o espaco volta para a led
	 *
	 * @param
	 * registro_alvo: a inscricao do registro a ser removido
	 */
	void RemoveRegistro(char *registro_alvo)
	{
		short byte_offset_alvo;
		short led_head;
		short tamanho_registro;
		char *flag_removido = "*|";
		short teste = 10;

		byte_offset_alvo = BuscaRegistro(registro_alvo);
		if(byte_offset_alvo == -1)
		{
			printf("\n ################################## \n");
			printf("\n ####### REGISTRO INVALIDO ######## \n");
			printf("\n ################################## \n");
			return;
		}
		arquivo_registro = fopen(OUTPUT_FILE, "r+");
		rewind(arquivo_registro);
		fread(&led_head, sizeof(short), 1, arquivo_registro);
		fseek(arquivo_registro, byte_offset_alvo, SEEK_SET);
		fread(&tamanho_registro, sizeof(short), 1, arquivo_registro);
		fwrite(flag_removido, sizeof(char), strlen(flag_removido), arquivo_registro);
		fwrite(&led_head, sizeof(short), 1, arquivo_registro);
		fwrite("|", sizeof(char), 1, arquivo_registro);
		led_head = byte_offset_alvo;
		rewind(arquivo_registro);
		fwrite(&led_head, sizeof(short), 1, arquivo_registro);
		printf("\n ######################### \n");
		printf("\n ####### REMOVIDO ######## \n");
		printf("\n ######################### \n");
		fclose(arquivo_registro);
	}
