# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: augay <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 08:33:54 by augay             #+#    #+#              #
#    Updated: 2021/01/06 08:33:58 by augay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
OPTION = -c
FLAG = -Wall -Werror -Wextra
SRC = main.c utils.c die.c gestion.c philo_fork.c philo_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAG) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
$(OBJ) :
	@gcc $(FLAG) $(OPTION) $(SRC)
re: fclean all

.PHONY: all clean fclean re $(NAME)