/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:30 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:13:31 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_is_valid_key(const char *key)
{
	size_t	index;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	index = 1;
	while (key[index])
	{
		if (!(ft_isalnum(key[index]) || key[index] == '_'))
			return (0);
		index++;
	}
	return (1);
}

static int	export_print_all(t_ms *ms)
{
	size_t	env_index;
	char	*equals_pos;

	env_index = 0;
	while (ms->envp && ms->envp[env_index])
	{
		ft_putstr_fd("declare -x ", 1);
		equals_pos = ft_strchr(ms->envp[env_index], '=');
		if (equals_pos)
		{
			*equals_pos = '\0';
			ft_putstr_fd(ms->envp[env_index], 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equals_pos + 1, 1);
			ft_putstr_fd("\"", 1);
			*equals_pos = '=';
		}
		else
			ft_putstr_fd(ms->envp[env_index], 1);
		ft_putstr_fd("\n", 1);
		env_index++;
	}
	return (0);
}

static int	export_parse_arg(const char *arg, char **key, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	if (!equals_pos)
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(arg, 0, equals_pos - arg);
		*value = ft_strdup(equals_pos + 1);
		if (!*value)
		{
			free(*key);
			return (-1);
		}
	}
	return (0);
}

static int	export_process_arg(const char *arg, t_ms *ms)
{
	char	*key;
	char	*value;

	if (export_parse_arg(arg, &key, &value) == -1)
		return (-1);
	if (!key || !export_is_valid_key(key))
	{
		builtin_puterr3("export: `", arg, "': not a valid identifier\n");
		free(key);
		free(value);
		return (1);
	}
	if (value && env_variable_set(ms, key, value) == -1)
	{
		free(key);
		free(value);
		return (-1);
	}
	free(key);
	free(value);
	return (0);
}

int	builtin_export(int argc, char **argv, t_ms *ms)
{
	int	arg_index;
	int	exit_status;
	int	current_status;

	if (argc == 1)
		return (export_print_all(ms));
	exit_status = 0;
	arg_index = 1;
	while (arg_index < argc)
	{
		current_status = export_process_arg(argv[arg_index], ms);
		if (current_status == -1)
			return (-1);
		if (current_status == 1)
			exit_status = 1;
		arg_index++;
	}
	return (exit_status);
}
