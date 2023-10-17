# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 17:31:53 by iaschnei          #+#    #+#              #
#    Updated: 2023/06/16 12:28:44 by iaschnei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
SRCS		=	main.c \
				srcs/parsing.c srcs/initialise_data.c srcs/cleanup.c     \
				srcs/create_threads.c srcs/checks.c srcs/eating.c        \
				srcs/messages.c srcs/sleeping.c
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
OBJS		=	$(SRCS:.c=.o)

CC			=	cc

INCL		=	philo.h

FLAGS		=	-Wall -Wextra -Werror

NAME		=	philo

COLOR_GREEN	=	\033[1;32m
COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[3;36m
COLOR_PURP	=	\033[1;35m
COLOR_END	=	\033[0m

%.o: %.c $(INCL)
	@$(CC) -include $(INCL) -c $< -o $@ -g
	@echo "$(COLOR_BLUE) || Compiling ($<)...$(COLOR_END)"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -g -lpthread
	@echo "$(COLOR_GREEN) || Done !$(COLOR_END)"
	@echo "$(COLOR_GREEN) || Ready to use ./philo !$(COLOR_END)"

clean:
	@rm -rf $(OBJS)
	@echo "$(COLOR_RED) || Cleaning files...$(COLOR_END)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(COLOR_RED) || Cleaning library...$(COLOR_END)"

re: fclean all
	
