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
	 InsereRegistro("123|THIAGOSAITO|CC|316|");
	 RemoveRegistro("113605");
	 //PrintRegistro(BuscaRegistro("123"));
	 //PrintRegistro(BuscaRegistro("200500"));
	 InsereRegistro("123|THIAGOSAITO|CC|316|");

	 ExibirArquivo(OUTPUT_FILE);
	 printf("\n");
	 //PrintLed();
	 return 0;
 }
