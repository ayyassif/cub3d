/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:29:57 by ayyassif          #+#    #+#             */
/*   Updated: 2024/09/14 15:14:07 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_put_pixel(mlx_image_t *image, uint32_t x,
	uint32_t y, uint32_t color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

void	draw_square(t_cub *cub, int x, int y, int color)
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
					create_rgb(0, 150, 0));
			else
				ft_put_pixel(cub->s_map.img_s_map, x, y, color);
			x++;
		}
		y++;
	}
}

void	player_square_draw(t_cub *cub)
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
			ft_put_pixel(cub->s_map.img_s_map, x, y, create_rgb(255, 0, 0));
			x++;
		}
		y++;
	}
}

void	dda(t_vec pos, t_vec vec, t_cub *cub, int color)
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

void	ver_line(t_cub *cub, int drawStart, int drawEnd, int x)
{
	int	i;

	i = -1;
	while (++i < drawStart)
		ft_put_pixel(cub->s_map.img_s_map, x, i, create_rgb(0, 0, 0));
	while (drawEnd >= ++drawStart)
		ft_put_pixel(cub->s_map.img_s_map, x, drawStart, cub->line_color);
	while (++drawEnd < HEIGHT)
		ft_put_pixel(cub->s_map.img_s_map, x, drawEnd, create_rgb(10, 127, 0));
}
