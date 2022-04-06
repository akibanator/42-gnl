/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:12:18 by akenji-a          #+#    #+#             */
/*   Updated: 2022/04/01 22:28:06 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(len + 1);
	if (res == 0)
		return (0);
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;
	size_t	str_len;

	str_len = ft_strlen(s);
	i = 0;
	str = malloc(str_len + 1);
	if (str == 0)
		return (0);
	while (i < str_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	*s;
	unsigned char	chr;

	s = (unsigned char *)str;
	chr = (unsigned char)c;
	if (*s == chr)
		return ((char *)s);
	while (*s++)
	{
		if (*s == chr)
			return ((char *)s);
	}
	return (0);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	cont;

	cont = 0;
	while (cont < len)
	{
		((unsigned char *)str)[cont] = c;
		cont++;
	}
	return (str);
}
