/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:29:57 by ayyassif          #+#    #+#             */
/*   Updated: 2024/09/26 23:00:48 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_cub *cub, double x, double y, int color)
{
	double	x_max;
	double	y_max;
	double	x_tmp;

	x_tmp = x;
	x_max = x + TILE_SIZE;
	y_max = y + TILE_SIZE;
	printf("%.2f\n", x / TILE_SIZE);
	while (y < y_max)
	{
		x = x_tmp;
		while (x < x_max)
		{
			if (x == x_max - TILE_SIZE || y == y_max - TILE_SIZE)
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
	size_t	x;
	size_t	y;
	size_t	pos;

	pos = (M_MAP + 0.5) * TILE_SIZE;
	y = pos;
	while (y <= pos + 1)
	{
		x = pos;
		while (x <= pos + 1)
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

static void	tex_to_wall(t_cub *cub, int drawStart, int tmp_start, int tmp_end)
{
	uint32_t	tmp_value;
	int			index;
	int			color;

	cub->tex_pos_y = (drawStart - tmp_start) / (double)(tmp_end - tmp_start);
	cub->tex_pos_y *= cub->texture[cub->tex_id].tex_png->height;
	tmp_value = (int)cub->tex_pos_y * cub->texture[cub->tex_id].tex_png->height;
	tmp_value += (int)cub->tex_pos_x;
	index = tmp_value * 4;
	color = color_from_pixel(cub->texture[cub->tex_id].tex_png, index);
	ft_put_pixel(cub->s_map.img_s_map, cub->x, drawStart, color);
}

void	ver_line(t_cub *cub, int drawStart, int drawEnd)
{
	int			i;
	int			tmp_start;
	int			tmp_end;
	int			color;

	i = -1;
	tmp_start = drawStart;
	tmp_end = drawEnd;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	cub->tex_pos_x *= cub->texture[cub->tex_id].tex_png->width;
	color = create_rgb(cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue);
	while (++i < drawStart)
		ft_put_pixel(cub->s_map.img_s_map, cub->x, i, color);
	while (drawEnd > ++drawStart)
		tex_to_wall(cub, drawStart, tmp_start, tmp_end);
	color = create_rgb(cub->floor.red, cub->floor.green, cub->floor.blue);
	while (++drawEnd < HEIGHT)
		ft_put_pixel(cub->s_map.img_s_map, cub->x, drawEnd, color);
}
