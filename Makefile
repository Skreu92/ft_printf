# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/04 23:54:53 by Etienne           #+#    #+#              #
#    Updated: 2017/07/04 23:54:55 by Etienne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS= -Wall -Werror -Wextra -O0 -g -fsanitize=address


SRC= ft_printf.c\
		getter.c\
		setter.c\
		is_it.c\


NAME = ft_printf
CC = gcc
OBJ = $(SRC:.c=.o)
RM = rm -rf
INC = -I includes/
FT = -L libft/ -lft
CG = \033[92m
CY =  \033[93m
CE = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Creating Library$(CE)\033[1A";
	@make -C libft/ fclean
	@make -C libft/
	@$(CC)  $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(FT)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Compiled FT_PRINTF$(CE)";

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:
	@$(RM) $(OBJ)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Cleaning Object files $(CE)";

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Cleaning FT_PRINTF $(CE)";

re: fclean all

.PHONY : all clean fclean re

