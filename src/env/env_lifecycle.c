/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:15 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:15 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_array_cleanup_partial(char **env_array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

char	**env_context_init(char **envp_src)
{
	size_t	env_count;
	char	**new_env;
	size_t	i;

	env_count = 0;
	while (envp_src && envp_src[env_count])
		env_count++;
	new_env = (char **)ft_calloc(env_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = ft_strdup(envp_src[i]);
		if (!new_env[i])
		{
			env_array_cleanup_partial(new_env, i);
			return (NULL);
		}
		i++;
	}
	new_env[env_count] = NULL;
	return (new_env);
}

void	env_context_free(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
