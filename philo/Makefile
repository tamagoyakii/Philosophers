# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 13:47:13 by jihyukim          #+#    #+#              #
#    Updated: 2022/08/19 19:19:31 by jihyukim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

SRCS = main.c philo.c utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o :%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
