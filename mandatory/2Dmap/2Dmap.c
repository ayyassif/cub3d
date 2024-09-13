/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/13 19:54:25 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int switchxd = 0;

static int32_t	create_rgb(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	ft_put_pixel(mlx_image_t *image, uint32_t x,
	uint32_t y, uint32_t color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

static void	draw_square(t_cub *cub, int x, int y, int32_t color)
{
	int	x_max;
	int	y_max;
	int	x_tmp;

	x_tmp = x;
	x_max = x + cub->tile_size;
	y_max = y + cub->tile_size;
	while (y < y_max)
	{
		x = x_tmp;
		while (x < x_max)
		{
			if (x == x_max - cub->tile_size || y == y_max - cub->tile_size)
				ft_put_pixel(cub->s_map.img_s_map, x, y,
					create_rgb(0, 150, 0, 255));
			else
				ft_put_pixel(cub->s_map.img_s_map, x, y, color);
			x++;
		}
		y++;
	}
}

static t_vec	player_pos(int x, int y, int type, t_cub *cub)
{
	if (type == 1)
	{
		cub->pos.x = x;
		cub->pos.y = y;
	}
	return (cub->pos);
}

static void	draw_s_map(t_cub *cub)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			draw_square(cub, x * cub->tile_size,
				y * cub->tile_size, create_rgb(0, 0, 0, 255));
			if (cub->map[y][x].value == M_WALL)
				draw_square(cub, x * cub->tile_size,
					y * cub->tile_size, create_rgb(100, 150, 100, 255));
			else if (is_player(cub->map[y][x].value))
			{
				player_pos (x * cub->tile_size + cub->tile_size / 2, y * cub->tile_size + cub->tile_size / 2, 1, cub);
				cub->map[y][x].value = M_FLOOR;
			}
			x++;
		}
		y++;
	}
}

static void	player_square_draw(t_cub *cub)
{
	t_vec		pos;
	size_t		x;
	size_t		y;

	pos = cub->pos;
	y = pos.y;
	while (y <= pos.y + 1)
	{
		x = pos.x;
		while (x <= pos.x + 1)
		{
			ft_put_pixel(cub->s_map.img_s_map, x, y, create_rgb(255, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void	key_pressed(keys_t key, t_cub *cub)
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

void	key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;

	puts("hi");
	cub = (t_cub *)v_cub;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0); //to free
	if (keydata.action == MLX_PRESS)
		key_pressed(keydata.key, cub);
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_LEFT || keydata.key ==  MLX_KEY_RIGHT)
			cub->pressed_down.turn_left_right = 0;
		else if (keydata.key == 'A' || keydata.key == 'D')
			cub->pressed_down.left_right = 0;
		else if (keydata.key == 'W' || keydata.key == 'S')
			cub->pressed_down.frwd_bckwd = 0;
	}
}

// void	vec_normalize(t_vec *vec)
// {
// 	double	length;

// 	length = sqrtf(vec->x * vec->x + vec->y * vec->y);
// 	vec->x = vec->x / length;
// 	vec->y = vec->y / length;
// }

t_vec	vec_rotation(t_vec vec, double theta)
{
	t_vec	prime_vec;
	
	theta = theta * (M_PI / 180);
	prime_vec.x = vec.x * (double)cosf(theta) - vec.y * (double)sinf(theta);
	prime_vec.y = vec.x * (double)sinf(theta) + vec.y * (double)cosf(theta);
	return (prime_vec);
}

void	dda(t_vec pos, t_vec vec, t_cub *cub, int32_t color)
{
	double	step;
	double	x_inc;
	double	y_inc;
	int		i;

	i = 0;
	step = fmax(fabs(vec.x), fabs(vec.y));
	x_inc = vec.x / step;
	y_inc = vec.y / step;
	while (i < step * 10)
	{
		pos.x = pos.x + x_inc;
		pos.y = pos.y + y_inc;
		ft_put_pixel(cub->s_map.img_s_map, pos.x, pos.y, color);
		i++;
	}
}

t_vec	vec_multiply(t_vec vec, double multiplier)
{
	vec.x = vec.x * multiplier;
	vec.y = vec.y * multiplier;
	return (vec);
}

t_vec	side_dist_setter(t_vec ray, t_vec *map_cords, t_vec delta_dist, t_vec *step)
{
	t_vec	side_dist;

	if (ray.x < 0)
	{
		step->x = -1;
		side_dist.x = (map_cords->x - (int)map_cords->x) * delta_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist.x = ((int)map_cords->x + 1 - map_cords->x) * delta_dist.x;
	}
	if (ray.y < 0)
	{
		step->y = -1;
		side_dist.y = (map_cords->y - (int)map_cords->y) * delta_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist.y = ((int)map_cords->y + 1 - map_cords->y) * delta_dist.y;
	}
	map_cords->x = (int)map_cords->x;
	map_cords->y = (int)map_cords->y;
	return (side_dist);
}

double	ray_dda(t_cub *cub, t_vec delta_dist, t_vec map_cords, t_vec ray)
{
	int		side;
	t_vec	side_dist;
	t_vec	step;
	double	perp_wall_dist;

	side_dist = side_dist_setter(ray, &map_cords, delta_dist, &step);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_cords.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_cords.y += step.y;
			side = 1;
		}
		// why tho?
		if (cub->map[(int)map_cords.y][(int)map_cords.x].value == M_WALL)
			break ;
	}
	//printf("ray: y: %d\tx: %d\n", (int)map_cords.y, (int)map_cords.x);
	if (side == 0 && ray.x > 0)
		cub->line_color = create_rgb(255, 0, 0, 255);
	else if (side == 0)
		cub->line_color = create_rgb(0, 255, 0, 255);
	else if (ray.y > 0)
		cub->line_color = create_rgb(0, 0, 255, 255);
	else
		cub->line_color = create_rgb(255, 255, 0, 255);
	if (side == 0)
		perp_wall_dist = (side_dist.x - delta_dist.x);
	else
		perp_wall_dist = (side_dist.y - delta_dist.y);
	return (perp_wall_dist);
}

double	ray_distance(t_cub *cub, t_vec ray)
{
	t_vec	map_cords;
	t_vec	delta_dist;

	map_cords.x = cub->pos.x / cub->tile_size;
	map_cords.y = cub->pos.y / cub->tile_size;
	if (ray.x)
		delta_dist.x = fabs(1 / ray.x);
	else
		delta_dist.x = INFINITY;
	if (ray.y)
		delta_dist.y = fabs(1 / ray.y);
	else
		delta_dist.y = INFINITY;
	return (ray_dda(cub, delta_dist, map_cords, ray));
}

void	verline(t_cub *cub, int drawStart, int drawEnd, int x)
{
	while (drawEnd >= drawStart)
	{
		ft_put_pixel(cub->s_map.img_s_map, x, drawStart, cub->line_color);
		drawStart++;
	}
}

void	ray_casting(t_cub *cub, double perp_wall_dist)
{
	double	camera_x;
	t_vec	ray;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray.x = (cub->direction.x + cub->cam_plane.x * camera_x);
		ray.y = (cub->direction.y + cub->cam_plane.y * camera_x);
		perp_wall_dist = ray_distance(cub, ray);
		if (perp_wall_dist < 1)
			perp_wall_dist = 1;
		lineHeight = (int)(HEIGHT/ perp_wall_dist) + WIDTH / HEIGHT * 2;
		drawStart = (HEIGHT - lineHeight) / 2;
		drawEnd = drawStart + lineHeight;
		verline(cub, drawStart, drawEnd, x);
	}
}

int	is_wall_coll(t_cub cub ,double v1, double v2, double len)
{
	return ((int)(v1 + len) < cub.height && (int)(v1 - len) < cub.height
		&& cub.map[(int)(v1 + len)][(int)(v2 + len)].value != M_WALL
		&& cub.map[(int)(v1 - len)][(int)(v2 + len)].value != M_WALL
		&& cub.map[(int)(v1 + len)][(int)(v2 - len)].value != M_WALL
		&& cub.map[(int)(v1 + len)][(int)(v2 - len)].value != M_WALL);
}

void	move_process(t_cub *cub, t_vec *velo)
{
	t_vec	new_pos;
	double	move_speed;
	double	perp_wall_dist;

	if (velo)
	{
		move_speed = SPEED * cub->s_map.mlx_s_map->delta_time;
		new_pos.x = cub->pos.x + velo->x * move_speed;
		new_pos.y = cub->pos.y + velo->y * move_speed;
		if (is_wall_coll(*cub, new_pos.y / cub->tile_size, cub->pos.x / cub->tile_size, 0.01))
			cub->pos.y = new_pos.y;
		if (is_wall_coll(*cub, cub->pos.y / cub->tile_size, new_pos.x / cub->tile_size, 0.01))
			cub->pos.x = new_pos.x;
	}
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	perp_wall_dist = 0;
	ray_casting(cub, perp_wall_dist);
	draw_s_map(cub);
	player_square_draw(cub);
	dda(cub->pos ,cub->direction, cub, create_rgb(0, 255, 0, 255));
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
}


void	loop_hook(void *v_cub)
{
	t_cub	*cub;
	t_vec	velocity;
	int		theta;

	cub = (t_cub *)v_cub;
	if (cub->pressed_down.turn_left_right)
	{
		cub->direction = vec_rotation(cub->direction,
			cub->pressed_down.turn_left_right * ROT_ANG);
		cub->cam_plane = vec_rotation(cub->cam_plane,
			cub->pressed_down.turn_left_right * ROT_ANG);
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
}

static void	draw_player(t_cub *cub)
{
	mlx_key_hook(cub->s_map.mlx_s_map, key_func, cub);
	mlx_loop_hook(cub->s_map.mlx_s_map, loop_hook, cub);
}

int	mini_map(t_cub *cub)
{
	cub->s_map.img_s_map = NULL;
	cub->s_map.mlx_s_map = mlx_init(WIDTH, HEIGHT, "Cub3d_2Dmap", false);
	if (!cub->s_map.mlx_s_map)
		return (-1);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	if (!cub->s_map.img_s_map)
		return (-1);
	draw_player(cub);
	mlx_loop(cub->s_map.mlx_s_map);
	return (0);
}
