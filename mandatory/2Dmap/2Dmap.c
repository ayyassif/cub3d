/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/02 19:18:31 by hakaraou         ###   ########.fr       */
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
			if (x == x_max - TILE_SIZE || x == x_max - 1
				|| y == y_max - TILE_SIZE || y == y_max - 1)
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
			if (cub->map[y][x].value == E_BLOCK)
				draw_square(&cub->s_map, x * TILE_SIZE,
					y * TILE_SIZE, create_rgb(100, 150, 100, 255));
			else if (is_player(cub->map[y][x].value))
				player_pos (x * TILE_SIZE + TILE_SIZE / 2,
					y * TILE_SIZE + TILE_SIZE / 2, 1, cub);
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

static void	draw_s_map_1(t_cub *cub)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			draw_square(&cub->s_map, x * TILE_SIZE, y * TILE_SIZE,
				create_rgb(0, 0, 0, 255));
			if (cub->map[y][x].value == E_BLOCK)
				draw_square(&cub->s_map, x * TILE_SIZE, y * TILE_SIZE,
					create_rgb(100, 150, 100, 255));
			x++;
		}
		y++;
	}
}
void key_func(mlx_key_data_t keydata, void *v_cub)
{
	t_cub	*cub;
	int		speed;
	t_vec	pos;
	double	angle = 0;
// pos.x += (cos(cub->player_dir + angle) - sin(cub->player_dir + angle)) * speed;
		// pos.y += (cos(cub->player_dir + angle) + sin(cub->player_dir + angle)) * speed;
	speed = 10;
	cub = (t_cub *)v_cub;
	pos = player_pos(0, 0, 0, cub);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.action == 0)
		angle = 0;
	if (keydata.action == 2)
		keydata.action = 1;
	if (keydata.key == MLX_KEY_LEFT)
		cub->player_dir -= 0.02;
	if (keydata.key ==  MLX_KEY_RIGHT)
		cub->player_dir += 0.02;
	if (keydata.key == 'A' && keydata.action == 1)
		angle = - M_PI * 0.5;
	if (keydata.key == 'D' && keydata.action == 1)
		angle = M_PI * 0.5;
	if (keydata.key == 'W' && keydata.action == 1)
		angle = M_PI * 2;
	if (keydata.key == 'S' && keydata.action == 1)
		angle = M_PI;
	if (angle != 0)
	{
		pos.x += roundf(speed * cos(cub->player_dir + angle));
		pos.y += roundf(speed * sin(cub->player_dir + angle));
		printf("%f\n", angle);	
	}
	angle = 0;
	if ((pos.y / TILE_SIZE) < cub->height
		&& (pos.x / TILE_SIZE) < cub->width
		&& cub->map[pos.y / TILE_SIZE][pos.x / TILE_SIZE].value
		!= E_BLOCK)
		player_pos(pos.x, pos.y, 1, cub);	
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	draw_s_map_1(cub);
	player_square_draw(cub);
	for (int i = 0; i < 100; i++)
	{
		int x = cub->pos.x + i * cos(cub->player_dir);
		int y = cub->pos.y + i * sin(cub->player_dir);
		ft_put_pixel(cub->s_map.img_s_map, x, y, create_rgb(255, 155, 55, 255));
	}
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
	return ;
}

static void	draw_player(t_cub *cub)
{
	player_square_draw(cub);
	// mlx_loop_hook(cub->s_map.mlx_s_map, key_hook, cub);
	mlx_key_hook(cub->s_map.mlx_s_map, key_func, cub);
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
