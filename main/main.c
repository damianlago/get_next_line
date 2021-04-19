/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlago-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:40:35 by dlago-mo          #+#    #+#             */
/*   Updated: 2021/04/19 14:40:42 by dlago-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char *line;
	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s", line);
		free(line);
		line = NULL;
	}
	
	system("leaks a.out");
	return (0);
}
