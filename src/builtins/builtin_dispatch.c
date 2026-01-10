/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:12:37 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:12:39 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0 && !cmd[4])
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0 && !cmd[2])
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0 && !cmd[3])
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0 && !cmd[6])
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0 && !cmd[5])
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0 && !cmd[3])
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0 && !cmd[4])
		return (1);
	return (0);
}

int	run_builtin(int argc, char **argv, t_ms *ms)
{
	if (!argv || !argv[0])
		return (-1);
	if (ft_strncmp(argv[0], "echo", 5) == 0 && !argv[0][4])
		return (builtin_echo(argv, ms));
	if (ft_strncmp(argv[0], "cd", 3) == 0 && !argv[0][2])
		return (builtin_cd(argc, argv, ms));
	if (ft_strncmp(argv[0], "pwd", 4) == 0 && !argv[0][3])
		return (builtin_pwd(ms));
	if (ft_strncmp(argv[0], "export", 7) == 0 && !argv[0][6])
		return (builtin_export(argc, argv, ms));
	if (ft_strncmp(argv[0], "unset", 6) == 0 && !argv[0][5])
		return (builtin_unset(argc, argv, ms));
	if (ft_strncmp(argv[0], "env", 4) == 0 && !argv[0][3])
		return (builtin_env(argc, argv, ms));
	if (ft_strncmp(argv[0], "exit", 5) == 0 && !argv[0][4])
		return (builtin_exit(argc, argv, ms));
	return (-1);
}
