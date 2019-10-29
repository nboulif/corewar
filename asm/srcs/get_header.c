/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/29 16:06:05 by nsondag          ###   ########.fr       */
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

int		get_valid_name_comment(t_prog *p, int max_len, char **name_comment)
{
	int len_type;
	int tmp_i;

	len_type = max_len == PROG_NAME_LENGTH ? NAME : COMMENT;
	p = skip_nb_chars(p, len_type);
	p = skip_chars(p, " \t");
	if (!(*p->line))
		return (print_error_tokken(p, p->i, 0, "ENDLINE"));
	if (*p->line != '"')
		return (manage_errors(p, p->i));
	p = skip_nb_chars(p, 1);
	tmp_i = p->i;
	p = skip_until(p, "\"");
	if (*p->line != '"')
		return (manage_errors(p, p->i));
	if (p->i - tmp_i + 1 >= max_len)
		return (printf("%s (Max length %d)\n", LONG_NAME, max_len));
	if (!((*name_comment) = ft_strnew(max_len)))
		return (printf("MALLOC PROBLEM\n"));
	ft_strncpy(*name_comment, p->line - p->i + tmp_i, p->i - tmp_i);
	p = skip_nb_chars(p, 1);
	p = skip_chars(p, " \t");
	return ((!*(p->line) || *p->line == '#') ? 0 : manage_errors(p, p->i));
}

int		get_header(t_prog *p)
{
	while ((p->nb_line++ >= 0) && get_next_line(p->fd, &p->line) > 0)
	{
		p = skip_chars(p, " \t");
		if (!p->line || !*p->line || *p->line == '#')
			continue;
		if (!ft_strncmp(p->line, NAME_CMD_STRING, NAME))
		{
			if (p->name)
				return (print_error_tokken(p, 0, NAME, "COMMAND_NAME"));
			if (get_valid_name_comment(p, PROG_NAME_LENGTH, &p->name))
				return (1);
		}
		else if (!ft_strncmp(p->line, COMMENT_CMD_STRING, COMMENT))
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
