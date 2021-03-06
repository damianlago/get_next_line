/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlago-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:47:26 by dlago-mo          #+#    #+#             */
/*   Updated: 2021/04/21 11:47:40 by dlago-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_freestr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_get_line(char **line, char **str)
{
	int		len;
	char	*aux;

	len = 0;
	while ((*str)[len] != '\0' && (*str)[len] != '\n')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_substr((*str), 0, len);
		aux = ft_strdup(&(*str)[len + 1]);
		free(*str);
		*str = aux;
		if ((*str)[0] == '\0')
			ft_freestr(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_freestr(str);
		return (0);
	}
	return (1);
}

int	ft_return(char **line, char **str, int bytes_r)
{
	if (bytes_r < 0)
		return (-1);
	else if (bytes_r == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (ft_get_line(line, str));
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		buff[BUFFER_SIZE + 1];
	char		*aux;
	int			bytes_r;

	if (fd < 0 || line == NULL)
		return (-1);
	bytes_r = read(fd, buff, BUFFER_SIZE);
	while (bytes_r > 0)
	{
		buff[bytes_r] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup("");
		aux = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = aux;
		if (ft_strchr(buff, '\n'))
			break ;
		bytes_r = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_return(line, &str[fd], bytes_r));
}
