/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/04 14:45:03 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	door_interaction(t_cub *cub)
{
	double	f_x;
	double	f_y;
	double	d_x;
	double	d_y;
	double	distance;

	f_x = (int)cub->focused.x + 0.5;
	f_y = (int)cub->focused.y + 0.5;
	if (f_x == -1)
		return ;
	d_x = cub->pos.x / TILE_SIZE - f_x;
	d_y = cub->pos.y / TILE_SIZE - f_y;
	distance = sqrt(d_x * d_x + d_y * d_y);
	if (distance > 3)
		return ;
	if (cub->map[(int)f_y][(int)f_x].value == M_DOOR_CLOSED)
		cub->map[(int)f_y][(int)f_x].value = M_DOOR_OPEN;
	else if (cub->map[(int)f_y][(int)f_x].value == M_DOOR_OPEN)
		cub->map[(int)f_y][(int)f_x].value = M_DOOR_CLOSED;
}

static void	key_pressed(keys_t key, t_cub *cub)
{
	if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
		cub->is_rot_pressed = 1;
	if (key == MLX_KEY_LEFT)
		cub->pressed_down.turn_left_right = -1;
	else if (key == MLX_KEY_RIGHT)
		cub->pressed_down.turn_left_right = 1;
	else if (key == 'A')
		cub->pressed_down.left_right = -1;
	else if (key == 'D')
		cub->pressed_down.left_right = 1;
	else if (key == 'W')
		cub->pressed_down.frwd_bckwd = -1;
	else if (key == 'S')
		cub->pressed_down.frwd_bckwd = 1;
	else if (key == 'E')
		door_interaction(cub);
}

static void	esc_exit(t_cub *cub)
{
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	free_cub(cub);
	exit(0);
}

void	key_released(keys_t key, t_cub *cub)
{
	if (key == MLX_KEY_RIGHT || key == MLX_KEY_LEFT)
		cub->is_rot_pressed = 0;
	if (key == MLX_KEY_RIGHT
		&& cub->pressed_down.turn_left_right == 1)
		cub->pressed_down.turn_left_right = 0;
	else if (key == MLX_KEY_LEFT
		&& cub->pressed_down.turn_left_right == -1)
		cub->pressed_down.turn_left_right = 0;
	else if (key == 'A' && cub->pressed_down.left_right == -1)
		cub->pressed_down.left_right = 0;
	else if (key == 'D' && cub->pressed_down.left_right == 1)
		cub->pressed_down.left_right = 0;
	else if (key == 'W' && cub->pressed_down.frwd_bckwd == -1)
		cub->pressed_down.frwd_bckwd = 0;
	else if (key == 'S' && cub->pressed_down.frwd_bckwd == 1)
		cub->pressed_down.frwd_bckwd = 0;
}

static void	key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keydata.key == MLX_KEY_ESCAPE)
		esc_exit(cub);
	if (keydata.key == MLX_KEY_ENTER)
		cub->start = 1;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		key_pressed(keydata.key, cub);
	else if (keydata.action == MLX_RELEASE)
		key_released(keydata.key, cub);
}

static int	hooking(t_cub *cub)
{
	mlx_key_hook(cub->s_map.mlx_s_map, key_func, cub);
	if (mlx_loop_hook(cub->s_map.mlx_s_map, loop_hook, cub) == false);
	{
		ft_putendl_fd("the hook was not added successfully", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	execution(t_cub *cub)
{
	cub->start = 0;
	cub->is_rot_pressed = 0;
	cub->s_map.img_s_map = NULL;
	cub->s_map.mlx_s_map = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!cub->s_map.mlx_s_map)
		return (-1);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	if (!cub->s_map.img_s_map)
		return (-1);
	mlx_set_cursor_mode(cub->s_map.mlx_s_map, MLX_MOUSE_HIDDEN);
	if (draw_image(cub, TX_INTRO,
		mlx_load_png("mandatory/textures/DON'T FORGET TO (1).png"))
		|| mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0))
		return (-1);
	hooking(cub);
	mlx_loop(cub->s_map.mlx_s_map);
	return (0);
}
