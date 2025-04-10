/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:21:26 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/17 11:13:20 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	textures(t_cub *cub, int type_tex)
{
	cub->tex_id = 0;
	if (type_tex == 2)
		cub->tex_id = 4;
	if (cub->side == 0 && cub->ray.x > 0 && type_tex == 1)
	{
		while (cub->texture[cub->tex_id].identifier != E_EA)
			cub->tex_id++;
	}
	else if (cub->side == 0 && type_tex == 1)
	{
		while (cub->texture[cub->tex_id].identifier != E_WE)
			cub->tex_id++;
	}
	else if (cub->ray.y > 0 && type_tex == 1)
	{
		while (cub->texture[cub->tex_id].identifier != E_SO)
			cub->tex_id++;
	}
	else if (type_tex == 1)
	{
		while (cub->texture[cub->tex_id].identifier != E_NO)
			cub->tex_id++;
	}
}

int	color_from_pixel(mlx_texture_t *texture, int index)
{
	int	r;
	int	g;
	int	b;

	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	return (create_rgb(r, g, b));
}

void	ft_put_pixel(mlx_image_t *image, uint32_t x,
	uint32_t y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
