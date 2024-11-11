/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:00:56 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/11 20:36:39 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_hook(t_cub *cub)
{
	int	w_center;

	w_center = WIDTH / 2;
	mlx_get_mouse_pos(cub->s_map.mlx_s_map, &cub->x_cursor, &cub->y_cursor);
	if (!cub->is_rot_pressed)
	{
		if (cub->x_cursor > w_center)
			cub->pressed_down.turn_left_right = 1;
		else if (cub->x_cursor < w_center)
			cub->pressed_down.turn_left_right = -1;
		else
			cub->pressed_down.turn_left_right = 0;
	}
	mlx_set_mouse_pos(cub->s_map.mlx_s_map, WIDTH / 2, HEIGHT / 2);
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

static void	key_released(keys_t key, t_cub *cub)
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

static void	esc_exit(t_cub *cub)
{
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	free_cub(cub);
	exit(0);
}

void	key_func(mlx_key_data_t keydata, void *v_cub)
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
