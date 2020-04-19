# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 16:21:36 by bchaleil          #+#    #+#              #
#    Updated: 2017/01/04 22:54:25 by bchaleil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC    = gcc
NAME  = philo_one
FLAGS = -Wall -Werror -Wextra -g
LIB   = -lpthread
SRCS  = main.c minilib1.c minilib2.c philo.c thread.c error.c log.c
OBJS  = $(SRCS:srcs/%.c=obj/%.o)

all: obj $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

obj:
	@mkdir -p obj

obj/%.o: srcs/%.c
	$(CC) $(FLAGS) -c -o $@ $<

re: fclean all

.PHONY:clean fclean re
