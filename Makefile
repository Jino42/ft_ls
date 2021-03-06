# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/08/03 03:22:02 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

DIR_LFT = libft/
DIR_LIB = libs/
CFLAGS = -Wall -Werror -Wextra
FLAGS =  -g -I ./include/

SRC = main.c \
	  ls_type_and_file_right.c \
	  ft_lstinsert_alphabet.c \
	  ft_lstinsert_time.c \
	  ft_lst_remove_index.c \
	  ls_get_dir.c \
	  ls_stat_to_list.c \
	  ft_lst_remove.c \
	  ls_print.c \
	  ls_print_basic.c \
	  ls_print_l.c \
	  ls_loop.c \
	  ls_max_print.c \
	  ls_recup_file.c \
	  ls_free_env.c \
	  ls_pars_arg.c

SRC_DIR = srcs/

CC = gcc 

MODE = 

INC = includes/

INC_FILES = includes/ft_ls.h

OBJET = $(SRC:.c=.o)

OBJ_DIR = objs/

.PHONY: all, clean, fclean, re, $(NAME), lft, start, end


all: $(OBJ_DIR) $(NAME)

$(NAME): lib $(addprefix $(OBJ_DIR), $(OBJET)) $(INC_FILES)
	@$(CC) $(MODE) -I$(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LFT) -lft -o $(NAME)
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	#@mkdir $(DIR_LIB)
	#@mkdir $(OBJ_DIR)/event

start:
	@echo "\033[4m\033[33mCreation de $(NAME)   ...\033[0m"

end:
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@echo "\033[34m$^ \033[0m-> \033[1m\033[37m$@\033[0m"
	@($(CC) $(MODE) $(FLAGS)  -I./$(INC) -c -o $@ $<)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
#	@(cp $(DIR_LFT)libft.a ./libs/)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && make clean)

fclean: clean
	@/bin/rm -f $(NAME)
#	@(rm -rf $(DIR_LIB))
	@(cd $(DIR_LFT) && make fclean)

re: fclean all
