/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:12:38 by sdoidi            #+#    #+#             */
/*   Updated: 2023/12/01 19:43:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			str_len;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		len = 0;
	if (len > (str_len + 1))
		len = str_len + 1;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_bzero(ret, len + 1);
	while (s[start + i] && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	while (i < len)
		ret[++i] = '\0';
	return (ret);
}

char	*ft_strcat(char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	y;

	i = ft_strlen(s1);
	y = 0;
	while (s2[y])
	{
		s1[i + y] = s2[y];
		y++;
	}
	s1[i + y] = '\0';
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ret = (char *)malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	ft_bzero(ret, len);
	ft_strcat(ret, s1);
	ft_strcat(ret, s2);
	return (ret);
}
