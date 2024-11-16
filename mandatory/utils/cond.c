/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:47:59 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/16 18:39:26 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_non_empty(t_type value)
{
	if (value == M_FLOOR || value == M_PLAYER)
		return (1);
	return (0);
}

int	is_collision(t_type value)
{
	if (value == M_WALL)
		return (1);
	return (0);
}
