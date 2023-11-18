/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:04:25 by aquinter          #+#    #+#             */
/*   Updated: 2023/11/18 18:18:15 by aquinter         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;

	dstlen = ft_strlen(dst);
	if (dstsize > dstlen)
	{
		i = 0;
		while ((dstlen + i) < (dstsize - 1) && src[i] != '\0')
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		dst[i + dstlen] = '\0';
		return (dstlen + ft_strlen(src));
	}
	return (ft_strlen(src) + dstsize);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*s3;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(total_len * sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, total_len);
	ft_strlcat(s3, s2, total_len);
	free((void *)s1);
	return (s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		s2 = malloc(1 * sizeof(char));
		if (!s2)
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	s2 = malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, len + 1);
	free((void *)s);
	return (s2);
}
