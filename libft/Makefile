# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 12:40:14 by dabeloos          #+#    #+#              #
#    Updated: 2019/03/05 17:08:37 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3#-g -pg

GLOBALHEAD	= ./includes

CHAR_F		= ft_isalpha \
			  ft_isdigit \
			  ft_isalnum \
			  ft_isascii \
			  ft_isprint \
			  ft_toupper \
			  ft_tolower

INT_F		= ft_itoa \
			  ft_itoa2 \
			  ft_swap_int \
			  ft_sort_int \
			  ft_count_digit \

LST_F		= ft_lstnew \
			  ft_lstdelone \
			  ft_lstdel \
			  ft_lstdel_content \
			  ft_lstadd \
			  ft_lstiter \
			  ft_lstmap

MEM_F		= ft_memset \
			  ft_bzero \
			  ft_memcpy \
			  ft_memccpy \
			  ft_memmove \
			  ft_memchr \
			  ft_memcmp \
			  ft_memalloc \
			  ft_memdel

PUT_F		= ft_putchar \
			  ft_putstr \
			  ft_putendl \
			  ft_putnbr \
			  ft_putnbr2 \
			  ft_putchar_fd \
			  ft_putstr_fd \
			  ft_putendl_fd \
			  ft_putnbr_fd \
			  ft_putnbr2_fd

STR_F		= ft_strlen \
			  ft_strdup \
			  ft_strcpy \
			  ft_strncpy \
			  ft_strcat \
			  ft_strncat \
			  ft_strlcat \
			  ft_strchr \
			  ft_strrchr \
			  ft_strstr \
			  ft_strnstr \
			  ft_strcmp \
			  ft_strncmp \
			  ft_atoi \
			  ft_atoi2 \
			  ft_atoi3 \
			  ft_atoi_base \
			  ft_strnew \
			  ft_strdel \
			  ft_strclr \
			  ft_striter \
			  ft_striteri \
			  ft_strmap \
			  ft_strmapi \
			  ft_strequ \
			  ft_strnequ \
			  ft_strsub \
			  ft_strsub2 \
			  ft_strjoin \
			  ft_strtrim \
			  ft_strsplit \
			  ft_strrev \
			  ft_strdel_ptr \
			  ft_index_of

MAIN_F		= apply_ornament \
			  justify \
			  bases \
			  decode_format \
			  init_clean \
			  inspect_flags \
			  inspect_flags_support \
			  printf

HANDLERS_F	= handle_c \
			  handle_d \
			  handle_f \
			  handle_i \
			  handle_o \
			  handle_p \
			  handle_pctg \
			  handle_s \
			  handle_u \
			  handle_x \
			  handle_xmaj

FLOATS_F	= float_bits_extraction \
			  float_extraction \
			  float_extraction_support

CONVERS_F	= char_conversion \
			  float_bits_conversion \
			  float_conversion \
			  signed_conversion \
			  str_conversion \
			  unsigned_conversion

POLYADIC_F	= pf_boot \
			  pf_extrema \
			  pf_decimal_formatting \
			  pf_operations \
			  pf_manager \
			  pf_decimal_formatting_support \
			  pf_print_recursion \
			  pf_init_clean

READER_F	= reader \
			  remain_editor \
			  str_realloc_join \
			  get_next_line

ARRAY_F		= array \
			  growth \
			  search \
			  shrink \
			  iterator

MARRAY_F	= marray \
			  growth \
			  iterator

TYPEMNG_F	= typemanager \
			  typearray \
			  type_requests \
			  typeused

BTREE_F		= comparable \
			  replace \
			  iterator \
			  rebalance_deleted \
			  rebalance_added \
			  search \
			  utils \
			  status

TBTREE_F	= tbtree \
			  shrink \
			  growth \
			  iterator

MBTREE_F	= mbtree \
			  shrink \
			  growth \
			  initialize \
			  iterator

MEMNG_F		= free \
			  get_as_is \
			  get \
			  growth \
			  initialize \
			  memanager \
			  refill \
			  validate

HMAP_F		= hashable \
			  search \
			  iterator

MHMAP_F		= growth \
			  mhashmap \
			  mhashmap2 \
			  shrink \
			  iterator

THMAP_F		= growth \
			  thashmap \
			  shrink

O_FILES		= $(addsuffix .o, \
					$(addprefix ./basic_functions/, \
						$(addprefix char/, $(CHAR_F)) \
						$(addprefix int/, $(INT_F)) \
						$(addprefix lst/, $(LST_F)) \
						$(addprefix mem/, $(MEM_F)) \
						$(addprefix put/, $(PUT_F)) \
						$(addprefix str/, $(STR_F))) \
					$(addprefix ./ft_printf/, \
						$(addprefix handlers/, $(HANDLERS_F)) \
						$(addprefix floats/, $(FLOATS_F)) \
						$(addprefix conversions/, $(CONVERS_F)) \
						$(addprefix polyadic_float/, $(POLYADIC_F)) \
						$(addprefix main/, $(MAIN_F))) \
					$(addprefix ./ft_read/, \
						$(addprefix reader/, $(READER_F))) \
					$(addprefix ./array/, \
						$(addprefix array/, $(ARRAY_F)) \
						$(addprefix marray/, $(MARRAY_F))) \
					$(addprefix ./memory_manager/, \
						$(addprefix typemanager/, $(TYPEMNG_F)) \
						$(addprefix memanager/, $(MEMNG_F))) \
					$(addprefix ./hashmap/, \
						$(addprefix hashmap/, $(HMAP_F)) \
						$(addprefix thashmap/, $(THMAP_F)) \
						$(addprefix mhashmap/, $(MHMAP_F))) \
					$(addprefix ./btree/, \
						$(addprefix btree/, $(BTREE_F)) \
						$(addprefix tbtree/, $(TBTREE_F)) \
						$(addprefix mbtree/, $(MBTREE_F))))

END_E		= \033[00m
RED_E		= \033[01;31m
GREEN_E		= \033[01;32m
YELLOW_E	= \033[01;33m
PURPLE_E	= \033[01;35m
CYAN_E		= \033[01;36m
WHITE_E		= \033[01;37m
BOLD_E		= \033[1m
UNDERLINE_E	= \033[4m

#debug @gcc -g -pg -o $(NAME) $(O_FILES)
$(NAME):	$(O_FILES)
			@ar -rcs $@ $^
			@echo "$(GREEN_E)end compilation : $(NAME)$(END_E)"

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(GLOBALHEAD)

clean:
			@rm -f $(O_FILES)
			@echo "$(PURPLE_E)end clean : $(NAME)$(END_E)"

fclean:		clean
			@rm -f $(NAME)
			@echo "$(RED_E)end fclean : $(NAME)$(END_E)"

re:			fclean all

.PHONY: clean fclean all re
