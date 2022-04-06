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

	i = 0;
	j = 0;
	pos_start_buffer = buffer;
	pos_nline = ft_strchr(buffer, '\n');
	while (buffer++ != pos_nline)
		i++;
	split_buffer = malloc(i + 2);
	while (j <= i)
	{
		split_buffer[j] = *pos_start_buffer;
		pos_start_buffer++;
		j++;
	}
	split_buffer[j] = '\0';
	return (split_buffer);
}

int	ft_current_line(char *buffer, char **buffered, char **saved)
{
	char	*buffered_temp;
	char	*split_temp;
	int		boolcl;

	boolcl = 0;
	buffered_temp = ft_strdup(*buffered);
	free(*buffered);
	if (ft_strchr(buffer, '\n') == NULL)
		*buffered = ft_strjoin(buffered_temp, buffer);
	else
	{
		split_temp = ft_mini_split(buffer);
		*saved = ft_strdup(ft_strchr(buffer, '\n') + 1);
		*buffered = ft_strjoin(buffered_temp, split_temp);
		free(split_temp);
		boolcl = 1;
	}
	free(buffered_temp);
	return (boolcl);
}

void	ft_strjoin_saved(char **saved, char **buffer)
{
	char	*buffer_temp;

	buffer_temp = ft_strdup(*buffer);
	free(*buffer);
	*buffer = ft_strjoin(*saved, buffer_temp);
	free(*saved);
	free(buffer_temp);
	*saved = NULL;
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*buffered;

	buffered = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_memset(malloc(BUFFER_SIZE + 1), 0, BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE) != 0)
	{
		if (saved != NULL)
			ft_strjoin_saved(&saved, &buffer);
		if (ft_current_line(buffer, &buffered, &saved))
		{
			free(buffer);
			return (buffered);
		}
	}
	free(saved);
	saved = NULL;
	free(buffer);
	free(buffered);
	return (NULL);
}
