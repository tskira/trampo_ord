 /*
  *  Modulo que define as funcoes para realizacao de busca no arquivo de registro
  */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "busca.h"

	/*
	 * Funcao que realiza busca sequencial no arquivo de registros com base
	 * no campo inscricao
	 *
	 * @param
	 * inscricao_alvo: a inscricao do registro a ser buscado
	 *
	 * @returns
	 * retona o byte_offset do registro alvo, caso encontrado
	 * retorn -1 se não encontrar
	 */
 	int BuscaRegistro(char *inscricao_alvo)
	{
		char read_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
		char aux_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
		char *inscricao;
		short tam = 0;
		int byte_offset;
		int encontrou = FALSE;

		arquivo_registro = fopen("arquivo_final", "r");
		fread(&tam, sizeof(short), 1, arquivo_registro);
		byte_offset = ftell(arquivo_registro);
		while(fread(&tam, sizeof(short), 1, arquivo_registro))
		{
			fread(read_buffer, tam, 1, arquivo_registro);
			inscricao = strtok(read_buffer, "|");
			inscricao[strlen(inscricao)] = '\0';
			if(strcmp(inscricao, inscricao_alvo) == 0)
			{
				encontrou = TRUE;
				break;
			}
			memset(read_buffer,'\0',strlen(read_buffer));
			byte_offset = ftell(arquivo_registro);
		}
		fclose(arquivo_registro);
		if (encontrou) return(byte_offset);
		return(-1);
	}
