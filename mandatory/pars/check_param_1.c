/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:30:58 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/21 19:18:15 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_empty(t_cub *cub, size_t ln, size_t col)
{
	if (ln == 0 || ln == cub->height - 1 || col == 0 || col == cub->width - 1)
		return (-1);
	if (cub->map[ln - 1][col] == M_VOID)
		return (-1);
	if (cub->map[ln + 1][col] == M_VOID)
		return (-1);
	if (cub->map[ln][col - 1] == M_VOID)
		return (-1);
	if (cub->map[ln][col + 1] == M_VOID)
		return (-1);
	return (0);
}

int	pars_map(t_cub *cub)
{
	size_t	ln;
	size_t	col;
	int		p;

	p = 0;
	ln = -1;
	while (++ln < cub->height)
	{
		col = -1;
		while (++col < cub->width)
		{
			if (is_non_empty(cub->map[ln][col])
				&& check_empty(cub, ln, col) == -1)
				return (ft_putendl_fd("Error:\ninvalid wall", 2), -1);
			if (cub->map[ln][col] == M_PLAYER)
			{
				p++;
				cub->map[ln][col] = M_FLOOR;
			}
		}
	}
	if (p != 1)
		return (ft_putendl_fd("Error:\nnumber of player", 2), -1);
	return (0);
}
