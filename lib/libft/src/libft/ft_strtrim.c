/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:15:13 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/09 14:48:00 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j >= i && ft_strchr(set, s1[j]))
		j--;
	j = j - i + 1;
	str = (char *)ft_calloc(j + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, j + 1);
	return (str);
}
