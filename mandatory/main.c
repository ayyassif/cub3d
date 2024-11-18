/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/18 16:29:43 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2 || check_file_name(av[1]))
		return (ft_putendl_fd("ERROR:\n\tinvalid parametre", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (close(cub.fd), -1);
	if (execution(&cub) == -1)
		return (free_cub(&cub), -1);
	free_cub(&cub);
	mlx_delete_image(cub.mlx.mlx_handle, cub.mlx.img);
	return (0);
}
