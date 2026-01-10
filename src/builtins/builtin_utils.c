/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:55 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:13:56 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_putstr(const char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
}

void	builtin_puterr3(const char *a, const char *b, const char *c)
{
	write(STDERR_FILENO, a, ft_strlen(a));
	write(STDERR_FILENO, b, ft_strlen(b));
	write(STDERR_FILENO, c, ft_strlen(c));
}

int	builtin_count_args(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}
