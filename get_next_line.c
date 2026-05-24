/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboubeke <nboubeke@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:50:59 by nboubeke          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:35 by nboubeke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readbyte(char **page, char *line)
{
	char	*temp;
	size_t	len;

	if (!ft_strchr(*page, '\n'))
	{
		line = ft_strdup(*page);
		free(*page);
		*page = NULL;
		return (line);
	}
	line = malloc(ft_strchr(*page, '\n') - *page + 2);
	len = ft_strchr(*page, '\n') - *page + 1;
	ft_strlcpy(line, *page, len + 1);
	temp = ft_strdup(ft_strchr(*page, '\n') + 1);
	free(*page);
	*page = temp;
	return (line);
}

char	*read_until_newline(int fd, char **page)
{
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];
	int		readbytes;

	while (!ft_strchr(*page, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes <= 0)
		{
			return (NULL);
		}
		buffer[readbytes] = '\0';
		temp = ft_strjoin(*page, buffer);
		free(*page);
		*page = temp;
	}
	return (*page);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*page;

	line = NULL;
	if (!page)
	{
		page = malloc(1);
		page[0] = '\0';
	}
	if (ft_strchr(page, '\n'))
		return (readbyte(&page, line));
	else
	{
		if (!read_until_newline(fd, &page))
		{
			if (page && page[0])
				return (readbyte(&page, line));
			return (NULL);
		}
		return (readbyte(&page, line));
	}
}
/*
int main()
{
    char*   filename;
    int fd;
    char    buffer[1024];
    int bytesread;

    filename = "read.txt";
    fd = open(filename, O_RDWR);

    if (fd == -1)
    {
        printf("Error Opening File");
        exit(1);
    }
    else
    {
        printf("File opened successfully\n");
    }

    bytesread = read(fd, buffer, sizeof(buffer));
    printf("%d bytes read\n", bytesread);
    printf("File content: %s\n", buffer);
}*/
