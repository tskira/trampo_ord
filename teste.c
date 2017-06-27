 #include <stdio.h>
 #include "importacao.h"
 #include "busca.h"
 #include "print.h"
 #include "remocao.h"
 #include "led.h"
 #include "insercao.h"

 int main()
 {
	 ImportarArquivoRegistro(OUTPUT_FILE);
	 //PrintRegistro(BuscaRegistro("113605"));
	 //RemoveRegistro("113605");
	 //RemoveRegistro("135220");

	 //ExibirArquivo(OUTPUT_FILE);
	 //InsereRegistro("123|T|CC|316|");
	 //PrintRegistro(BuscaRegistro("123"));
	 //PrintRegistro(BuscaRegistro("200500"));

	 RemoveRegistro("123");
	 ExibirArquivo(OUTPUT_FILE);
	 PrintLed();
	 printf("\n");
	 //PrintLed();
	 return 0;
 }
