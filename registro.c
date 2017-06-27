/*
 * Trabalho 1 de Ord
 * Instrucoes no pdf README
 * Alunos: Thiago Kira ra 78750
 * 		   Evandro Estima ra
 */

#include <stdio.h>
#include <argp.h>
#include <string.h>

#include "busca.h"
#include "importacao.h"
#include "insercao.h"
#include "led.h"
#include "print.h"
#include "remocao.h"

struct arguments
{
	char *args[4];
	int funcao;
};


static struct argp_option options[] =
{
	{0, 'i', " Inscricao Nome Curso Score", OPTION_ARG_OPTIONAL, "Insere novo registro"},
	{0, 'r', " Inscricao ", OPTION_ARG_OPTIONAL, "Remove registro"},
	{0, 'b', 0, OPTION_ARG_OPTIONAL, "Insere registro com estrategia best fit"},
	{0, 'w', 0, OPTION_ARG_OPTIONAL, "Insere registro com estrategia worst fit"},
	{0, 'p', 0, OPTION_ARG_OPTIONAL, "Printa o arquivo de registros"},
	{0, 'l', 0, OPTION_ARG_OPTIONAL, "Printa a atual estado da led, no formato: byte offset -> tamanho disponivel"},
	{0, 's', " Inscricao ", OPTION_ARG_OPTIONAL, "Busca um registro"},
	{0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch(key)
	{
		case 'i':
		{
			arguments->funcao = 0;
			break;
		}
		case 'r':
		{
			arguments->funcao = 1;
			break;
		}
		case 'b':
		{
			arguments->funcao = 2;
			break;
		}
		case 'w':
		{
			arguments->funcao = 3;
			break;
		}
		case 'p':
		{
			arguments->funcao = 4;
			break;
		}
		case 'l':
		{
			arguments->funcao = 5;
			break;
		}
		case 's':
		{
			arguments->funcao = 6;
			break;
		}
		case ARGP_KEY_ARG:
		  if (state->arg_num > 4)
		  {
		  	argp_usage(state);
		  }
		  arguments->args[state->arg_num] = arg;
		  break;
		  /*
		case ARGP_KEY_END:
		  if (state->arg_num != 0 )
		  {
		  	argp_usage (state);
		  }
		  break;
		  */
		default:
		  return ARGP_ERR_UNKNOWN;

	}
	return 0;
}

static struct argp argp = {options, parse_opt, 0, 0};

int main (int argc, char **argv)
{
	struct arguments arguments;
	char argumentos_buffer[512] = {[0 ... 511] = '\0'};

	arguments.args[0] = "";
	arguments.args[1] = "";
	arguments.args[2] = "";
	arguments.args[3] = "";

	ImportarArquivoRegistro(OUTPUT_FILE);
	argp_parse(&argp, argc, argv, OPTION_ARG_OPTIONAL, 0, &arguments);
	strcat(argumentos_buffer, arguments.args[0]);
	strcat(argumentos_buffer, "|");
	strcat(argumentos_buffer, arguments.args[1]);
	strcat(argumentos_buffer, "|");
	strcat(argumentos_buffer, arguments.args[2]);
	strcat(argumentos_buffer, "|");
	strcat(argumentos_buffer, arguments.args[3]);
	strcat(argumentos_buffer, "|");


	switch(arguments.funcao)
	{
		case 0:
		{
			InsereRegistro(argumentos_buffer);
			break;
		}
		case 1:
		{
			RemoveRegistro(arguments.args[0]);
			break;
		}
		case 2:
		{
			printf("\nImplementar o Best Fit");
			break;
		}
		case 3:
		{
			printf("\nImplementao Worts Fit");
			break;
		}
		case 4:
		{
			ExibirArquivo(OUTPUT_FILE);
			break;
		}
		case 5:
		{
			PrintLed();
			break;
		}
		case 6:
		{
			PrintRegistro(BuscaRegistro(arguments.args[0]));
			break;
		}
	}
	printf("\n\n");
}
