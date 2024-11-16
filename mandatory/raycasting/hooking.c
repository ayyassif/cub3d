/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:00:56 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/16 18:12:48 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	key_pressed(keys_t key, t_cub *cub)
{
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
}

static void	key_released(keys_t key, t_cub *cub)
{
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
	mlx_delete_image(cub->mlx.mlx_handle, cub->mlx.img);
	free_cub(cub);
	exit(0);
}

void	key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keydata.key == MLX_KEY_ESCAPE)
		esc_exit(cub);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		key_pressed(keydata.key, cub);
	else if (keydata.action == MLX_RELEASE)
		key_released(keydata.key, cub);
}
