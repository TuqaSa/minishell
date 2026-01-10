/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:51:40 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/14 14:16:29 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			res = ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		res = ((char *)&s[i]);
	return (res);
}
