# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dna <dna@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 10:38:06 by dgross            #+#    #+#              #
#    Updated: 2023/02/15 19:16:34 by dna              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

VPATH		= src: src/builtins: src/utils: src/signals: \
			  src/lexer: src/parser: src/execution: \
			  src/redirection: src/heredoc:

LIBFT		= libft/libft.a

SRC			= main.c error.c free.c syntax.c\
			  utils.c catch.c\
			  signals.c open_file.c\
			  reset_redir.c redirection.c \
			  parser.c cmd_counter.c cmd_handler.c init_cmd.c redir_handler.c \
			  lexer.c counter.c skipper.c whitespace_skipper.c \
			  heredoc_exp.c heredoc.c \
			  execution.c execute_builtin.c execute_cmd.c \
			  exec_exit.c expansion.c edit_line.c pipes.c\
			  echo.c cd.c pwd.c export.c env.c exit.c unset.c

OBJ_DIR		= ./obj/

OBJ			= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

INCLUDES	= -I./includes -I./libft/includes -I /Users/$(USER)/goinfre/.brew/opt/readline/include #-Wno-gnu-include-next -ILeaksanitizer/include


LINCLUDES	= -L./libft -lft -L /Users/$(USER)/goinfre/.brew/opt/readline/lib #-LLeaksanitizer -llsan -lc++

g			= \033[1;32m
de 			= \033[0m
r 			= \033[0;31m
w			= \033[0;97m
b			= \033[0;30m
br          = \033[38;5;215m
wb			= \033[48;5;015m
brb			= \033[48;5;137m

all: $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

obj/%.o: %.c
	@echo "$(g)Compiling  $(w)$<$(de)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): obj $(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBFT) $(LINCLUDES) -lreadline -o $(NAME)
	@echo "$(g)Compiling Done ✔️$(de)"

clean:
	@echo "$(r)Cleaning 🧹 $(w)...$(de)"
	@$(MAKE) clean -C libft/
	@rm -rf obj
	@rm -rf here_doc

fclean: clean
	@$(MAKE) fclean -C libft/
	@rm -rf $(NAME)

git:
	git add .
	git commit -m "commit"
	git push

re: fclean all

.PHONY: all clean fclean re
