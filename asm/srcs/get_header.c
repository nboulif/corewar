/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 17:07:57 by nsondag          ###   ########.fr       */
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

char	*search_next_line(t_prog *p, int max_len)
{
	int		len;
	char	*name_comment_continue;

	len = 0;
	if (!((name_comment_continue) = ft_strnew(max_len)))
	{
		printf("MALLOC PROBLEM\n");
		return (NULL);
	}
	while (get_next_line(p->fd, &p->line) > 0)
	{
		p->nb_line++;
		p->i = 0;
		len = skip_until(p->line, &p->i, "\"");
		ft_strcat(name_comment_continue, "\n");
		ft_strncat(name_comment_continue, &p->line[p->i - len], len);
		if (p->line[p->i] == '"')
			break ;
	}
	if (p->line[p->i] != '"')
		return (NULL);
	return (name_comment_continue);
}

int		get_valid_name_comment(t_prog *p, int max_len, char **name_comment)
{
	int		len_type;
	int		len;
	char	*name_comment_continue;

	len_type = max_len == PROG_NAME_LENGTH ? NAME : COMMENT;
	p->i += len_type;
	skip_chars(p->line, &p->i, " \t");
	if (!(p->line[p->i]))
		return (print_error_tokken(p, p->i, 0, "ENDLINE"));
	if (p->line[p->i] != '"')
		return (manage_errors(p, p->i));
	p->i++;
	len = skip_until(p->line, &p->i, "\"");
	if (!((*name_comment) = ft_strnew(max_len)))
		return (printf("MALLOC PROBLEM\n"));
	ft_strncpy(*name_comment, &p->line[p->i - len], len);
	if (p->line[p->i] != '"')
	{
		name_comment_continue = search_next_line(p, max_len);
		if (!name_comment_continue)
			return (manage_errors(p, p->i));
		else
		{
			len += ft_strlen(name_comment_continue);
			ft_strcat(*name_comment, name_comment_continue);
		}
	}
	if (len > max_len)
		return (printf("%s (Max length %d)\n", LONG_NAME, max_len));
	p->i++;
	skip_chars(p->line, &p->i, " \t");
	return ((!(p->line[p->i]) || p->line[p->i] == '#') ? 0 : manage_errors(p, p->i));
}

int		get_header(t_prog *p)
{
	while ((p->nb_line++ >= 0) && get_next_line(p->fd, &p->line) > 0)
	{
		p->i = 0;
		skip_chars(p->line, &p->i, " \t");
		if (!p->line || !p->line[p->i] || p->line[p->i] == '#')
			continue;
		if (!ft_strncmp(&p->line[p->i], NAME_CMD_STRING, NAME))
		{
			if (p->name)
				return (print_error_tokken(p, 0, NAME, "COMMAND_NAME"));
			if (get_valid_name_comment(p, PROG_NAME_LENGTH, &p->name))
				return (1);
		}
		else if (!ft_strncmp(&p->line[p->i], COMMENT_CMD_STRING, COMMENT))
		{
			if (p->comment)
				return (print_error_tokken(p, 0, COMMENT, "COMMAND_COMMENT"));
			if (get_valid_name_comment(p, COMMENT_LENGTH, &p->comment))
				return (1);
		}
		else
			return (manage_errors(p, 0));
		if (p->name && p->comment)
			break ;
	}
	return (0);
}
