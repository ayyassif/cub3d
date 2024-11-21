/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:09:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/20 12:52:05 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	hooking(t_cub *cub)
{
	mlx_key_hook(cub->mlx.mlx_handle, key_func, cub);
	if (mlx_loop_hook(cub->mlx.mlx_handle, loop_hook, cub) == false)
	{
		ft_putendl_fd("Error:\nthe hook was not added successfully", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	execution(t_cub *cub)
{
	cub->mlx.img = NULL;
	cub->mlx.mlx_handle = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!cub->mlx.mlx_handle)
		return (-1);
	cub->mlx.img = mlx_new_image(cub->mlx.mlx_handle, WIDTH, HEIGHT);
	if (!cub->mlx.img)
		return (-1);
	hooking(cub);
	mlx_loop(cub->mlx.mlx_handle);
	return (0);
}
