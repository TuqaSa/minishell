/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:12:44 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:12:46 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_is_all_ns(const char *s)
{
	size_t	index;

	if (!s || s[0] != '-')
		return (0);
	index = 1;
	while (s[index])
	{
		if (s[index] != 'n')
			return (0);
		index++;
	}
	return (ft_strlen(s) > 1);
}

static int	echo_parse_flags(char **argv, int *no_newline)
{
	int	arg_index;

	arg_index = 1;
	*no_newline = 0;
	while (argv[arg_index] && echo_is_all_ns(argv[arg_index]))
	{
		*no_newline = 1;
		arg_index++;
	}
	return (arg_index);
}

static void	echo_print_args(char **argv, int start_index, const char *home)
{
	int	arg_index;
	int	first_arg;

	first_arg = start_index;
	arg_index = start_index;
	while (argv[arg_index])
	{
		if (arg_index > first_arg)
			ft_putchar_fd(' ', STDOUT_FILENO);
		if (argv[arg_index][0] == '~' && argv[arg_index][1] == '\0' && home)
			builtin_putstr(home);
		else
			builtin_putstr(argv[arg_index]);
		arg_index++;
	}
}

int	builtin_echo(char **argv, t_ms *ms)
{
	int			start_index;
	int			no_newline;
	const char	*home;

	home = env_value_get(ms, "HOME");
	start_index = echo_parse_flags(argv, &no_newline);
	echo_print_args(argv, start_index, home);
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ms->last_status = 0;
	return (0);
}
