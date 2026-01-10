/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:07:09 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/22 02:06:22 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_strchr_gnl(char *str, char ch)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup_gnl(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dup = (char *)malloc(ft_strlen_gnl(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_substr_gnl(char *str, int start, int length)
{
	char	*sub;
	int		i;

	i = 0;
	if (!str || start < 0 || length < 0)
		return (NULL);
	sub = (char *)malloc(length + 1);
	if (!sub)
		return (NULL);
	while (i < length && str[start + i])
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
