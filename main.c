/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:47:55 by akenji-a          #+#    #+#             */
/*   Updated: 2022/04/01 22:53:07 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"
#include	<fcntl.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	main(void)
{
	char	*str;
	int		fd;
	char	*res_expected1 = "10987654\n";
	char	*res_expected2 = "98765432\n";
	size_t	i;

	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	if (!(ft_strcmp(str, res_expected1)))
	{
		printf("Retorno esperando: '%s' == '%s'\n", str, res_expected1);
	}
	else
	{
		printf("Retorno NÃO esperado: '%s' != '%s'\n", str, res_expected1);
	}
	free(str);
/*	str = get_next_line(fd);
	if (!(ft_strcmp(str, res_expected2)))
	{
		printf("Retorno esperando: '%s' == '%s'\n", str, res_expected2);
	}
	else
	{
		printf("Retorno NÃO esperado: '%s' != '%s'\n", str, res_expected2);
	}*/
	str = get_next_line(fd);
	if (!str)
		printf("TERMINOU\n");
	close(fd);
	return (0);
}
