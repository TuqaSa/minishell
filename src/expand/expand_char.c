/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:37 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:15:39 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_append_to_output(const char *raw_input, size_t *pos, char **output)
{
	char	char_buffer[2];
	char	*new_output;

	char_buffer[0] = raw_input[*pos];
	char_buffer[1] = '\0';
	if (*output)
		new_output = ft_strjoin(*output, char_buffer);
	else
		new_output = ft_strdup(char_buffer);
	if (!new_output)
		return (-1);
	if (*output)
		free(*output);
	*output = new_output;
	(*pos)++;
	return (0);
}

int	quote_toggle_check(const char *raw_input, size_t *pos,
							int *in_single, int *in_double)
{
	if (raw_input[*pos] == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		(*pos)++;
		return (1);
	}
	if (raw_input[*pos] == '"' && !*in_single)
	{
		*in_double = !*in_double;
		(*pos)++;
		return (1);
	}
	return (0);
}

int	literal_dollar_append(char **output)
{
	char	dollar_char[2];
	char	*temp_result;

	dollar_char[0] = '$';
	dollar_char[1] = '\0';
	if (*output)
		temp_result = ft_strjoin(*output, dollar_char);
	else
		temp_result = ft_strdup(dollar_char);
	if (!temp_result)
		return (-1);
	if (*output)
		free(*output);
	*output = temp_result;
	return (0);
}

int	status_expansion_handle(t_ms *ms, size_t *pos, char **output)
{
	char	status_buffer[12];
	char	*temp_result;

	expand_status_to_string(ms->last_status, status_buffer);
	if (*output)
		temp_result = ft_strjoin(*output, status_buffer);
	else
		temp_result = ft_strdup(status_buffer);
	if (!temp_result)
		return (-1);
	if (*output)
		free(*output);
	*output = temp_result;
	(*pos)++;
	return (0);
}
