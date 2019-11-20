/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:30:09 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 16:28:11 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_MALLOC					1
# define ERROR_INDENTIFY_OPC			2
# define ERROR_WRONG_ARGC				4
# define ERROR_WRONG_FD					5
# define ERROR_MISSING_LABEL			6
# define ERROR_UNKNOW_COMMAND			7
# define ERROR_DOUBLE_NAME_COMMENT		8
# define ERROR_EMPTY_NAME_COMMENT		9
# define ERROR_MISSING_QUOTE			10
# define ERROR_MAX_LENGTH				11
# define ERROR_LEXICAL					12
# define ERROR_INVALID_REG_NUMBER		13
# define ERROR_INVALID_IND_DIR			14
# define ERROR_EMPTY_PARAM				15
# define ERROR_WRONG_NB_PARAMS			16
# define ERROR_PARAM_TYPE				17
# define ERROR_COMMAND_IN_PROG			18

extern char *g_err_msgs[19];

#endif
