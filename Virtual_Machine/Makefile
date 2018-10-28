# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 16:16:43 by dbauduin          #+#    #+#              #
#    Updated: 2018/10/28 17:20:42 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = $(addsuffix .o, $(addprefix obj/, add_player check_cor check_live main setup print arena init op parse_argv process utl debug run  sort_player get_cycle tool0 tool1 tool2 i_add i_lfork i_or i_xor i_aff i_live i_st i_zjump i_and i_ld i_lld i_sti i_fork i_ldi i_lldi i_sub))

OBJ_W ?= $(shell find obj | grep \\.o$)

PROJECT = COREWAR
NAME = Virtual
cc =	-O1 -g -fsanitize=address	\
		-fno-omit-frame-pointer		\
		-fsanitize-address-use-after-scope

FLAG = -Wall	\
	   -Werror	\
	   -Wextra	

C_DEF	?=	\e[38;5;15m
OK		?=	\e[38;5;47m


all: obj $(NAME)

obj:
	@mkdir obj

$(NAME): $(OBJ)
	@make -C ../libft
	@gcc -lncurses -o $(NAME) $(OBJ) ../libft/libft.a
	@printf "$(OK)[+][$(PROJECT)] Done $(C_DEF)\n"

obj/%.o: mysrc/%.c
	@gcc -lncurses -o $@ -c $< -I include/ -I ../libft/include
obj/%.o: mysrc/operator/%.c
	@gcc -lncurses -o $@ -c $< -I include/ -I ../libft/include

clean:
	@rm -f $(OBJ_W)
	@make -C ./../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./../libft fclean

re: fclean all
