 #include <stdio.h>
 #include "importacao.h"
 #include "busca.h"

 int main()
 {
	 ImportarArquivoRegistro("arquivo_final");
	 ExibirArquivo("arquivo_final");
	 printf("%d", BuscaRegistro("147228"));
	 return 0;
 }
