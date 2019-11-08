/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 16:28:06 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	search_next_line(t_prog *p, char **content, int *content_len)
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
			break ;
	}
	if (p->line[p->i] != '"')
		return (ERROR);
	return (OK);
}

static int	set_type(int type, char **error_type,
		char **error2long, int *max_len)
{
	if (type == NAME_TYPE)
	{
		*error_type = "COMMAND_NAME";
		*error2long = "Champion name too long";
		*max_len = PROG_NAME_LENGTH;
	}
	else if (type == COMMENT_TYPE)
	{
		*error_type = "COMMAND_COMMENT";
		*error2long = "Champion comment too long";
		*max_len = COMMENT_LENGTH;
	}
	return (OK);
}

static int	get_header_content(t_prog *p, char **content,
		int type_len, int type)
{
	char	*error_type;
	int		max_len;
	int		content_len;
	char	*error2long;

	set_type(type, &error_type, &error2long, &max_len);
	if (*content)
		return (print_error_token(p, 0, type_len, error_type));
	skip_chars(p->line, &p->i, " \t");
	if (!(p->line[p->i]))
		return (print_error_token(p, p->i, 0, "ENDLINE"));
	if (p->line[p->i++] != '"')
		return (manage_errors(p, p->i - 1));
	content_len = skip_until(p->line, &p->i, "\"");
	if (!((*content) = ft_strnew(max_len)))
		return (printf("MALLOC PROBLEM\n"));
	ft_strncpy(*content, &p->line[p->i - content_len], content_len);
	if (p->line[p->i++] != '"')
		if (search_next_line(p, content, &content_len) != OK)
			return (ERROR);
	if (content_len > max_len)
		return (printf("%s (Max length %d)\n", error2long, max_len));
	skip_chars(p->line, &p->i, " \t");
	return (!p->line[p->i] || p->line[p->i] == '#' ?
			OK : manage_errors(p, p->i));
}

/*
** type_len:	length of *_CMD_STRING (".name" or ".comment")
** ret:			return value, 0 if no error
**
** return:		ret
*/

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
			ret = get_header_content(p, &p->name, type_len, NAME_TYPE);
		else if (!ft_strncmp(&p->line[p->i - type_len],
					COMMENT_CMD_STRING, type_len))
			ret = get_header_content(p, &p->comment, type_len, COMMENT_TYPE);
		else
			return (manage_errors(p, 0));
		if ((p->name && p->comment) || ret)
			break ;
	}
	return (ret);
}
