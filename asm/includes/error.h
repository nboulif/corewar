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

# define ERROR_MALOC							"Malloc error (%s) on line : %d\n"
# define ERROR_INDENTIFY_OPC					"Can't identify operation code on line %d : %s\n"
# define ERROR_EMPTY_PROG						"Empty program\n"
# define ERROR_WRONG_ARGC						"Wrong number of arguments : %d\n"
# define ERROR_WRONG_FD							"Can't read source file %s\n"
# define ERROR_MISSING_LABEL					"Missing label : %s\n"
# define ERROR_UNKNOW_COMMAND					"Unknown command : %s\n"
# define ERROR_DOUBLE_NAME_COMMENT				"Double %s on line %d.\n"
# define ERROR_EMPTY_NAME_COMMENT				"Empty %s on line %d\n"
# define ERROR_MISSING_QUOTE					"Missig %s quote for %s on line %d.\n"
# define ERROR_MAX_LENGTH						"Max length exceeded for %s on line %d : %d (max: %d)\n"
# define ERROR_LEXICAL							"Lexical error (%d) on [%0.3d:%0.3d].\n"
# define ERROR_INVALID_REG_NUMBER				"Invalid register number on line %d : r%d \n"
# define ERROR_INVALID_IND_DIR					"Invalid value (\"%s\") of type %s on line %d, param number %d.\n"
# define ERROR_EMPTY_PARAM						"Empty param number %d on line %d.\n"
# define ERROR_WRONG_NB_PARAMS					"Wrong number of params on line %d : %d vs %d\n"
# define ERROR_PARAM_TYPE					    "Invalid param on line %d.\nReceived %s type for the param number %d\n"
# define ERROR_COMMAND_IN_PROG					"Command in program at [%0.3d:%0.3d]."

#endif
