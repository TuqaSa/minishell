/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:48 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:13:49 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_is_valid_key(const char *key)
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

int	builtin_unset(int argc, char **argv, t_ms *ms)
{
	int	arg_index;
	int	exit_status;

	if (argc < 2)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		ms->last_status = 1;
		return (1);
	}
	exit_status = 0;
	arg_index = 1;
	while (arg_index < argc)
	{
		if (!unset_is_valid_key(argv[arg_index]))
		{
			builtin_puterr3("unset: `", argv[arg_index],
				"': not a valid identifier\n");
			exit_status = 1;
		}
		else
			env_variable_unset(ms, argv[arg_index]);
		arg_index++;
	}
	ms->last_status = exit_status;
	return (exit_status);
}
