 #include <stdio.h>
 #include "importacao.h"
 #include "busca.h"
 #include "print.h"

 int main()
 {
	 ImportarArquivoRegistro(OUTPUT_FILE);
	 //ExibirArquivo(OUTPUT_FILE);
	 PrintRegistro(BuscaRegistro("113605"));
	 return 0;
 }
