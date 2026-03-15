#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int	parse_int(json *dst, FILE *stream)
{
	if (fscanf(stream, "%d", &dst->integer) != 1)
		return (-1);
	dst->type = INTEGER;
	return (1);
}

int	parse_string(json *dst, FILE *stream)
{
	char	buf[10000];
	int		c;
	int		i;

	if (!expect(stream, '"'))
		return (-1);
	i = 0;
	while ((c = getc(stream)) != '"' && c != EOF)
	{
		if (c == '\\')
			c = getc(stream);
		buf[i++] = c;
	}
	buf[i] = '\0';
	dst->type = STRING;
	dst->string = strdup(buf);
	return (1);
}

int	parse_map(json *dst, FILE *stream)
{
	if (!expect(stream, '{'))
		return (-1);
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	while (peek(stream) != '}' && peek(stream) != EOF)
	{
		dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
		json key_tmp;
		if (parse_string(&key_tmp, stream) == -1)
			return (-1);
		dst->map.data[dst->map.size].key = key_tmp.string;
		if (!expect(stream, ':'))
			return (-1);
		if (argo(&dst->map.data[dst->map.size].value, stream) == -1)
			return (-1);
		dst->map.size++;
		if (peek(stream) == ',')
			accept(stream, ',');
	}
	return (expect(stream, '}'));
}

int	argo(json *dst, FILE *stream)
{
	int	c;

	while (isspace(c = peek(stream)))
		getc(stream);
	if (c == '{')
		return (parse_map(dst, stream));
	if (c == '"')
		return (parse_string(dst, stream));
	if (isdigit(c) || c == '-')
		return (parse_int(dst, stream));
	unexpected(stream);
	return (-1);
}
