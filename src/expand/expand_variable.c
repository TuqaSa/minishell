/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:54 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:15:55 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*positional_param_get(t_ms *ms, const char *var_name)
{
	int	param_num;

	if (var_name[0] >= '0' && var_name[0] <= '9' && var_name[1] == '\0')
	{
		param_num = var_name[0] - '0';
		if (param_num == 0)
			return (ms->argv[0]);
		if (param_num < ms->argc)
			return (ms->argv[param_num]);
		return ("");
	}
	return (NULL);
}

static size_t	variable_name_length_get(const char *raw_input,
	size_t start_pos)
{
	size_t	current_pos;

	current_pos = start_pos;
	if (raw_input[current_pos] >= '0' && raw_input[current_pos] <= '9')
	{
		current_pos++;
		return (current_pos - start_pos);
	}
	while (ft_isalnum(raw_input[current_pos]) || raw_input[current_pos] == '_')
		current_pos++;
	return (current_pos - start_pos);
}

static void	variable_name_extract(char *dest_name, const char *raw_input,
							size_t start_pos, size_t name_length)
{
	size_t	copy_index;

	copy_index = 0;
	while (copy_index < name_length)
	{
		dest_name[copy_index] = raw_input[start_pos + copy_index];
		copy_index++;
	}
	dest_name[name_length] = '\0';
}

static int	variable_value_append(char **output, const char *var_value)
{
	char	*new_output;

	if (!var_value)
		return (0);
	if (*output)
		new_output = ft_strjoin(*output, var_value);
	else
		new_output = ft_strdup(var_value);
	if (!new_output)
	{
		free(*output);
		*output = NULL;
		return (-1);
	}
	free(*output);
	*output = new_output;
	return (0);
}

int	expand_variable_substitute(t_ms *ms, const char *raw_input,
	size_t *current_pos, char **output)
{
	size_t		start_pos;
	size_t		name_length;
	char		var_name[256];
	const char	*var_value;

	start_pos = *current_pos;
	name_length = variable_name_length_get(raw_input, start_pos);
	if (name_length == 0)
		return (0);
	variable_name_extract(var_name, raw_input, start_pos, name_length);
	var_value = positional_param_get(ms, var_name);
	if (!var_value)
		var_value = env_value_get(ms, var_name);
	if (variable_value_append(output, var_value) < 0)
		return (-1);
	*current_pos += name_length;
	return (0);
}
