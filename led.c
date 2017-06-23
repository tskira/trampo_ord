 #include <stdio.h>
 #include <stdlib.h>

 #include "led.h"
 #include "importacao.h"

	void PrintLed()
	{
		short prox;

		arquivo_registro = fopen(OUTPUT_FILE, "r");
		do
		{
			fseek(arquivo_registro, prox, SEEK_SET);
			printf("%d ->", prox);
		} while((fread(&prox, sizeof(short), 1, arquivo_registro)), prox != -1);
		fclose(arquivo_registro);
	}
