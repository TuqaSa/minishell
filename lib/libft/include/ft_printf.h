/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:37 by ealshari          #+#    #+#             */
/*   Updated: 2024/12/30 12:49:08 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_print_string(char *str, int *len);
void	ft_putchar(char c, int *len);
void	ft_print_number(int num, int *len);
void	ft_print_pointer(size_t ptr, int *len);
void	ft_print_hex(size_t num, int *len, char x);
void	ft_print_unsigned(unsigned int num, int *len);

#endif
