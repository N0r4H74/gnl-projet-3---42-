/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoidi <sdoidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:50:35 by sdoidi            #+#    #+#             */
/*   Updated: 2023/11/29 15:41:43 by sdoidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static char	*ft_get_line(char *line)
{
	char	*new_line;
	int		i;

	new_line = NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	new_line = malloc((i + 2) * sizeof(char));
	if (new_line == NULL)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	free(line);
	line = NULL;
	return (new_line);
}

static void	ft_get_stock(char *stock_str)
{
	int		i;

	i = 0;
	while (stock_str[i] && stock_str[i] != '\n')
		i++;
	if (stock_str[i] == '\n')
		i++;
	ft_memmove(stock_str, stock_str + i, (BUFFER_SIZE - i));
	ft_bzero(&stock_str[BUFFER_SIZE - i], i);
}

static char	*ft_read_file(int fd, char *line, char *stock_str)
{
	int		nb_read;

	nb_read = BUFFER_SIZE;
	stock_str[ft_strlen(stock_str) + nb_read] = '\0';
	while (!ft_strchr(stock_str, '\n'))
	{
		nb_read = read(fd, stock_str, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(stock_str);
			stock_str = NULL;
			return (NULL);
		}
		if (nb_read == 0)
			break;
	}
	line = ft_strjoin(line, stock_str);
	return (line);
}

char *get_next_line(int fd)
{
	static char stock_str[BUFFER_SIZE +1];
	char 		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read_file(fd, line, stock_str);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	line = ft_get_line(line);//retourner la ligne jusqu'au premier \n
	ft_get_stock(stock_str);
	return (line);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *line;
	int fd = open("to_read.txt", O_RDONLY);
	int	i;

	i = 1;

	if (fd < 0)
	{
		printf("%s\n", "Erreur lors de l'ouverture du fichier");
		return 1;
	}
	 while (i <= 4) 
	{
		line = get_next_line(fd);
		printf("%s", line);
		//free(line);
		i++;
	}
	close(fd);
	return 0;
}

// int main()
// {
// 	static char buffer[BUFFER_SIZE + 1];

// 	buffer = "Dididou\ndessine moi une fleur pour ma maman";

// 	printf("%s\n", ft_get_next_line(buffer));
// 	return (0);
// }