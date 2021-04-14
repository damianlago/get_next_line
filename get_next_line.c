#include "get_next_line.h"

void	ft_freestr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_return(int fd, char **line, int b_read, char **str)
{
	int	len;

	len = 0;
	if (b_read == 0 && str[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	while (str[fd][len] != '\0' && str[fd][len] != '\n')
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_substr(str[fd], 0, len);
		str[fd] = ft_strdup(&str[fd][len + 1]);
		if (str[fd][0] == '\0')
			ft_freestr(&str[fd]);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_freestr(&str[fd]);
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		*buff;
	char		*temp;
	int			b_read;
	
	buff = malloc((sizeof(char) * (BUFFER_SIZE)) + 1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buff)
		return (-1);
	while ((b_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[b_read] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_substr("", 0, 0);
		temp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	free(buff);
	if (b_read < 0)
		return (-1);
	else
		return (ft_return(fd, line, b_read, str));
}
