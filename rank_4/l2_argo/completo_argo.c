#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* --- ESTRUTURAS FORNECIDAS --- */
typedef struct	json {
	enum { MAP, INTEGER, STRING } type;
	union {
		struct { struct pair *data; size_t size; } map;
		int	integer;
		char *string;
	};
} json;

typedef struct	pair {
	char *key;
	json value;
} pair;

/* --- PROTÓTIPOS DAS AUXILIARES DO EXAME --- */
int		peek(FILE *stream);
int		accept(FILE *stream, char c);
int		expect(FILE *stream, char c);
void	unexpected(FILE *stream);
int		argo(json *dst, FILE *stream);

/* -------------------------------------------------------------------------- */
/* LÓGICA DO PARSER                             */
/* -------------------------------------------------------------------------- */

// 1. PARSE DE INTEIROS
int	parse_int(json *dst, FILE *stream)
{
	// fscanf com %d é o jeito mais curto de ler um número e convertê-lo.
	// Se retornar 1, leu com sucesso.
	if (fscanf(stream, "%d", &dst->integer) != 1)
		return (-1);
	dst->type = INTEGER;
	return (1);
}

// 2. PARSE DE STRINGS
int	parse_string(json *dst, FILE *stream)
{
	// Garante que começa com aspas. O expect consome o caractere se for verdadeiro.
	if (!expect(stream, '"'))
		return (-1);

	char	buf[10000]; // Buffer grande para evitar mallocs repetidos durante o parse.
	int		i = 0;
	int		c;

	// Lê até encontrar a aspa de fechamento ou fim do arquivo.
	while ((c = getc(stream)) != '"' && c != EOF)
	{
		// Se encontrar '\', o caractere seguinte é literal (escape).
		if (c == '\\')
			c = getc(stream);
		buf[i++] = c;
	}
	buf[i] = '\0';
	dst->type = STRING;
	// strdup aloca memória na heap e copia o buffer. Necessário para persistir os dados.
	dst->string = strdup(buf);
	return (1);
}

// 3. PARSE DE MAPAS { "key": value }
int	parse_map(json *dst, FILE *stream)
{
	// Garante que o mapa inicia com '{'.
	if (!expect(stream, '{'))
		return (-1);

	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;

	// Loop enquanto não encontrar o fechamento do mapa '}'.
	while (peek(stream) != '}' && peek(stream) != EOF)
	{
		// Expande o array de pares conforme novos elementos surgem.
		// sizeof(pair) garante o espaço para a struct que contém a chave e o valor.
		dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));

		// A chave em JSON é obrigatoriamente uma String.
		json key_tmp;
		if (parse_string(&key_tmp, stream) == -1)
			return (-1);
		dst->map.data[dst->map.size].key = key_tmp.string;

		// O separador entre chave e valor deve ser ':'.
		if (!expect(stream, ':'))
			return (-1);

		// RECURSÃO: O valor pode ser qualquer tipo (Int, String ou outro Mapa).
		// Chamamos argo() para resolver isso genericamente.
		if (argo(&dst->map.data[dst->map.size].value, stream) == -1)
			return (-1);

		dst->map.size++;

		// Se houver uma vírgula, consumimos ela para o próximo item.
		// O accept() consome se for verdade, senão ignora.
		if (peek(stream) == ',')
			accept(stream, ',');
	}
	// Fecha o mapa e garante que termina com '}'.
	return (expect(stream, '}'));
}

/* 4. FUNÇÃO PRINCIPAL (ENTRY POINT) */
int	argo(json *dst, FILE *stream)
{
	int	c;

	// Pula espaços brancos (tabs, spaces, newlines) antes de identificar o token.
	while (isspace(c = peek(stream)))
		getc(stream);

	// IDENTIFICAÇÃO DE TIPO (Peek não remove o caractere, apenas olha).
	if (c == '{')
		return (parse_map(dst, stream));
	if (c == '"')
		return (parse_string(dst, stream));
	// Se for dígito ou sinal negativo, é um inteiro.
	if (isdigit(c) || c == '-')
		return (parse_int(dst, stream));

	// Se não for nada disso, é um erro de formato.
	unexpected(stream);
	return (-1);
}

/* -------------------------------------------------------------------------- */
/* FUNÇÕES AUXILIARES (FORNECIDAS)                     */
/* -------------------------------------------------------------------------- */

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream); // Devolve o caractere para o stream para ser lido depois.
	return (c);
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		getc(stream); // Consome o caractere.
		return (1);
	}
	return (0);
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return (1);
	unexpected(stream); // Avisa erro de token inesperado.
	return (0);
}

void	unexpected(FILE *stream)
{
	int c = peek(stream);
	if (c != EOF)
		printf("unexpected token '%c'\n", c);
	else
		printf("unexpected end of input\n");
}
