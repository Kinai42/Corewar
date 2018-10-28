# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/28 17:24:12 by dbauduin          #+#    #+#              #
#    Updated: 2018/10/28 17:25:23 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=   gcc
CFLAGS	= 	-Wall -Wextra -Werror
RM		=   rm -f

VM_PATH		= ./VM
ASM_PATH	= ./asm_dir
DECOMP		= ./decomp

all:	$(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@make -C $(VM_PATH)
	@make -C $(ASM_PATH)

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(VM_PATH) clean
	@make -C $(ASM_PATH) clean

fclean:	clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(VM_PATH) fclean
	@make -C $(ASM_PATH) fclean

re:		fclean all

.PHONY:		all clean fclean re
