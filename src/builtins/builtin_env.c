/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:02 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:13:04 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(int argc, char **argv, t_ms *ms)
{
	size_t	env_index;

	if (argc > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->last_status = 127;
		return (127);
	}
	env_index = 0;
	while (ms->envp && ms->envp[env_index])
	{
		ft_putstr_fd(ms->envp[env_index], 1);
		ft_putstr_fd("\n", 1);
		env_index++;
	}
	ms->last_status = 0;
	return (0);
}
