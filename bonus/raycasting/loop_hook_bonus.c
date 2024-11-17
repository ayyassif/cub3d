/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:05:44 by ayyassif          #+#    #+#             */
/*   Updated: 2024/11/17 15:48:28 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	map_square(t_cub *cub, t_vec tmp, t_vec	start)
{
	int		color;

	color = 0xff000000;
	if (cub->map[(int)tmp.y][(int)tmp.x] == M_FLOOR)
		color = create_rgb(cub->floor.red,
				cub->floor.green, cub->floor.blue);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_WALL)
		color = create_rgb(100, 150, 100);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_DOOR_CLOSED)
		color = create_rgb(200, 50, 50);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_DOOR_OPEN)
		color = create_rgb(150, 25, 25);
	draw_square(cub, ((int)tmp.x - start.x + 1) * TILE_SIZE,
		((int)tmp.y - start.y + 1) * TILE_SIZE, color);
}

static void	draw_s_map(t_cub *cub)
{
	t_vec	start;
	t_vec	end;
	t_vec	tmp;

	start.x = cub->pos.x / TILE_SIZE - M_MAP;
	start.y = cub->pos.y / TILE_SIZE - M_MAP;
	end.x = cub->pos.x / TILE_SIZE + M_MAP;
	end.y = cub->pos.y / TILE_SIZE + M_MAP;
	tmp.y = start.y;
	while (tmp.y < end.y)
	{
		tmp.x = start.x;
		while (tmp.x < end.x)
		{
			if (tmp.y >= 0 && tmp.y <= cub->height
				&& tmp.x >= 0 && tmp.x <= cub->width)
				map_square(cub, tmp, start);
			tmp.x++;
		}
		tmp.y++;
	}
	player_square_draw(cub);
}

void	tx_loop(t_cub *cub, t_vec size, t_vec start, mlx_texture_t *texture)
{
	int		y;
	int		x;
	int		index;
	double	t_y;
	double	t_x;

	y = -1;
	while (++y < size.y)
	{
		x = -1;
		t_y = y / (double)size.y;
		t_y *= texture->height;
		while (++x < size.x)
		{
			t_x = x / (double)size.x;
			t_x *= texture->width;
			index = ((int)t_y * texture->width + (int)t_x) * 4;
			if (texture->pixels[index + 4] != 0)
				ft_put_pixel(cub->mlx.img, x + start.x, y + start.y,
					color_from_pixel(texture, index));
		}
	}
	mlx_delete_texture(texture);
}

int	draw_image(t_cub *cub, t_tx_img tx_img, mlx_texture_t *texture)
{
	t_vec	start;
	t_vec	size;

	if (!texture)
		return (-1);
	start.x = 0;
	start.y = 0;
	size.y = HEIGHT;
	size.x = WIDTH;
	if (tx_img == TX_MAP)
	{
		size.y = (M_MAP * 2 + 1) * TILE_SIZE;
		size.x = size.y;
	}
	else if (tx_img == TX_ITEM)
	{
		size.y = texture->height - 1;
		size.x = texture->width - 1;
		start.x = WIDTH - size.x;
		start.y = HEIGHT - size.y;
	}
	tx_loop(cub, size, start, texture);
	return (0);
}

int	animat_items(t_cub *cub)
{
	static int		counter;
	static double	timer;

	timer += cub->mlx.mlx_handle->delta_time;
	if ((timer >= 0.16 && (cub->pressed_down.frwd_bckwd
				|| cub->pressed_down.left_right)) || timer >= 0.5)
	{
		counter++;
		if (counter > 31)
			counter = 0;
		cub->sword[34] = counter / 10 + '0';
		cub->sword[35] = counter % 10 + '0';
		if (cub->pressed_down.frwd_bckwd || cub->pressed_down.left_right)
			timer -= 0.16;
		else
			timer -= 0.5;
	}
	if (draw_image(cub, TX_ITEM, mlx_load_png(cub->sword)))
		return (-1);
	return (0);
}

int	fill_window(t_cub *cub)
{
	mlx_delete_image(cub->mlx.mlx_handle, cub->mlx.img);
	cub->mlx.img = mlx_new_image(cub->mlx.mlx_handle, WIDTH, HEIGHT);
	if (!cub->mlx.img)
		return (-1);
	ray_casting(cub);

	if (draw_image(cub, TX_MAP,
			mlx_load_png("bonus/textures/bonus/map_frame.png"))
		|| animat_items(cub))
		return (-1);
	draw_s_map(cub);
	dda(cub->direction, cub, create_rgb(0, 255, 0));
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
	if (cub->start == 0)
		return ;
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
	mouse_hook(cub);
}
