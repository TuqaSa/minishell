/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:27:00 by ealshari          #+#    #+#             */
/*   Updated: 2024/09/07 08:58:36 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len += 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	ln;
	int		len;
	char	*result;

	ln = n;
	len = int_len(ln);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (ln < 0)
	{
		result[0] = '-';
		ln *= -1;
	}
	if (ln == 0)
		result[0] = '0';
	result[len] = '\0';
	while (ln != 0)
	{
		result[len - 1] = (ln % 10) + '0';
		ln = ln / 10;
		len--;
	}
	return (result);
}
