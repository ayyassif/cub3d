/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:29:57 by ayyassif          #+#    #+#             */
/*   Updated: 2024/11/18 12:09:54 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	ft_put_pixel(cub->mlx.img, cub->x, drawStart, color);
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
		ft_put_pixel(cub->mlx.img, cub->x, i, color);
	while (drawEnd > drawStart++)
		tex_to_wall(cub, drawStart, tmp_start, tmp_end);
	color = create_rgb(cub->floor.red, cub->floor.green, cub->floor.blue);
	while (drawEnd++ < HEIGHT)
		ft_put_pixel(cub->mlx.img, cub->x, drawEnd, color);
}
