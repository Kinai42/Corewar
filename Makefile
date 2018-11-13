# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/28 17:24:12 by dbauduin          #+#    #+#              #
#    Updated: 2018/11/13 02:29:49 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM_PATH		= ./Virtual_Machine
ASM_PATH	= ./Assembler
DECOMP		= ./Decompilateur

all:
	@make -C $(VM_PATH)
	@make -C $(ASM_PATH)
	@make -C $(DECOMP)

clean:
	@make -C $(VM_PATH) clean
	@make -C $(ASM_PATH) clean
	@make -C $(DECOMP) clean

fclean:	clean
	@make -C $(VM_PATH) fclean
	@make -C $(ASM_PATH) fclean
	@make -C $(DECOMP) fclean

re:		fclean all

.PHONY:		all clean fclean re
