#include "get_next_line.h"

void	ft_freestr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_return(char **line, int b_read, char **str, int len, char *temp)
{
	len = 0;
	if (b_read == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	while ((*str)[len] != '\0' && (*str)[len] != '\n')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_substr(*str, 0, len);
		temp = ft_strdup(&(*str)[len + 1]);
		free(*str);
		*str = temp;
		if (*(str)[0] == '\0')
			ft_freestr(&(*str));
	}
	else
	{
		*line = ft_strdup(*str);
		ft_freestr(&(*str));
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		buff[BUFFER_SIZE + 1];
	int			b_read;
	char		*temp;
	int			len;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	b_read = read(fd, buff, BUFFER_SIZE);
	while (b_read > 0)
	{
		buff[b_read] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup("");
		temp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break ;
		b_read = read(fd, buff, BUFFER_SIZE);
	}
	if (b_read < 0)
		return (-1);
	else
		return (ft_return(line, b_read, &str[fd], len, temp));
}
