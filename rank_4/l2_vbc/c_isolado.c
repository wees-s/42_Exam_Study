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
