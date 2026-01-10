/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:15 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:21 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	exit_skip_spaces(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

static int	exit_parse_digits(const char *s, size_t *i, unsigned long long *v)
{
	if (!ft_isdigit(s[*i]))
		return (-1);
	*v = 0;
	while (ft_isdigit(s[*i]))
	{
		*v = *v * 10 + (s[*i] - '0');
		if (*v > (unsigned long long)LLONG_MAX)
			return (-1);
		(*i)++;
	}
	return (0);
}

static int	exit_parse_number(const char *s, unsigned char *out)
{
	size_t				i;
	int					sign;
	unsigned long long	v;
	long long			result;

	i = exit_skip_spaces(s);
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (exit_parse_digits(s, &i, &v) == -1)
		return (-1);
	i += exit_skip_spaces(s + i);
	if (s[i])
		return (-1);
	result = (long long)v * sign;
	*out = (unsigned char)(result & 0xFF);
	return (0);
}

int	builtin_exit(int argc, char **argv, t_ms *ms)
{
	unsigned char	status;

	ft_putstr_fd("exit\n", 2);
	if (argc == 1)
	{
		ms->last_status = 0;
		return (2);
	}
	if (exit_parse_number(argv[1], &status) == -1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms->last_status = 2;
		return (2);
	}
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	ms->last_status = status;
	return (2);
}
