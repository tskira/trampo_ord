 /*
  * Modulo que define as funcoes referente a importacao do arquivo
  */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "importacao.h"

 FILE *arquivo_registro;

/*
 * Função para importar arquivo de registros
 * Abre se o arquivo ja existir, cria caso contrario
 *
 * @param
 * nome_arquivo: nome do arquivo alvo a ser criado
 * este sera o nome para o arquivo de regitros
 */
 void ImportarArquivoRegistro(char *nome_arquivo)
 {
 	FILE *arquivo_fonte = fopen("dados-inline.txt", "r");
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
  * Função auxiliar para a leitura do arquivo de entrada dados-inline
  * Realiza copia de um registro a ser copiado
  * Atraves da contagem de campos
  *
  * @param
  * arquivo_origem: arquivo alvo para copia do registros
  * buffer_destino: buffer para a copia do registro
  *
  * @returns
  * retorna 0 caso o arquivo tenha chegado ao final
  * retorna 1 caso caso ainda nao tenha terminado
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
