/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:05:44 by ayyassif          #+#    #+#             */
/*   Updated: 2024/10/05 11:07:46 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_collision(t_type value)
{
	if (value == M_WALL || value == M_DOOR_CLOSED)
		return (1);
	return (0);
}

static void	draw_s_map(t_cub *cub)
{
	t_vec	start;
	t_vec	end;
	t_vec	tmp;
	int		color;

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
			{
				color = 0xff000000;
				if (cub->map[(int)tmp.y][(int)tmp.x].value == M_FLOOR)
					color = create_rgb(cub->floor.red, cub->floor.green, cub->floor.blue);
				else if (cub->map[(int)tmp.y][(int)tmp.x].value == M_WALL)
					color = create_rgb(100, 150, 100);
				else if (cub->map[(int)tmp.y][(int)tmp.x].value == M_DOOR_CLOSED || cub->map[(int)tmp.y][(int)tmp.x].value == M_DOOR_OPEN)
					color = create_rgb(139, 69, 19);
				draw_square(cub, ((int)tmp.x - start.x + 1) * TILE_SIZE, ((int)tmp.y - start.y + 1) * TILE_SIZE, color);
			}
			tmp.x++;
		}
		tmp.y++;
	}
	player_square_draw(cub);
}

static void	wall_coll(t_cub *cub, t_vec new_pos, t_vec map_cords)
{
	t_vec	d;
	t_vec	inc;
	double	step;
	int		i;

	d.x = (new_pos.x - cub->pos.x) / (double)TILE_SIZE;
	d.y = (new_pos.y - cub->pos.y) / (double)TILE_SIZE;
	step = fmax(fabs(d.x), fabs(d.y));
	inc.x = (d.x / step) / (double)TILE_SIZE;
	inc.y = (d.y / step) / (double)TILE_SIZE;
	d.x = new_pos.x / (double)TILE_SIZE;
	d.y = new_pos.y / (double)TILE_SIZE;
	i = -1;
	while (++i < step)
	{
		if (!is_collision(cub->map[(int)d.y][(int)map_cords.x].value))//hna zid 7ta lbab
			d.y += inc.y;
		if (!is_collision(cub->map[(int)map_cords.y][(int)d.x].value))
			d.x += inc.x;
	}
	if (!is_collision(cub->map[(int)d.y][(int)map_cords.x].value))
		cub->pos.y = new_pos.y;
	if (!is_collision(cub->map[(int)map_cords.y][(int)d.x].value))
		cub->pos.x = new_pos.x;
}

void	map_background(t_cub *cub)
{
	mlx_texture_t* texture = mlx_load_png("mandatory/textures/map_frame.png");
	int	map_height;
	int	map_width;
	
	map_height = (M_MAP * 2 + 1) * TILE_SIZE;
	map_width = (M_MAP * 2 + 1) * TILE_SIZE;
	if (!texture)
		exit(1);
	int	y = -1;
	while (++y < map_height)
	{
		int	x = -1;
			double t_y = y / (double)map_height;
			t_y *= texture->height;
		while (++x < map_width)
		{
			double t_x = x / (double)map_width;
			t_x *= texture->width;
			int index = ((int)t_y * texture->width + (int)t_x) * 4;
			if (texture->pixels[index + 4] != 0)
				ft_put_pixel(cub->s_map.img_s_map, x, y, color_from_pixel(texture, index));
		}
	}
}

static void	move_process(t_cub *cub, t_vec *velo)
{
	t_vec	new_pos;
	double	move_speed;
	t_vec	map_cords;

	map_cords.x = cub->pos.x / TILE_SIZE;
	map_cords.y = cub->pos.y / TILE_SIZE;
	if (velo)
	{
		move_speed = SPEED * cub->s_map.mlx_s_map->delta_time;
		new_pos.x = cub->pos.x + velo->x * move_speed;
		new_pos.y = cub->pos.y + velo->y * move_speed;
		wall_coll(cub, new_pos, map_cords);
	}
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	cub->perp_wall_dist = 0;
	ray_casting(cub);
	map_background(cub);
	draw_s_map(cub);
	dda(cub->direction, cub, create_rgb(0, 255, 0));
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
}

static t_vec	vec_rotation(t_vec vec, double theta)
{
	t_vec	prime_vec;

	theta = theta * (M_PI / 180);
	prime_vec.x = vec.x * (double)cosf(theta) - vec.y * (double)sinf(theta);
	prime_vec.y = vec.x * (double)sinf(theta) + vec.y * (double)cosf(theta);
	return (prime_vec);
}

void	mouse_hook(t_cub *cub)
{
	int	w_center;

	w_center = WIDTH / 2;
	mlx_get_mouse_pos(cub->s_map.mlx_s_map, &cub->x_cursor, &cub->y_cursor);
	if (cub->x_cursor > w_center)
		cub->pressed_down.turn_left_right = 1;
	else if (cub->x_cursor < w_center)
		cub->pressed_down.turn_left_right = -1;
	else if (cub->is_rot_pressed == 0)
		cub->pressed_down.turn_left_right = 0;
	mlx_set_mouse_pos(cub->s_map.mlx_s_map, WIDTH / 2, HEIGHT / 2);
}

void	loop_hook(void *v_cub)
{
	t_cub	*cub;
	t_vec	velocity;
	int		theta;

	cub = (t_cub *)v_cub;
	if (cub->start == 0)
		return ;
	if (cub->pressed_down.turn_left_right)
	{
		cub->direction = vec_rotation(cub->direction,
				cub->pressed_down.turn_left_right * ROT_ANG * cub->s_map.mlx_s_map->delta_time);
		cub->cam_plane = vec_rotation(cub->cam_plane,
				cub->pressed_down.turn_left_right * ROT_ANG * cub->s_map.mlx_s_map->delta_time);
	}
	theta = cub->pressed_down.left_right * 90;
	if (cub->pressed_down.frwd_bckwd && cub->pressed_down.left_right)
		theta = theta + cub->pressed_down.frwd_bckwd * theta / 2;
	else if (cub->pressed_down.frwd_bckwd == 1)
		theta = 180;
	velocity = vec_rotation(cub->direction, theta);
	if (cub->pressed_down.frwd_bckwd != -1 && theta == 0)
		move_process(cub, NULL);
	else
		move_process(cub, &velocity);
	mouse_hook(cub);
}
