/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:48 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:15:49 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	string_reverse(char *buffer, int buffer_length)
{
	int		start_index;
	int		end_index;
	char	temp_char;

	start_index = 0;
	end_index = buffer_length - 1;
	while (start_index < end_index)
	{
		temp_char = buffer[start_index];
		buffer[start_index] = buffer[end_index];
		buffer[end_index] = temp_char;
		start_index++;
		end_index--;
	}
}

static int	digits_to_buffer(unsigned int abs_value,
	char *buffer, int start_pos)
{
	int	digit_index;

	digit_index = start_pos;
	while (abs_value > 0)
	{
		buffer[digit_index++] = (char)('0' + (abs_value % 10));
		abs_value /= 10;
	}
	buffer[digit_index] = '\0';
	return (digit_index);
}

void	expand_status_to_string(int status_value, char output_buffer[12])
{
	int				digit_index;
	unsigned int	abs_value;

	digit_index = 0;
	if (status_value == 0)
	{
		output_buffer[digit_index++] = '0';
		output_buffer[digit_index] = '\0';
		return ;
	}
	if (status_value < 0)
	{
		output_buffer[digit_index++] = '-';
		abs_value = (unsigned int)(-status_value);
	}
	else
		abs_value = (unsigned int)status_value;
	digit_index = digits_to_buffer(abs_value, output_buffer, digit_index);
	if (status_value < 0)
		string_reverse(output_buffer + 1, digit_index - 1);
	else
		string_reverse(output_buffer, digit_index);
}
