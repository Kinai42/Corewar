# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 16:16:43 by dbauduin          #+#    #+#              #
#    Updated: 2018/11/13 02:30:22 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = $(addsuffix .o, $(addprefix obj/, add_player check_cor check_live main \
	  setup print arena init op parse_argv process utl error run sort_player \
	  tool0 tool1 tool2 i_add i_lfork i_or i_xor i_aff i_live i_st i_zjump \
	  i_and i_ld i_lld i_sti i_fork i_ldi i_lldi i_sub))

OBJ_W ?= $(shell find obj | grep \\.o$)

PROJECT = COREWAR
NAME = ../Virtual
cc =	-O1 -g -fsanitize=address	\
		-fno-omit-frame-pointer		\
		-fsanitize-address-use-after-scope

FLAG = -Wall	\
	   -Wextra	

C_DEF	?=	\e[38;5;15m
OK		?=	\e[38;5;47m


all: obj $(NAME)

obj:
	@mkdir obj

$(NAME): $(OBJ)
	@make -C ../libft
	@gcc -lcurses -o $(NAME) $(FLAG) $(OBJ) ../libft/libft.a
	@ echo "\033[32m[$(PROJECT)] Compilation done\033[0m"
	@ echo "\033[32m[$(PROJECT)] Executable created\033[0m"

obj/%.o: src/%.c
	@gcc $(FLAG) -o $@ -c $< -I include/ -I ../libft/include
obj/%.o: src/operator/%.c
	@gcc $(FLAG) -o $@ -c $< -I include/ -I ../libft/include

clean:
	@rm -f $(OBJ_W)
	@make -C ./../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./../libft fclean

re: fclean all
