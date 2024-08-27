/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/27 14:06:56 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	main(int ac, char **av)
{
	t_cub	cub;
	if (ac != 2)
		return (ft_putendl_fd("ERROR", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (-1);
	ft_write_cub(&cub);
	return (0);
}
