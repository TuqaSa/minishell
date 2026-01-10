/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 04:37:15 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/07 04:42:35 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	unsigned char	temp_c;
	size_t			i;

	temp_s = (unsigned char *)s;
	temp_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (temp_s[i] == temp_c)
			return ((void *)&temp_s[i]);
		i++;
	}
	return (NULL);
}
