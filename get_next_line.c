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

// we extract line from page
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

// everything is in the name xd
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

// same as above
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
	char*   filename = "get_next_line.h";
    int fd = open(filename, O_RDWR);
	char *line = get_next_line(fd);
	int i = 3;

    if (fd == -1)
    {
        printf("Error Opening File");
        exit(1);
    }
    else
    {
        printf("File opened successfully\n");
    }

	printf("1 : %s\n", line);
	free(line);

	line = get_next_line(fd);
	printf("2 : %s\n", line);
	free(line);

	printf("           ------------ BOUCLE -----------\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%d ", i);
		printf(": %s\n", line);
		free(line);
		i++;
	}
	close(fd);
}*/
