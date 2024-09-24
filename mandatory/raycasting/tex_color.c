/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:21:26 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/24 10:27:23 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	textures(t_cub *cub)
{
	cub->texture_id = 0;
	if (cub->side == 0 && cub->ray.x > 0)
	{
		while (cub->texture[cub->texture_id].identifier != E_EA)
			cub->texture_id++;
	}
	else if (cub->side == 0)
	{
		while (cub->texture[cub->texture_id].identifier != E_WE)
			cub->texture_id++;
	}
	else if (cub->ray.y > 0)
	{
		while (cub->texture[cub->texture_id].identifier != E_SO)
			cub->texture_id++;
	}
	else
	{
		while (cub->texture[cub->texture_id].identifier != E_NO)
			cub->texture_id++;
	}
}
