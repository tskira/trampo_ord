 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "importacao.h"

/*
 * Função para importar arquivo de registros
 * Abre se o arquivo ja existir, cria caso contrario
 *
 * parametros: nome do arquivo alvo
 */

 void ImportarArquivoRegistro(char *nome_arquivo)
 {
 	FILE *arquivo_fonte = fopen("dados-inline.txt", "r");
 	extern FILE *arquivo_registro;
	char buffer_registro[TAM_MAX];
	short tamanho = -1;

	arquivo_registro = fopen(nome_arquivo, "a+");

	fseek(arquivo_registro, 0, SEEK_END);
	if (ftell(arquivo_registro) == 0)
	{
		//escreve a cabeça da led
		fwrite(&tamanho, sizeof(short), 1, arquivo_registro);
		while( CopiaRegistro(arquivo_fonte, buffer_registro) )
		{
			tamanho = (short) strlen(buffer_registro);
			fwrite(&tamanho, sizeof(short), 1, arquivo_registro);
			fwrite(buffer_registro, tamanho, 1, arquivo_registro);
			printf("\n%d ", tamanho);
			printf("%s", buffer_registro);
		}
	}
	fclose(arquivo_fonte);
	fclose(arquivo_registro);
 }

 /*
  * Função que recebe um arquivo de dados e copia o atual campo referenciado
  *
  * parametros: arquivo alvo, buffer destino
  */

  int CopiaRegistro(FILE *arquivo_origem, char *buffer_destino)
  {
  	char atual_char;
	char buffer_auxiliar[TAM_MAX];
	int contador_campos = 0;
	int tamanho_buffer;

	buffer_auxiliar[0] = '\0';
	while (contador_campos < 4)
	{
		if ((atual_char = getc(arquivo_origem)) == EOF) return 0;
		if ((atual_char) == '|') contador_campos++;
		strncat(buffer_auxiliar, &atual_char, 1);
	}
	strcpy(buffer_destino, buffer_auxiliar);
	return 1;
  }

  /*
   * Funcao para imprimir arquivo
   * parametros: nome do arquivo
   */

  void ExibirArquivo(char *arquivo_alvo)
  {
  	FILE *fd = fopen(arquivo_alvo, "r");
	char read_buffer[TAM_MAX] = {[0 ... (TAM_MAX-1)] = '\0'};
  	char atual_char;
	short tam;

	fread(&tam, sizeof(short), 1, fd);
	printf("\nLED: %d", tam);

	while(fread(&tam, sizeof(short), 1, fd))
		{
		printf("\ntamanho: %d ", tam);
		fread(read_buffer, tam , 1, fd);
		printf("\n %s\n", read_buffer);
		memset(read_buffer,'\0',strlen(read_buffer));
		}
	fclose(fd);
  }
