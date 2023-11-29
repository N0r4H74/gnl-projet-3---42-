/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoidi <sdoidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:12:38 by sdoidi            #+#    #+#             */
/*   Updated: 2023/11/29 12:17:20 by sdoidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		slength;
	char	*s2;

	i = 0;
	slength = ft_strlen (s);
	s2 = malloc(slength + 1);
	if (s2 != NULL)
	{
		while (s[i] && i < slength)
		{
			s2[i] = s[i];
			i++;
		}
		s2[i] = '\0';
		return (s2);
	}
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_length;

	i = 0;
	if ((!dst || !src) && size == 0)
		return (0);
	dst_length = ft_strlen(dst);
	if (size <= dst_length)
		return (size + ft_strlen(src));
	while (dst_length + i < size - 1 && src[i])
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*newstr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(len + 1);
	if (newstr == NULL)
		return (NULL);

	ft_strlcat(newstr, s1, ft_strlen(s1) +1);
	ft_strlcat(newstr, s2, (ft_strlen(s2) + ft_strlen(s1) + 1));
	return (newstr);
}

void	*ft_memmove(void *dest, const void *src, size_t n) 
{
	size_t	i;

	if (src < dest) 
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
	{
		i = 0;
		if (!dest && !src)
			return (NULL);
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
		return (dest);
	}
	return (dest);
}
