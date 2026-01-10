/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:09:36 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/06 23:32:46 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (src == NULL && dst == NULL)
		return (NULL);
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		while (len-- > 0)
			temp_dst[len] = temp_src[len];
	return (dst);
}
