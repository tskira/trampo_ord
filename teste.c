 #include <stdio.h>
 #include "importacao.h"
 #include "busca.h"
 #include "print.h"
 #include "remocao.h"
 #include "led.h"

 int main()
 {
	 ImportarArquivoRegistro(OUTPUT_FILE);
	 PrintRegistro(BuscaRegistro("113605"));

	 RemoveRegistro("113605");

	 PrintRegistro(BuscaRegistro("113605"));
	 ExibirArquivo(OUTPUT_FILE);
	 printf("\n");
	 PrintLed();
	 return 0;
 }
