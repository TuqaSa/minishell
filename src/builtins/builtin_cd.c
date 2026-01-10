/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:12:29 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:12 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*cd_get_target(int argc, char **argv, t_ms *ms)
{
	if (argc > 2)
		return (NULL);
	if (argc == 1)
		return (env_value_get(ms, "HOME"));
	return (argv[1]);
}

static int	cd_handle_dash(t_ms *ms, char *oldpwd)
{
	const char	*target;

	target = env_value_get(ms, "OLDPWD");
	if (!target || !*target)
	{
		builtin_puterr3("minishell: cd: ", "OLDPWD not set", "\n");
		free(oldpwd);
		return (1);
	}
	printf("%s\n", target);
	return (0);
}

static int	cd_validate_args(int argc, char *oldpwd)
{
	if (argc > 2)
	{
		builtin_puterr3("minishell: cd: ", "too many arguments", "\n");
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(int argc, char **argv, t_ms *ms)
{
	const char	*target;
	char		*expanded;
	char		*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (cd_validate_args(argc, oldpwd))
		return (1);
	if (argc == 2 && ft_strncmp(argv[1], "-", 2) == 0 && !argv[1][1])
		return (cd_handle_dash(ms, oldpwd));
	target = cd_get_target(argc, argv, ms);
	if (!target || !*target)
	{
		builtin_puterr3("minishell: cd: ", "HOME not set", "\n");
		free(oldpwd);
		return (1);
	}
	expanded = cd_expand_tilde(target, ms);
	if (expanded)
		target = expanded;
	if (chdir(target) != 0)
		return (cd_handle_error(target, oldpwd, expanded));
	cd_update_env(ms, oldpwd);
	free(expanded);
	return (0);
}
