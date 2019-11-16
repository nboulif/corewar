/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 18:05:00 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	manage_header_errors(t_prog *p, int i)
{
	int tmp_i;

	tmp_i = i;
	printf("INVALID HEADER, ERROR line %d: ", p->nb_line);
	if (p->line[i++] == '.')
	{
		skip_chars(p->line, &i, LABEL_CHARS);
		return (printf("unknown command \"%.*s\"\n",
					i - tmp_i, &p->line[tmp_i]));
	}
	printf("%s\n", &p->line[i]);
	printf("line %d: ", p->nb_line);
	if (!p->name && !p->comment)
		return (printf("program name and comment not found\n"));
	else if (!p->name)
		return (printf("program name not found\n"));
	else if (!p->comment)
		return (printf("program comment not found\n"));
	return (0);
}

static int	search_next_line(t_prog *p, char **content,
	int *content_len, char *error_type)
{
	int		len;

	len = 0;
	while (get_next_line(p->fd, &p->line) > 0)
	{
		p->nb_line++;
		p->i = 0;
		len = skip_until(p->line, &p->i, "\"");
		ft_strcat(*content, "\n");
		ft_strncat(*content, &p->line[p->i - len], len);
		*content_len += len;
		if (p->line[p->i] == '"')
		{
			p->i++;
			return (OK);
		}
	}
	return (printf(ERROR_MISSING_QUOTE, "end", error_type, p->nb_line));
}

static int	set_type(int type, char **error_type, int *max_len)
{
	if (type == NAME_TYPE)
	{
		*error_type = "COMMAND_NAME";
		*max_len = PROG_NAME_LENGTH;
	}
	else if (type == COMMENT_TYPE)
	{
		*error_type = "COMMAND_COMMENT";
		*max_len = COMMENT_LENGTH;
	}
	return (OK);
}

static int	get_header_content(t_prog *p, char **content, int type)
{
	char	*error_type;
	int		max_len;
	int		content_len;

	set_type(type, &error_type, &max_len);
	if (*content)
		return (printf(ERROR_DOUBLE_NAME_COMMENT, error_type, p->nb_line));
	skip_chars(p->line, &p->i, " \t");
	if (!(p->line[p->i]))
		return (printf(ERROR_EMPTY_NAME_COMMENT, error_type, p->nb_line));
	if (p->line[p->i++] != '"')
		return (printf(ERROR_MISSING_QUOTE, "start", error_type, p->nb_line));
	content_len = skip_until(p->line, &p->i, "\"");
	if (!((*content) = ft_strnew(max_len)))
		return (printf(ERROR_MALOC, error_type, p->nb_line));
	ft_strncpy(*content, &p->line[p->i - content_len], content_len);
	if (p->line[p->i++] != '"')
		if (search_next_line(p, content, &content_len, error_type) != OK)
			return (ERROR);
	if (content_len > max_len)
		return (printf(ERROR_MAX_LENGTH,
			error_type, p->nb_line, content_len, max_len));
	skip_chars(p->line, &p->i, " \t");
	return (!p->line[p->i] || p->line[p->i] == '#' ? OK :
		printf(ERROR_LEXICAL, 36, p->nb_line, p->i));
}

int			get_header(t_prog *p)
{
	int		type_len;
	int		ret;

	ret = OK;
	while (get_next_line(p->fd, &p->line) > 0)
	{
		p->nb_line++;
		p->i = 0;
		skip_chars(p->line, &p->i, " \t");
		if (!p->line || !p->line[p->i] || p->line[p->i] == '#')
			continue;
		p->i++;
		type_len = skip_chars(p->line, &p->i, LABEL_CHARS) + 1;
		if (!ft_strncmp(&p->line[p->i - type_len], NAME_CMD_STRING, type_len))
			ret = get_header_content(p, &p->name, NAME_TYPE);
		else if (!ft_strncmp(&p->line[p->i - type_len],
					COMMENT_CMD_STRING, type_len))
			ret = get_header_content(p, &p->comment, COMMENT_TYPE);
		else
			return (manage_header_errors(p, p->i - type_len));
		if ((p->name && p->comment) || ret)
			break ;
	}
	return (ret);
}
