# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 17:33:55 by dbauduin          #+#    #+#              #
#    Updated: 2018/10/28 17:05:37 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = $(addsuffix .o, $(addprefix obj/, byte check error file get_header init instruction inst_1_4 inst_5_8 inst_9_12 inst_13_16 is_type main op print tool ocp write tool_atoi))
OBJ_W ?= $(shell find obj | grep \\.o$)

PROJECT = ASM
NAME = asm
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
	@gcc $(FLAG) -o $(NAME) $(OBJ) ../libft/libft.a
	@printf "$(OK)[+][$(PROJECT)] Done $(C_DEF)\n"

obj/%.o: src/%.c
	@gcc $(FLAG) -o $@ -c $< -I include/ -I ../libft/include

clean:
	@rm -f $(OBJ_W)
	@make -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all
