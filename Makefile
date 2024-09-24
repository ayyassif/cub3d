# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 10:44:54 by hakaraou          #+#    #+#              #
#    Updated: 2024/09/24 19:31:34 by hakaraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror # -O3

NAME = cub3D

B_NAME = cub3d_bonus

SRC = mandatory/ft_write_test.c \
	mandatory/main.c \
	mandatory/get_next_line/get_next_line.c \
	mandatory/get_next_line/get_next_line_utils.c \
	mandatory/pars/ft_pars.c mandatory/pars/set_param.c \
	mandatory/pars/set_map_0.c mandatory/pars/set_map_1.c \
	mandatory/pars/check_param_0.c mandatory/pars/check_param_1.c \
	mandatory/utils/libft_str.c mandatory/utils/libft_ptr_0.c \
	mandatory/utils/libft_ptr_1.c mandatory/utils/cond.c \
	mandatory/utils/ft_free.c \
	mandatory/raycasting/draw.c mandatory/raycasting/execution.c \
	mandatory/raycasting/loop_hook.c mandatory/raycasting/ray_casting.c \
	mandatory/raycasting/tex_color.c \
	
	

H_SRC = mandatory/cub3d.h mandatory/get_next_line/get_next_line.h

B_SRC =

HB_SRC =

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

all : $(NAME) clean

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ) -o $(NAME)

mandatory/%.o: mandatory/%.c $(H_SRC)
	@$(CC) $(CFLAGS) -c -o $@ $<

bonus : $(B_NAME)

$(B_NAME) : $(B_OBJ)
	@$(CC) $(CFLAGS) $(B_OBJ) -o $(B_NAME)

bonus/%.o: bonus/%.c $(HB_SRC)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean :
	@rm -f $(OBJ) $(B_OBJ)

fclean : clean
	@rm -f $(NAME) $(B_NAME)
	
re : fclean all

.PHONY : all clean fclean re bonus