/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ptr_0_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:19:02 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/18 16:29:49 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		len1;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	s2 = (char *)malloc(len1 + 1);
	if (!s2)
		return (NULL);
	i = -1;
	while (++i < len1)
		s2[i] = s1[i];
	s2[i] = 0;
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	j;
	size_t	lens;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (len > lens - start)
		len = lens - start;
	if (start > lens)
		len = 0;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (0);
	j = 0;
	while (j < len)
	{
		s1[j] = s[start];
		j++;
		start++;
	}
	s1[j] = 0;
	return (s1);
}
