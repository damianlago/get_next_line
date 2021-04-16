/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlago-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:26:25 by dlago-mo          #+#    #+#             */
/*   Updated: 2021/04/16 16:35:30 by dlago-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_freestr(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

static char	*ft_get_line(char **line, char *str, int *bytes_r)
{
	int		len;
	char	*aux;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (str[len] == '\n')
	{
		*line = ft_substr(str, 0, len);
		aux = ft_strdup(str + (len + 1));
		free(str);
		str = aux;
		if (str[0] == '\0')
			str = ft_freestr(str);
		*bytes_r = 1;
	}
	else
	{
		*line = ft_strdup(str);
		free(str);
		str = NULL;
		*bytes_r = 0;
	}
	return (str);
}

static int	ft_return(char **line, int bytes_r)
{
	if (bytes_r < 0)
		 return (-1);
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		*buff;
	int			bytes_r;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (-1);
	bytes_r = read(fd, buff, BUFFER_SIZE);
	while (bytes_r > 0)
	{
		buff[bytes_r] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
			str[fd] = ft_strjoin(str[fd], buff);
		if (ft_strchr(str[fd], '\n'))
			break ;
		bytes_r = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if ((bytes_r < 0) || (bytes_r == 0 && str[fd] == NULL))
		return (ft_return(line, bytes_r));
	str[fd] = ft_get_line(line, str[fd], &bytes_r);
	return (bytes_r);
}
