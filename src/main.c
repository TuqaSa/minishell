/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:07 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:18:08 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_only_space(const char *s)
{
	if (!s)
		return (1);
	while (*s == ' ' || *s == '\t')
		s++;
	return (*s == '\0');
}

static void	main_init_shell(t_ms *ms, int argc, char **argv, char **envp)
{
	char	*shlvl_str;
	int		shlvl;

	ms->last_status = 0;
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = env_context_init(envp);
	ms->pipe_fds = NULL;
	ms->child_pids = NULL;
	shlvl_str = (char *)env_value_get(ms, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		env_variable_set(ms, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	ms_set_echoctl(0);
	ms_signals_interactive();
}

static int	main_process_line(t_ms *ms, char *line)
{
	int	rc;

	if (!main_only_space(line))
		add_history(line);
	rc = ms_run_line_simple(ms, line);
	free(line);
	return (rc);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	char	*line;
	int		rc;

	main_init_shell(&ms, argc, argv, envp);
	while (1)
	{
		ms_signals_interactive();
		line = readline("minishell$ ");
		if (g_sig == SIGINT)
		{
			ms.last_status = 130;
			g_sig = 0;
		}
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		rc = main_process_line(&ms, line);
		if (rc == 1)
			break ;
	}
	env_context_free(ms.envp);
	return (ms.last_status);
}
