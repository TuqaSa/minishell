/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:12:19 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:03 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_expand_tilde(const char *target, t_ms *ms)
{
	const char	*home;
	size_t		home_len;
	size_t		rest_len;
	char		*expanded;

	if (target[0] != '~' || (target[1] != '\0' && target[1] != '/'))
		return (NULL);
	home = env_value_get(ms, "HOME");
	if (!home || !*home)
	{
		builtin_puterr3("minishell: cd: ", "HOME not set", "\n");
		return (NULL);
	}
	home_len = ft_strlen(home);
	rest_len = ft_strlen(target + 1);
	expanded = malloc(home_len + rest_len + 1);
	if (!expanded)
		return (NULL);
	ft_memcpy(expanded, home, home_len);
	ft_memcpy(expanded + home_len, target + 1, rest_len);
	expanded[home_len + rest_len] = '\0';
	return (expanded);
}

void	cd_update_env(t_ms *ms, char *oldpwd)
{
	char	*newpwd;

	if (oldpwd)
	{
		env_variable_set(ms, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		env_variable_set(ms, "PWD", newpwd);
		free(newpwd);
	}
}

int	cd_handle_error(const char *target, char *oldpwd, char *expanded)
{
	builtin_puterr3("minishell: cd: ", target, ": ");
	builtin_puterr3(strerror(errno), "\n", "");
	free(oldpwd);
	free(expanded);
	return (1);
}
