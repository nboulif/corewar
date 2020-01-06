# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboulif <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 23:59:28 by nboulif           #+#    #+#              #
#    Updated: 2019/10/29 10:53:47 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = full_corewar
CC = gcc

ASM_NAME = asm
VM_NAME = corewar

ASM = $(ASM_DIRECTORY)$(ASM_NAME)
VM = $(VM_DIRECTORY)$(VM_NAME)

ASM_DIRECTORY = ./asm/
VM_DIRECTORY = ./corewar/

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re asm corewar asm_test

all: $(NAME)

$(NAME): $(LIBFT) $(ASM_NAME) $(VM_NAME) 
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(ASM_NAME):
	@echo "$(NAME): $(GREEN)Creating $(ASM)...$(RESET)"
	@$(MAKE) -sC $(ASM_DIRECTORY)

$(VM_NAME):
	@echo "$(NAME): $(GREEN)Creating $(VM)...$(RESET)"
	@$(MAKE) -sC $(VM_DIRECTORY)

asm_tester:
	@echo "$(NAME): $(GREEN) STARTING TEST ASM FSANITIZE $(RESET)"
	@$(MAKE) -sC $(ASM_DIRECTORY) tester_f
	@echo "$(NAME): $(GREEN) STARTING TEST ASM VALGRIND $(RESET)"
	@$(MAKE) -sC $(ASM_DIRECTORY) tester_v

clean:
	@$(MAKE) -sC $(ASM_DIRECTORY) clean
	@$(MAKE) -sC $(VM_DIRECTORY) clean
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(ASM_DIRECTORY) fclean
	@$(MAKE) -sC $(VM_DIRECTORY) fclean
	
re: fclean all
