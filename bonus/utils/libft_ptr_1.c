/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ptr_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:37:56 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/16 18:31:51 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static char	*ft_m1(char *s)
{
	s = malloc(1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

static size_t	ft_front(char const *s1)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_white_space(s1[i]))
		i++;
	return (i);
}

static size_t	ft_back(char const *s1)
{
	size_t	j;

	j = ft_strlen(s1) - 1;
	while (j != 0 && is_white_space(s1[j]))
		j--;
	return (j);
}

char	*ft_strtrim(char *s1)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	a;

	if (!s1)
		return (0);
	i = 0;
	if (s1[i] == '\0')
		return (ft_m1((char *)s1));
	i = ft_front(s1);
	j = ft_back(s1);
	str = malloc(((i <= j) * (j - i + 2)) + ((i > j) * (i - j + 2)));
	if (!str)
		return (free(s1), NULL);
	a = 0;
	while (i <= j)
		str[a++] = s1[i++];
	str[a] = 0;
	free(s1);
	return (str);
}

char	*ft_back_strtrim(char *s1)
{
	size_t	j;
	char	*str;
	size_t	a;
	size_t	i;

	i = 0;
	if (!s1)
		return (0);
	if (s1[0] == '\0')
		return (ft_m1((char *)s1));
	j = ft_back(s1);
	str = malloc(j + 2);
	if (!str)
		return (free(s1), NULL);
	a = 0;
	while (i <= j)
		str[a++] = s1[i++];
	str[a] = 0;
	free(s1);
	return (str);
}
