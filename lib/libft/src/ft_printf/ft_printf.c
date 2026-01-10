/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari < ealshari@student.42amman.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:23 by ealshari          #+#    #+#             */
/*   Updated: 2024/11/23 15:36:36 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_check(char fmt, va_list *args, int *len)
{
	if (fmt == 's')
		ft_print_string(va_arg(*args, char *), len);
	else if (fmt == 'd' || fmt == 'i')
		ft_print_number(va_arg(*args, int), len);
	else if (fmt == 'p')
		ft_print_pointer(va_arg(*args, unsigned long), len);
	else if (fmt == 'x')
		ft_print_hex(va_arg(*args, unsigned int), len, 'x');
	else if (fmt == 'X')
		ft_print_hex(va_arg(*args, unsigned int), len, 'X');
	else if (fmt == '%')
		ft_print_string("%", len);
	else if (fmt == 'u')
		ft_print_unsigned(va_arg(*args, unsigned int), len);
	else if (fmt == 'c')
		ft_putchar(va_arg(*args, int), len);
	else
		(*len) = -1;
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			return (-1);
		if (str[i] == '%')
		{
			i++;
			printf_check(str[i], &args, &len);
			i++;
		}
		else
		{
			ft_putchar(str[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
