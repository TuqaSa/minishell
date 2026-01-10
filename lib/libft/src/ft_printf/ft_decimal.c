/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:11 by ealshari          #+#    #+#             */
/*   Updated: 2024/11/23 14:15:38 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(size_t num, int *len, char x)
{
	char	*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num >= 16)
		ft_print_hex(num / 16, len, x);
	ft_putchar(base[num % 16], len);
}

void	ft_print_number(int num, int *len)
{
	if (num == -2147483648)
	{
		ft_print_string("-2147483648", len);
		return ;
	}
	if (num < 0)
	{
		ft_putchar('-', len);
		num = -num;
	}
	if (num >= 10)
		ft_print_number(num / 10, len);
	ft_putchar(num % 10 + '0', len);
}
