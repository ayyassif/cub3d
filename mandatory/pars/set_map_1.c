/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:01:01 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/28 16:21:19 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_map(t_cub *cub)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_line_map	*tmp;

	tmp = cub->line_map;
	j = 0;
	while (tmp)
	{
		i = cub->ofset_front;
		k = 0;
		while (tmp->line_map[i] && k < cub->width)
		{
			if (tmp->line_map[i] != '\n')
				cub->map[j][k].value = tmp->line_map[i];
			else
				cub->map[j][k].value = ' ';
			k++;
			i++;
		}
		while (k < cub->width)
		{
			cub->map[j][k].value = ' ';
			k++;
		}
		j++;
		tmp = tmp->next;
	}
}

int	creat_map(t_cub *cub)
{
	size_t	i;

	i = 0;

	cub->map = malloc(sizeof(t_map *) * cub->height);
	if (!cub->map)
		return (ft_putendl_fd("error: malloc", 2), -1);
	while (i < cub->height && cub->map[i])
	{
		cub->map[i] = malloc(sizeof(t_map) * cub->width);
		if (!cub->map[i])
			return (ft_putendl_fd("error: malloc", 2), -1);
		i++;
	}
	put_map(cub);
	return (0);
}
