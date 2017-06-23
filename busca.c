 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "busca.h"

 	int BuscaRegistro(char *inscricao_alvo)
	{
		char read_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
		char aux_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
		char *inscricao;
		short tam = 0;
		int byte_offset = 2;
		arquivo_registro = fopen("arquivo_final", "r");
		fread(&tam, sizeof(short), 1, arquivo_registro);
		while(!feof(arquivo_registro))
		{
			fread(&tam, sizeof(short), 1, arquivo_registro);
			fread(read_buffer, tam, 1, arquivo_registro);
			inscricao = strtok(read_buffer, "|");
			inscricao[strlen(inscricao)] = '\0';
			if(strcmp(inscricao, inscricao_alvo) == 0)
			{
				break;
			}
			byte_offset += tam;
			memset(read_buffer,'\0',strlen(read_buffer));
		}
		fclose(arquivo_registro);
		return(byte_offset);
	}
