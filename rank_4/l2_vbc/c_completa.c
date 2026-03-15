#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	enum { ADD, MULTI, VAL } type;
	int val;
	struct node *l;
	struct node *r;
} node;

/* Aloca memória e inicializa o nó com os dados da estrutura passada por valor */
node *new_node(node n)
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

/* Desaloca a árvore recursivamente; verifica NULL para evitar crash em erros de sintaxe */
void destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

/* Centraliza mensagens de erro de parsing conforme o enunciado da 42 */
void unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

/* Avança o ponteiro se o caractere atual for o esperado */
int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

/* Exige um caractere; se falhar, dispara a mensagem de erro */
int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}


// TODO

/* Protótipos: Definem a escada de precedência (Add -> Multi -> Primary) */
node	*parse_add(char **s);
node	*parse_multi(char **s);
node	*parse_primary(char **s);

/**
 * PARSE_EXPR (Interface e Validação)
 * LOGICA: Inicia o processo e garante que nenhum caractere "lixo" sobrou.
 * SINTAXE: Recebe char* mas passa char** (&s) para as funções de baixo.
 */
node	*parse_expr(char *s)
{
	node	*res;

	res = parse_add(&s);
	if (!res)
		return (NULL);
	// Se a árvore terminou mas ainda existe algo na string (ex: "1+2)")
	if (*s)
	{
		unexpected(*s);
		return (destroy_tree(res), NULL);
	}
	return (res);
}

/**
 * PARSE_ADD (Baixa Precedência)
 * LOGICA: É o ponto de partida da matemática. Une blocos de multiplicação com '+'.
 * SINTAXE: Mesma estrutura do Multi, mas chamando a função de precedência superior.
 */
node	*parse_add(char **s)
{
	node	*left;
	node	*right;
	node	*tmp;

	left = parse_multi(s); // Primeiro tenta resolver as multiplicações
	if (!left)
		return (NULL);
	while (**s == '+')
	{
		(*s)++; // Consome o '+'
		right = parse_multi(s);
		if (!right)
			return (destroy_tree(left), NULL);
		tmp = new_node((node){ADD, 0, left, right});
		if (!tmp)
			return (destroy_tree(left), destroy_tree(right), NULL);
		left = tmp;
	}
	return (left);
}

/**
 * PARSE_MULTI (Alta Precedência)
 * LOGICA: Agrupa números/parênteses usando a multiplicação.
 * SINTAXE: O loop 'while' garante a associatividade à esquerda (1*2*3).
 */
node	*parse_multi(char **s)
{
	node	*left;
	node	*right;
	node	*tmp;

	left = parse_primary(s); // Primeiro tenta pegar um número ou parêntese
	if (!left)
		return (NULL);
	while (**s == '*')
	{
		(*s)++; // Consome o '*'
		right = parse_primary(s);
		if (!right)
			return (destroy_tree(left), NULL); // Erro à direita: destrói a árvore construída
		// O que já tínhamos (left) vira o filho esquerdo do novo nó MULTI
		tmp = new_node((node){MULTI, 0, left, right});
		if (!tmp)
			return (destroy_tree(left), destroy_tree(right), NULL);
		left = tmp;
	}
	return (left);
}

/**
 * PARSE_PRIMARY (O Atômico)
 * LOGICA: Resolve a unidade básica (um número) ou um grupo prioritário ().
 * SINTAXE: if (accept) para '(' ou if (isdigit) para valores.
 */
node	*parse_primary(char **s)
{
	node	*res;
	node	tmp;

	// Se houver '(', a precedência reseta: voltamos para o topo (parse_add)
	if (accept(s, '('))
	{
		res = parse_add(s);
		// Se a expressão interna falhar ou não fechar ')', limpamos tudo
		if (!res || !expect(s, ')'))
			return (destroy_tree(res), NULL);
		return (res);
	}
	// Se for dígito, cria o nó folha (sem filhos)
	if (isdigit(**s))
	{
		// SINTAXE: tmp = {TIPO, VALOR, ESQUERDA, DIREITA}
		tmp = (node){VAL, **s - '0', NULL, NULL}; // (node) cast para garantir atribuição
		(*s)++; // Avança o ponteiro da string
		return (new_node(tmp));
	}
	unexpected(**s);
	return (NULL);
}

// END

// REMOVER O EXPR ORIGINAL

/* Resolve a árvore matematicamente respeitando a precedência da estrutura */
int eval_tree(node *tree)
{
	if (tree->type == ADD)
		return (eval_tree(tree->l) + eval_tree(tree->r));
	if (tree->type == MULTI)
		return (eval_tree(tree->l) * eval_tree(tree->r));
	return (tree->val);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}
