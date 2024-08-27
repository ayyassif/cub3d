# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 10:44:54 by hakaraou          #+#    #+#              #
#    Updated: 2024/08/27 14:07:46 by hakaraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address# -O3

NAME = cub3D

B_NAME = cub3d_bonus

SRC = mandatory/ft_write_test.c \
	mandatory/main.c \
	mandatory/pars/get_next_line.c mandatory/pars/get_next_line_utils.c \
	mandatory/pars/ft_pars.c mandatory/pars/set_param.c\
	mandatory/utils/libft_str.c mandatory/utils/libft_ptr_0.c mandatory/utils/libft_ptr_1.c \
	mandatory/utils/cond.c \
	

H_SRC = mandatory/cub3d.h mandatory/pars/get_next_line.h

B_SRC =

HB_SRC =

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

mandatory/%.o: mandatory/%.c $(H_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

bonus : $(B_NAME)

$(B_NAME) : $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(B_NAME)

bonus/%.o: bonus/%.c $(HB_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJ) $(B_OBJ)

fclean : clean
	rm -f $(NAME) $(B_NAME)
	
re : fclean all

.PHONY : all clean fclean re bonus