#ifndef IMPORTACAO_H_
#define IMPORTACAO_H_
#define TAM_MAX 512
#define OUTPUT_FILE "arquivo_final"

	extern FILE *arquivo_registro;

	void ImportarArquivoRegistro(char*);
	int CopiaRegistro(FILE*, char*);

#endif
