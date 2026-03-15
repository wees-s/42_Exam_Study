#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}	type;
	int			val;
	struct node	*l;
	struct node	*r;
}	node;

node	*new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void	destroy_tree(node *n)
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

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

node	*parse_sum(char **s);

node	*parse_atomic(char **s)
{
	if (isdigit((unsigned char)**s))
	{
		node n = {VAL, **s - '0', NULL, NULL};
		(*s)++;
		return (new_node(n));
	}
	if (accept(s, '('))
	{
		node *n = parse_sum(s);
		if (!n)
			return (NULL);
		if (!expect(s, ')'))
		{
			destroy_tree(n);
			return (NULL);
		}
		return (n);
	}
	unexpected(**s);
	return (NULL);
}

node	*parse_product(char **s)
{
	node *l = parse_atomic(s);
	if (!l)
		return (NULL);
	while (accept(s, '*'))
	{
		node *r = parse_atomic(s);
		if (!r)
		{
			destroy_tree(l);
			return (NULL);
		}
		node n = {.type = MULTI, .l = l, .r = r};
		node *tmp = new_node(n);
		if (!tmp)
		{
			destroy_tree(l);
			destroy_tree(r);
			return (NULL);
		}
		l = tmp;
	}
	return (l);
}

node	*parse_sum(char **s)
{
	node *l = parse_product(s);
	if (!l)
		return (NULL);
	while (accept(s, '+'))
	{
		node *r = parse_product(s);
		if (!r)
		{
			destroy_tree(l);
			return (NULL);
		}
		node n = {.type = ADD, .l = l, .r = r };
		node *tmp = new_node(n);
		if (!tmp)
		{
			destroy_tree(l);
			destroy_tree(r);
			return (NULL);
		}
		l = tmp;
	}
	return (l);
}

node	*parse_expr(char *s)
{
	char *p = s;
	node *ret = parse_sum(&p);
	if (!ret)
		return (NULL);
	if (*p)
	{
		destroy_tree(ret);
		unexpected(*p);
		return (NULL);
	}
	return (ret);
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}