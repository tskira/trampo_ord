#ifndef IMPORTACAO_H_
#define IMPORTACAO_H_
#define TAM_MAX 512

	extern FILE *arquivo_registro;

	void ImportarArquivoRegistro(char*);
	void ExibirArquivo(char*);
	int CopiaRegistro(FILE*, char*);

#endif
