/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:47:59 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/04 18:06:00 by ayyassif         ###   ########.fr       */
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

int	is_player(t_type value)
{
	if (value == M_PLAYER_E || value == M_PLAYER_W || value == M_PLAYER_S
		|| value == M_PLAYER_N)
		return (1);
	return (0);
}
