# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 10:44:54 by hakaraou          #+#    #+#              #
#    Updated: 2024/11/16 13:49:14 by ayyassif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = cub3D

MLX_ARCHIVE = .MLX42/build/libmlx42.a

B_NAME = cub3d_bonus

SRC = mandatory/ft_write_test.c \
	mandatory/main.c \
	mandatory/get_next_line/get_next_line.c \
	mandatory/get_next_line/get_next_line_utils.c \
	mandatory/pars/check_param_0.c mandatory/pars/check_param_1.c \
	mandatory/pars/set_map_0.c mandatory/pars/set_map_1.c \
	mandatory/pars/ft_pars.c mandatory/pars/set_param.c \
	mandatory/raycasting/tex_color.c mandatory/raycasting/hooking.c \
	mandatory/raycasting/draw.c mandatory/raycasting/execution.c \
	mandatory/raycasting/loop_hook.c mandatory/raycasting/ray_casting.c \
	mandatory/raycasting/collision.c \
	mandatory/utils/libft_str.c mandatory/utils/libft_ptr_0.c \
	mandatory/utils/libft_ptr_1.c mandatory/utils/cond.c \
	mandatory/utils/ft_free.c \

H_SRC = mandatory/cub3d.h mandatory/get_next_line/get_next_line.h

B_SRC =

HB_SRC =

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

all: mlx $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_ARCHIVE) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ) -o $(NAME)

mlx:
	@cd .MLX42 && cmake -B build && cmake --build build -j4

mandatory/%.o: mandatory/%.c $(H_SRC)
	@$(CC) $(CFLAGS) -c -o $@ $<

bonus: $(B_NAME)

$(B_NAME): $(B_OBJ)
	@$(CC) $(CFLAGS) $(B_OBJ) -o $(B_NAME)

bonus/%.o: bonus/%.c $(HB_SRC)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ) $(B_OBJ)
	@cd .MLX42/build && make clean

fclean: clean
	@rm -rf $(NAME) $(B_NAME) .MLX42/build

re: fclean all

.PHONY: clean