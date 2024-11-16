/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/16 17:01:49 by ayyassif         ###   ########.fr       */
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
	mlx_delete_image(cub.s_map.mlx_s_map, cub.s_map.img_s_map);
	return (0);
}
