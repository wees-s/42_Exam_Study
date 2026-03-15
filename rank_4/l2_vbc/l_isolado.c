node	*parse_add(char **s);
node	*parse_multi(char **s);
node	*parse_primary(char **s);

node	*parse_expr(char *s)
{
	node	*res;

	res = parse_add(&s);
	if (!res)
		return (NULL);
	if (*s)
	{
		unexpected(*s);
		return (destroy_tree(res), NULL);
	}
	return (res);
}


node	*parse_primary(char **s)
{
	node	*res;
	node	tmp;

	if (accept(s, '('))
	{
		res = parse_add(s);
		if (!res || !expect(s, ')'))
			return (destroy_tree(res), NULL);
		return (res);
	}
	if (isdigit(**s))
	{
		tmp = (node){VAL, **s - '0', NULL, NULL};
		(*s)++;
		return (new_node(tmp));
	}
	unexpected(**s);
	return (NULL);
}

node	*parse_multi(char **s)
{
	node	*left;
	node	*right;
	node	*tmp;

	left = parse_primary(s);
	if (!left)
		return (NULL);
	while (**s == '*')
	{
		(*s)++;
		right = parse_primary(s);
		if (!right)
			return (destroy_tree(left), NULL);
		tmp = new_node((node){MULTI, 0, left, right});
		if (!tmp)
			return (destroy_tree(left), destroy_tree(right), NULL);
		left = tmp;
	}
	return (left);
}

node	*parse_add(char **s)
{
	node	*left;
	node	*right;
	node	*tmp;

	left = parse_multi(s);
	if (!left)
		return (NULL);
	while (**s == '+')
	{
		(*s)++;
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
