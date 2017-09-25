# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/04 23:54:53 by Etienne           #+#    #+#              #
#    Updated: 2017/09/25 15:37:54 by etranchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS= -Wall -Werror -Wextra -o2

/*-O0 -g -fsanitize=address */

SRC= ft_printf.c\
		getter.c\
		setter.c\
		is_it.c\
		ft_conv_s.c\
		ft_lltoa.c\
		ft_conv_dec.c\
		ft_conv_u.c\
		ft_conv_x.c\
		ft_conv_c.c\
		ft_conv_p.c\
		ft_conv_o.c\
		checker.c\
		libft/ft_strlen.c\
		libft/ft_putchar.c\
		libft/ft_atoi.c\
		libft/ft_isdigit.c\
		libft/ft_memset.c\
		libft/ft_putstr.c\
		libft/ft_strcpy.c\
		libft/ft_strdup.c\
		libft/ft_strjoin.c\
		libft/ft_strnew.c\
		libft/ft_strcmp.c\


NAME = libftprintf.a
CC = gcc
OBJ = $(SRC:.c=.o)
RM = rm -rf
FT = -L libft/ -lft 
CG = \033[92m
CY =  \033[93m
CE = \033[0m

all: $(NAME)
$(NAME): $(OBJ)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Creating Library$(CE)\033[1A";
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Compiled FT_PRINTF$(CE)";

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:
	@$(RM) $(OBJ)
	@make -C libft clean
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Cleaning Object files $(CE)";

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean
	@echo "\033[K$(CY)[FT_PRINTF] :$(CE) $(CG)Cleaning FT_PRINTF $(CE)";

re: fclean all

.PHONY : all clean fclean re

