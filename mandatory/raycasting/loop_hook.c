/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:05:44 by ayyassif          #+#    #+#             */
/*   Updated: 2024/11/21 12:04:15 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_window(t_cub *cub)
{
	mlx_delete_image(cub->mlx.mlx_handle, cub->mlx.img);
	cub->mlx.img = mlx_new_image(cub->mlx.mlx_handle, WIDTH, HEIGHT);
	if (!cub->mlx.img)
		return (-1);
	ray_casting(cub);
	if (mlx_image_to_window(cub->mlx.mlx_handle, cub->mlx.img, 0, 0))
		return (-1);
	return (0);
}

static void	move_process(t_cub *cub, t_vec velo)
{
	t_vec	new_pos;
	double	move_speed;
	t_vec	map_cords;

	map_cords.x = cub->pos.x / TILE_SIZE;
	map_cords.y = cub->pos.y / TILE_SIZE;
	move_speed = SPEED * cub->mlx.mlx_handle->delta_time;
	new_pos.x = cub->pos.x + velo.x * move_speed;
	new_pos.y = cub->pos.y + velo.y * move_speed;
	wall_coll(cub, new_pos, map_cords);
}

static t_vec	vec_rotation(t_vec vec, double theta)
{
	t_vec	prime_vec;

	theta = theta * (M_PI / 180);
	prime_vec.x = vec.x * (double)cosf(theta) - vec.y * (double)sinf(theta);
	prime_vec.y = vec.x * (double)sinf(theta) + vec.y * (double)cosf(theta);
	return (prime_vec);
}

void	rotation(t_cub *cub)
{
	if (cub->pressed_down.turn_left_right)
	{
		cub->direction = vec_rotation(cub->direction,
				cub->pressed_down.turn_left_right * ROT_ANG
				* cub->mlx.mlx_handle->delta_time);
		cub->cam_plane = vec_rotation(cub->cam_plane,
				cub->pressed_down.turn_left_right * ROT_ANG
				* cub->mlx.mlx_handle->delta_time);
	}
}

void	loop_hook(void *v_cub)
{
	t_cub	*cub;
	t_vec	velocity;
	int		theta;

	cub = (t_cub *)v_cub;
	rotation(cub);
	theta = cub->pressed_down.left_right * 90;
	if (cub->pressed_down.frwd_bckwd && cub->pressed_down.left_right)
		theta = theta + cub->pressed_down.frwd_bckwd * theta / 2;
	else if (cub->pressed_down.frwd_bckwd == 1)
		theta = 180;
	velocity = vec_rotation(cub->direction, theta);
	if (!(cub->pressed_down.frwd_bckwd != -1 && theta == 0))
		move_process(cub, velocity);
	if (fill_window(cub))
	{
		mlx_delete_image(cub->mlx.mlx_handle, cub->mlx.img);
		free_cub(cub);
		exit(-1);
	}
}
