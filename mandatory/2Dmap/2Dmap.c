/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/01 12:14:23 by hakaraou         ###   ########.fr       */
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
	y = pos.y - 4;
	while (y <= pos.y + 4)
	{
		x = pos.x - 4;
		while (x <= pos.x + 4)
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

static void	key_hook(void *v_cub)
{
	t_cub	*cub;
	int		speed;
	t_vec	pos;

	speed = 4;
	cub = (t_cub *)v_cub;
	pos = player_pos(0, 0, 0, cub);
	if (mlx_is_key_down(cub->s_map.mlx_s_map, MLX_KEY_A))
		cub->pos.x -= speed;
	if (mlx_is_key_down(cub->s_map.mlx_s_map, MLX_KEY_D))
		cub->pos.x += speed;
	if (mlx_is_key_down(cub->s_map.mlx_s_map, MLX_KEY_W))
		cub->pos.y -= speed;
	if (mlx_is_key_down(cub->s_map.mlx_s_map, MLX_KEY_S))
		cub->pos.y += speed;
	if ((cub->pos.y / TILE_SIZE) < cub->height
		&& (cub->pos.x / TILE_SIZE) < cub->width
		&& cub->map[cub->pos.y / TILE_SIZE][cub->pos.x / TILE_SIZE].value
		== E_EMPTY)
		player_pos(cub->pos.x, cub->pos.y, 1, cub);
	draw_s_map_1(cub);
	player_square_draw(cub);
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
	return ;
}

static void	draw_player(t_cub *cub)
{
	player_square_draw(cub);
	mlx_loop_hook(cub->s_map.mlx_s_map, key_hook, cub);
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
