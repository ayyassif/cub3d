/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:42:24 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/17 11:26:28 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < (count * size))
		str[i++] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin1(char *s1, char *s2, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
	}
	if (s2)
	{
		j = 0;
		while (s2[j])
			res[i++] = s2[j++];
	}
	return (res[i] = '\0', res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		l1 = ft_strlen(s1);
	if (s2)
		l2 = ft_strlen(s2);
	res = malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (ft_strjoin1(s1, s2, res));
}
