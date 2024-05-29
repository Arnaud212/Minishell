# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by jchauvet          #+#    #+#              #
#    Updated: 2023/08/18 08:52:00 by jchauvet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
#	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supress-readline ./minishell
#

NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror 

CPPFLAGS    := -I./inc -I./lib/libft/inc

LDFLAGS     := -L./lib/libft
LDLIBS      := -lft -lreadline

VPATH       := src/ \
			   src/cmd/ \
			   src/env/ \
			   src/exec/ \
			   src/expand/ \
			   src/lexer/ \
			   src/parser/ \
			   src/printer/ \
			   src/redir/ \
			   src/signals/ \
			   src/token/ \
			   src/utils/ \
			   src/builtin/

SRCS        := minishell.c
SRCS        += cmd.c scmd.c
SRCS        += env.c env_modify.c env_init.c
SRCS        += exec.c exec_pipeline.c exec_pipeline_pipes.c exec_scmd.c \
			   exec_scmd_path.c exec_wait.c exec_exit_status.c
SRCS        += expand.c  \
			   expand_var.c expand_var_split.c
SRCS        += lexer.c lexer_syntax.c lexer_token_other.c lexer_token_text.c
SRCS        += parser.c parser_scmd.c parser_pipeline.c \
			   parser_heredoc.c
SRCS        += printer_token.c printer_scmd.c printer_cmd.c
SRCS        += redir.c redir_undo.c
SRCS        += signals.c
SRCS        += token.c token_list.c
SRCS        += utils_error.c utils_gnl.c utils_lst.c utils_split.c utils_str.c utils_heredoc.c utils_exec.c
SRCS        += builtin_echo.c builtin_cd.c builtin_exit.c builtin_pwd.c \
			   builtin_env.c builtin_export.c builtin_unset.c builtin.c \
			   export_utils.c exit_utils.c

ODIR        := obj
OBJS        := $(SRCS:%.c=$(ODIR)/%.o)



.PHONY: all clean fclean re test

$(NAME): lib/libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.c| $(ODIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

%.a:
	$(MAKE) -C $(dir $@)

all: $(NAME)

clean:
	$(MAKE) -C lib/libft fclean
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
