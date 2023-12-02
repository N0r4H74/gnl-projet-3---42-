/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:51:34 by root              #+#    #+#             */
/*   Updated: 2023/12/02 16:53:23 by root             ###   ########.fr       */
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

static char	*ft_get_line(int fd, char **stock_str, char *line)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (!stock_str[fd])
		return (NULL);
	while (stock_str[fd][i] && stock_str[fd][i] != '\n')
		i++;
	if (stock_str[fd][i] == '\n')
		i++;
	line = ft_substr(stock_str[fd], 0, i);
	temp = ft_substr(stock_str[fd], i, ft_strlen(&stock_str[fd][i]));
	free(stock_str[fd]);
	stock_str[fd] = temp;
	if (!line || !temp || ft_strlen(line) == 0)
	{
		free(stock_str[fd]);
		free(line);
		stock_str[fd] = NULL;
		return (NULL);
	}
	return (line);
}

static char	*ft_read_file(int fd, char **stock_str, char *line)
{
	int		nb_read;
	char	*temp;

	nb_read = BUFFER_SIZE;
	while (nb_read >= 0)
	{
		ft_bzero(line, BUFFER_SIZE + 1);
		nb_read = read(fd, line, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(stock_str[fd]);
			return (NULL);
		}
		if (!stock_str[fd])
			stock_str[fd] = ft_strdup(line);
		else
		{
			temp = ft_strjoin(stock_str[fd], line);
			free(stock_str[fd]);
			stock_str[fd] = temp;
		}
		if (stock_str[fd] && (ft_strchr(stock_str[fd], '\n') || nb_read == 0))
			return (stock_str[fd]);
	}
	return (stock_str[fd]);
}

char	*get_next_line(int fd)
{
	static char	*stock_str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	stock_str[fd] = ft_read_file(fd, stock_str, line);
	free(line);
	if (!stock_str[fd])
		return (NULL);
	line = ft_get_line(fd, stock_str, line);
	return (line);
}
