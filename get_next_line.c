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

char	*ft_split_nline(char *current_buffer, char **has_nline)
{
	char	*ret_str;
	int		i;

	i = 0;
	while (current_buffer++ != *has_nline)
		i++;
	ret_str = malloc(i + 2);
	ret_str[i + 1] = '\0';
	while (i >= 0)
	{
		current_buffer--;
		ret_str[i] = *current_buffer;
		i--;
	}
	return (ret_str);
}

char	*ft_current_line(char **buffer, char *current_buffer, char **remain)
{
	char	*buffer_temp;
	char	*has_nline;
	char	*split_nline_temp;

	buffer_temp = ft_strdup(*buffer);
	free(*buffer);
	has_nline = ft_strchr(current_buffer, '\n');
	if (!has_nline)
		*buffer = ft_strjoin(buffer_temp, current_buffer);
	else
	{
		*remain = ft_strdup(has_nline + 1);
		split_nline_temp = ft_split_nline(current_buffer, &has_nline);
		*buffer = ft_strjoin(buffer_temp, split_nline_temp);
		free(split_nline_temp);
	}
	free(buffer_temp);
	return (*remain);
}

size_t	ft_remain_join(char **remain, char **buffer)
{
	char	*temp_remain;
	char	*has_nline;

	if (*remain == NULL)
		*buffer = ft_strdup("");
	else
	{
		temp_remain = ft_strdup(*remain);
		free(*remain);
		*remain = NULL;
		has_nline = ft_strchr(temp_remain, '\n');
		if (!has_nline)
		{
			*buffer = ft_strdup(temp_remain);
			free(temp_remain);
		}
		else
		{
			*remain = ft_strdup(has_nline + 1);
			*buffer = ft_split_nline(temp_remain, &has_nline);
			free(temp_remain);
			return (0);
		}
	}
	return (1);
}

void	ft_gnl_aux(char **buffer, char **current_buffer)
{
	if (ft_strlen(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	free(*current_buffer);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*current_buffer;
	char		*buffer;
	size_t		len_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) != 0)
		return (NULL);
	current_buffer = ft_memset(malloc(BUFFER_SIZE + 1), 0, BUFFER_SIZE + 1);
	len_buffer = ft_remain_join(&remain, &buffer);
	if (current_buffer == NULL || buffer == NULL)
		return (NULL);
	while (len_buffer > 0 && remain == NULL)
	{
		len_buffer = read(fd, current_buffer, BUFFER_SIZE);
		if (len_buffer < BUFFER_SIZE)
			ft_memset(&current_buffer[len_buffer], 0, BUFFER_SIZE - len_buffer);
		if (len_buffer > 0)
			remain = ft_current_line(&buffer, current_buffer, &remain);
	}
	ft_gnl_aux(&buffer, &current_buffer);
	return (buffer);
}
