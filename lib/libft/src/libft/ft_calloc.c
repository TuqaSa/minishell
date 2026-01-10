/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 05:44:32 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/14 13:40:16 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;
	size_t	i;

	i = 0;
	buffer = malloc(count * size);
	if (!buffer)
		return (NULL);
	while (i < count * size)
		((unsigned char *)buffer)[i++] = 0;
	return (buffer);
}
