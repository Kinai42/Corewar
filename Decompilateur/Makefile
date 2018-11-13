# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbauduin <dbauduin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 17:32:35 by dbauduin          #+#    #+#              #
#    Updated: 2018/11/13 02:32:32 by dbauduin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = 	get_arg.c check_arg.c w_name.c w_comment.c w_instructions.c\
			w_direct.c w_indirect.c w_arg.c opc.c created_file.c ft_printc.c\
			is_direct_char.c check_instruction.c check_magic.c init_tab.c\
			w_addr.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = src
OBJ_PATH = obj

LIB_PATH = ../libft


SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

PROJECT = DEASM
NAME = ../deasm

#FLAGS
CPPFLAGS = -I include -I ../libft/include
CFLAGS = -Wall -Werror -Wextra

#COMPILER
CC = clang

#RULES
all: $(NAME)

$(NAME): $(OBJ) include/deasm.h
	@make -C ../libft
	@ $(CC) $(CFLAGS) -o $@ $(OBJ) ../libft/libft.a
	@ echo "\033[32m[$(PROJECT)] Compilation done\033[0m"
	@ echo "\033[32m[$(PROJECT)] Executable created\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@ mkdir $(OBJ_PATH) 2> /dev/null || true
	@ $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@ rm -f $(OBJ)
	@make -C ../libft clean
	@ rmdir $(OBJ_PATH) 2>/dev/null || true

fclean: clean
	@ rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all

.livb/PHONY: all clean fclean re
