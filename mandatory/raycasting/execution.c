/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/22 16:41:23 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_rgb(int t, int r, int g)
{
	return (t << 24 | r << 16 | g << 8 | 255);
}

static void	key_pressed(keys_t key, t_cub *cub)
{
	if (key == MLX_KEY_LEFT)
		cub->pressed_down.turn_left_right = -1;
	else if (key ==  MLX_KEY_RIGHT)
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

static void	key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0); //to free
	if (keydata.action == MLX_PRESS)
		key_pressed(keydata.key, cub);
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_RIGHT && cub->pressed_down.turn_left_right == 1)
			cub->pressed_down.turn_left_right = 0;
		else if (keydata.key == MLX_KEY_LEFT && cub->pressed_down.turn_left_right == -1)
			cub->pressed_down.turn_left_right = 0;
		else if (keydata.key == 'A' && cub->pressed_down.left_right == -1)
			cub->pressed_down.left_right = 0;
		else if (keydata.key == 'D' && cub->pressed_down.left_right == 1)
			cub->pressed_down.left_right = 0;
		else if (keydata.key == 'W' && cub->pressed_down.frwd_bckwd == -1)
			cub->pressed_down.frwd_bckwd = 0;
		else if (keydata.key == 'S' && cub->pressed_down.frwd_bckwd == 1)
			cub->pressed_down.frwd_bckwd = 0;
	}
}

static void	hooking(t_cub *cub)
{
	mlx_key_hook(cub->s_map.mlx_s_map, key_func, cub);
	mlx_loop_hook(cub->s_map.mlx_s_map, loop_hook, cub);
}

int	execution(t_cub *cub)
{	
	cub->s_map.img_s_map = NULL;
	cub->s_map.mlx_s_map = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!cub->s_map.mlx_s_map)
		return (-1);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	if (!cub->s_map.img_s_map)
		return (-1);
	set_tex(cub);
	hooking(cub);
	mlx_loop(cub->s_map.mlx_s_map);
	return (0);
}
