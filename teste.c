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
	 RemoveRegistro("135220");

	 ExibirArquivo(OUTPUT_FILE);
	 printf("\n");
	 PrintLed();

	 printf("\n%d\n", ProcuraEspaco(35));
	 return 0;
 }
