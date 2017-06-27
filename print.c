/*
 * Conjunto de funcoes para exibir algumas paradas
 */

#include <stdio.h>
#include <string.h>
#include "print.h"
#include "importacao.h"

	/*
	 * Funcao para formatar impressao de um registro alvo
	 * So para ficar bonito para a professora
	 *
	 * @param
	 * byte_offset: e o offset do registro alvo
	 */
	void PrintRegistro(int byte_offset)
	{
		char registro_alvo[TAM_MAX];
		char *campo;
		short tam;
		char atual_char;
		if (byte_offset == -1)
		{
			printf("\n ####################################### \n");
			printf("\n ####### REGISTRO NAO EXISTENTE ######## \n");
			printf("\n ####################################### \n");
		}
		else
		{
			arquivo_registro = fopen(OUTPUT_FILE, "r");
			fseek(arquivo_registro, byte_offset, SEEK_SET);
			fread(&tam, sizeof(short), 1, arquivo_registro);
			fread(registro_alvo, tam, 1, arquivo_registro);
			printf("\n\n ####### REGISTRO ######## \n");
			campo = strtok(registro_alvo, "|");
			printf("\n INSCRICAO: %s", campo);
			campo = strtok(NULL, "|");
			printf("\n NOME: %s", campo);
			campo = strtok(NULL, "|");
			printf("\n CURSO: %s", campo);
			campo = strtok(NULL, "|");
			printf("\n SCORE: %s", campo);
			fclose(arquivo_registro);
			printf("\n");
			printf("\n ######################### \n");
		}
	}

	/*
	 * Funcao para imprimir todos os registros do arquivo de registros
	 *
	 * @param
	 * arquivo_alvo: nome do arquivo que desaja-se visualizar
	 *
	 */
	void ExibirArquivo(char *arquivo_alvo)
	{
	  FILE *fd = fopen(arquivo_alvo, "r");
	  char read_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
	  short tam;

	  fread(&tam, sizeof(short), 1, fd);
	  printf("\nLED: %d\n", tam);

	  while(fread(&tam, sizeof(short), 1, fd))
	  {
		  printf("\ntamanho: %d ", tam);
		  fread(read_buffer, tam , 1, fd);
		  if (read_buffer[0] != '*') printf(" %s\n", read_buffer);
		  else printf(" ### ESPAÇO DISPONIVEL ###\n");
		  memset(read_buffer,'\0',strlen(read_buffer));
	  }
	  fclose(fd);
  }
