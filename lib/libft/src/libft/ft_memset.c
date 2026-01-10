/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:45:21 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/06 23:17:31 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*temp_c;

	temp_c = (unsigned char *)b;
	while (n-- > 0)
		temp_c[n] = (unsigned char)c;
	return (b);
}
