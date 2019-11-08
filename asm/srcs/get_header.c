/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 13:28:32 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** len_type: longueur de ".name" ou ".comment"
** tmp_i: temporaire pour avoir la longueur de name ou comment
**
** skip .name ou .comment
** skip les espaces
** gestion d'erreur si p->line != '"'
** skip " (premier)
** skip comment ou name jusqu'au deuxieme "
** si pas de second " gestion d'erreur
** error si nom ou commentaire trop long
** copier name ou comment dans name_comment (prog->name ou prog->comment)
** skip deuxieme "
** skip espaces
** line vide ou commentaire attendu apres, sinon erreur
*/

static char	*search_next_line(t_prog *p, int max_len)
{
	int		len;
	char	*content_continue;

	len = 0;
	if (!((content_continue) = ft_strnew(max_len)))
	{
		printf("MALLOC PROBLEM\n");
		return (NULL);
	}
	while (get_next_line(p->fd, &p->line) > 0)
	{
		p->nb_line++;
		p->i = 0;
		len = skip_until(p->line, &p->i, "\"");
		ft_strcat(content_continue, "\n");
		ft_strncat(content_continue, &p->line[p->i - len], len);
		if (p->line[p->i] == '"')
			break ;
	}
	if (p->line[p->i] != '"')
		return (NULL);
	return (content_continue);
}

static int	get_header_content(t_prog *p, int max_len, char **content)
{
	int		len;
	char	*content_continue;

	p->i++;
	len = skip_until(p->line, &p->i, "\"");
	if (!((*content) = ft_strnew(max_len)))
		return (printf("MALLOC PROBLEM\n"));
	ft_strncpy(*content, &p->line[p->i - len], len);
	if (p->line[p->i] != '"')
	{
		content_continue = search_next_line(p, max_len);
		if (!content_continue)
			return (manage_errors(p, p->i));
		else
		{
			len += ft_strlen(content_continue);
			ft_strcat(*content, content_continue);
		}
	}
	if (len > max_len)
		return (printf("%s (Max length %d)\n", LONG_NAME, max_len));
	p->i++;
	skip_chars(p->line, &p->i, " \t");
	return ((!(p->line[p->i]) || p->line[p->i] == '#') ? 0 :
			manage_errors(p, p->i));
}

static int	get_header2(t_prog *p, char **content, int type_len, int type)
{
	char	*error_message;
	int		max_len;

	error_message = NULL;
	if (*content)
	{
		if (type == NAME_TYPE)
			error_message = "COMMAND_NAME";
		else if (type == COMMENT_TYPE)
			error_message = "COMMAND_COMMENT";
		return (print_error_token(p, 0, type_len, error_message));
	}
	p->i = p->i + type_len;
	if (type == NAME_TYPE)
		max_len = PROG_NAME_LENGTH;
	else if (type == COMMENT_TYPE)
		max_len = COMMENT_LENGTH;
	skip_chars(p->line, &p->i, " \t");
	if (!(p->line[p->i]))
		return (print_error_token(p, p->i, 0, "ENDLINE"));
	if (p->line[p->i] != '"')
		return (manage_errors(p, p->i));
	if (get_header_content(p, max_len, content))
		return (1);
	return (0);
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

	ret = 0;
	while (get_next_line(p->fd, &p->line) > 0)
	{
		type_len = 0;
		p->nb_line++;
		p->i = 0;
		skip_chars(p->line, &p->i, " \t");
		if (!p->line || !p->line[p->i] || p->line[p->i] == '#')
			continue;
		type_len = skip_chars(&p->line[p->i + 1], &type_len, LABEL_CHARS) + 1;
		if (!ft_strncmp(&p->line[p->i], NAME_CMD_STRING, type_len))
			ret = get_header2(p, &p->name, type_len, NAME_TYPE);
		else if (!ft_strncmp(&p->line[p->i], COMMENT_CMD_STRING, type_len))
			ret = get_header2(p, &p->comment, type_len, COMMENT_TYPE);
		else
			return (manage_errors(p, 0));
		if ((p->name && p->comment) || ret)
			break ;
	}
	return (ret);
}
