/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:11 by ealshari          #+#    #+#             */
/*   Updated: 2024/11/23 15:15:07 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_pointer(unsigned long ptr, int *len)
{
	if (!ptr)
	{
		ft_print_string("(nil)", len);
		return ;
	}
	write(1, "0x", 2);
	(*len) += 2;
	ft_print_hex(ptr, len, 'x');
}

void	ft_print_unsigned(unsigned int num, int *len)
{
	if (num > 9)
		ft_print_unsigned(num / 10, len);
	ft_putchar(num % 10 + '0', len);
}

void	ft_print_string(char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], len);
		i++;
	}
}

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}
