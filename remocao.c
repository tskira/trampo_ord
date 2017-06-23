#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "busca.h"
#include "importacao.h"
#include "remocao.h"

	void RemoveRegistro(char *registro_alvo)
	{
		int byte_offset_alvo;
		short led_head;
		short tamanho_registro;
		char *flag_removido = "*|";

		byte_offset_alvo = BuscaRegistro(registro_alvo);
		arquivo_registro = fopen(OUTPUT_FILE, "r+");
		rewind(arquivo_registro);
		fread(&led_head, sizeof(short), 1, arquivo_registro);
		fseek(arquivo_registro, byte_offset_alvo, SEEK_SET);
		fread(&tamanho_registro, sizeof(short), 1, arquivo_registro);
		fwrite(flag_removido, sizeof(char), strlen(flag_removido), arquivo_registro);
		fwrite(&led_head, sizeof(short), 1, arquivo_registro);
		fwrite("|", sizeof(char), 1, arquivo_registro);
		rewind(arquivo_registro);
		led_head = (short)byte_offset_alvo;
		fwrite(&led_head, sizeof(short), 1, arquivo_registro);
		printf("\n ######################### \n");
		printf("\n ####### REMOVIDO ######## \n");
		printf("\n ######################### \n");
		fclose(arquivo_registro);
	}
