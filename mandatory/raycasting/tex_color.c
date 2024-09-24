/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:21:26 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/24 19:29:35 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	textures(t_cub *cub)
{
	cub->tex_id = 0;
	if (cub->side == 0 && cub->ray.x > 0)
	{
		while (cub->texture[cub->tex_id].identifier != E_EA)
			cub->tex_id++;
	}
	else if (cub->side == 0)
	{
		while (cub->texture[cub->tex_id].identifier != E_WE)
			cub->tex_id++;
	}
	else if (cub->ray.y > 0)
	{
		while (cub->texture[cub->tex_id].identifier != E_SO)
			cub->tex_id++;
	}
	else
	{
		while (cub->texture[cub->tex_id].identifier != E_NO)
			cub->tex_id++;
	}
}

int	color_from_pixel(t_cub *cub, int index)
{
	int	r;
	int	g;
	int	b;

	r = cub->texture[cub->tex_id].tex_png->pixels[index];
	g = cub->texture[cub->tex_id].tex_png->pixels[index + 1];
	b = cub->texture[cub->tex_id].tex_png->pixels[index + 2];
	return (create_rgb(r, g, b));
}

void	ft_put_pixel(mlx_image_t *image, uint32_t x,
	uint32_t y, uint32_t color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_put_pixel(image, x, y, color);
}
