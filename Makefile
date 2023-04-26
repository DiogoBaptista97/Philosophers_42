# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 10:11:58 by dbraga-b          #+#    #+#              #
#    Updated: 2023/03/15 10:11:59 by dbraga-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
PUSH = philosiphers
SRC_PUSH = main.c ft_atoi.c actions.c checks.c routines.c create.c print.c
OBJ_PUSH = $(SRC_PUSH:.c=.o)


all: $(PUSH)


$(PUSH): $(OBJ_PUSH)
		$(CC) $(CFLAGS) -pthread $(OBJ_PUSH) -o philosiphers

clean:	clean
		rm -rf $(OBJ_PUSH)

fclean: clean
		rm -rf $(PUSH)

re: fclean all
