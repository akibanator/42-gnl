/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:17:34 by akenji-a          #+#    #+#             */
/*   Updated: 2022/04/01 23:01:43 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

char	*ft_mini_split(char *buffer)
{
	char	*split_buffer;
	char	*pos_nline;
	char	*pos_start_buffer;
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	pos_start_buffer = buffer;
	pos_nline = ft_strchr(buffer, '\n');
	while (buffer++ != pos_nline)
		i++;
	split_buffer = malloc(++i);
	split_buffer[i--] = '\0';
	while (j < i)
	{
		split_buffer[j] = *pos_start_buffer++;
		j++;
	}
	return (split_buffer);
}

int	ft_current_line(char *buffer, char **buffered)
{
	char	*buffered_temp;
	char	*split_temp;
	int		bool;

	bool = 0;
	buffered_temp = ft_strdup(*buffered);
	free(*buffered);
	if (ft_strchr(buffer, '\n') == NULL)
		*buffered = ft_strjoin(buffered_temp, buffer);
	else
	{
		split_temp = ft_mini_split(buffer);
		*buffered = ft_strjoin(buffered_temp, split_temp);
		bool = 1;
	}
	free(buffered_temp);
	return (bool);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*buffered;

	buffered = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE) != 0)
		if (ft_current_line(buffer, &buffered))
			break ;
	free(buffer);
	return (buffered);
}
