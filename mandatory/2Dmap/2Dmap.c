/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/09 14:57:55 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void	draw_square(t_s_map	*s_map, int x, int y, int32_t color)
{
	int	x_max;
	int	y_max;
	int	x_tmp;

	x_tmp = x;
	x_max = x + TILE_SIZE;
	y_max = y + TILE_SIZE;
	while (y < y_max)
	{
		x = x_tmp;
		while (x < x_max)
		{
			if (x == x_max - TILE_SIZE || y == y_max - TILE_SIZE)
				ft_put_pixel(s_map->img_s_map, x, y,
					create_rgb(0, 150, 0, 255));
			else
				ft_put_pixel(s_map->img_s_map, x, y, color);
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
			draw_square(&cub->s_map, x * TILE_SIZE,
				y * TILE_SIZE, create_rgb(0, 0, 0, 255));
			if (cub->map[y][x].value == M_WALL)
				draw_square(&cub->s_map, x * TILE_SIZE,
					y * TILE_SIZE, create_rgb(100, 150, 100, 255));
			else if (is_player(cub->map[y][x].value))
			{
				player_pos (x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE / 2, 1, cub);
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
			ft_put_pixel(cub->s_map.img_s_map, x, y,
				create_rgb(255, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_LEFT)
		{
			cub->pressed_down.is_turn_left = 1;
			cub->pressed_down.is_turn_right = 0;
		}
		else if (keydata.key ==  MLX_KEY_RIGHT)
		{
			cub->pressed_down.is_turn_left = 0;
			cub->pressed_down.is_turn_right = 1;
		}
		else if (keydata.key == 'A')
		{
			cub->pressed_down.is_left = 1;
			cub->pressed_down.is_right = 0;
		}
		else if (keydata.key == 'D')
		{
			cub->pressed_down.is_left = 0;
			cub->pressed_down.is_right = 1;
		}
		else if (keydata.key == 'W')
		{
			cub->pressed_down.is_bckwd = 0;
			cub->pressed_down.is_frwd = 1;
		}
		else if (keydata.key == 'S')
		{
			cub->pressed_down.is_bckwd = 1;
			cub->pressed_down.is_frwd = 0;
		}
	}
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_LEFT)
			cub->pressed_down.is_turn_left = 0;
		else if (keydata.key ==  MLX_KEY_RIGHT)
			cub->pressed_down.is_turn_right = 0;
		else if (keydata.key == 'A')
			cub->pressed_down.is_left = 0;
		else if (keydata.key == 'D')
			cub->pressed_down.is_right = 0;
		else if (keydata.key == 'W')
			cub->pressed_down.is_frwd = 0;
		else if (keydata.key == 'S')
			cub->pressed_down.is_bckwd = 0;
	}
}

void	vec_normalize(t_vec *vec)
{
	double	length;

	length = sqrtf(vec->x * vec->x + vec->y * vec->y);
	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

t_vec	vec_rotation(t_vec vec, double theta)
{
	t_vec	prime_vec;
	
	theta = theta * M_PI / 180;
	prime_vec.x = vec.x * (double)cosf(theta) - vec.y * (double)sinf(theta);
	prime_vec.y = vec.x * (double)sinf(theta) + vec.y * (double)cosf(theta);
	vec_normalize(&prime_vec);
	return (prime_vec);
}

double	dir_angle(t_vec dir)
{
	return ((double)acosf(dir.y / (double)sqrtf(dir.x * dir.x + dir.y * dir.y)));
}

void	dda(t_vec vec, t_cub *cub)
{
	double	step;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;

	step = fmax(fabs(vec.x), fabs(vec.y));
	x_inc = vec.x / step;
	y_inc = vec.y / step; 
	x = cub->pos.x;
	y = cub->pos.y;
	for (int i = 0; i < 100; i++)
	{
		x = x + x_inc;
		y = y + y_inc;
		ft_put_pixel(cub->s_map.img_s_map, x, y, create_rgb(255, 155, 55, 255));
	}
}


void	move_process(t_cub *cub, double x, double y)
{
	t_vec	new_pos;

	new_pos.x = cub->pos.x + x * SPEED;
	new_pos.y = cub->pos.y + y * SPEED;
	if (new_pos.y / TILE_SIZE < cub->height
		&& cub->map[(int)new_pos.y / TILE_SIZE][(int)cub->pos.x / TILE_SIZE].value
		!= M_WALL)
		cub->pos.y = new_pos.y;
	if (new_pos.x / TILE_SIZE < cub->width
		&& cub->map[(int)cub->pos.y / TILE_SIZE][(int)new_pos.x / TILE_SIZE].value
		!= M_WALL)
		cub->pos.x = new_pos.x;
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	draw_s_map(cub);
	player_square_draw(cub);
	dda(cub->direction, cub); 
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
}


void	loop_hook(void *v_cub)
{
	t_cub	*cub;
	t_vec	velocity;
	int		theta;

	cub = (t_cub *)v_cub;
	velocity = cub->direction;
	if (cub->pressed_down.is_turn_left)
		cub->direction = vec_rotation(cub->direction, 1);
	if (cub->pressed_down.is_turn_right)
		cub->direction = vec_rotation(cub->direction, -1);
	velocity = cub->direction;
	theta = 0;
	if (cub->pressed_down.is_right)
		theta = 90;
	if (cub->pressed_down.is_left)
		theta = -90;
	if (cub->pressed_down.is_bckwd && (cub->pressed_down.is_right || cub->pressed_down.is_left))
		theta = theta + theta / 2;
	else if (cub->pressed_down.is_bckwd)
		theta = 180;
	if (cub->pressed_down.is_frwd && (cub->pressed_down.is_right || cub->pressed_down.is_left))
		theta = theta - theta / 2;
	velocity = vec_rotation(cub->direction, theta);
	if (!cub->pressed_down.is_frwd && theta == 0)
		move_process(cub, 0, 0);
	else
		move_process(cub, velocity.x, velocity.y);
}

static void	draw_player(t_cub *cub)
{
	player_square_draw(cub);
	printf("x:%.2f\ty:%.2f\n", cub->direction.x, cub->direction.y);
	mlx_key_hook(cub->s_map.mlx_s_map, key_func, cub);
	mlx_loop_hook(cub->s_map.mlx_s_map, loop_hook, cub);
}

int	mini_map(t_cub *cub)
{
	cub->pos.x = 60;
	cub->pos.y = 60;
	cub->s_map.img_s_map = NULL;
	cub->s_map.mlx_s_map = mlx_init(WIDTH, HEIGHT, "Cub3d_2Dmap", false);
	if (!cub->s_map.mlx_s_map)
		return (-1);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	if (!cub->s_map.img_s_map)
		return (-1);
	draw_s_map(cub);
	draw_player(cub);
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
	mlx_loop(cub->s_map.mlx_s_map);
	return (0);
}
