/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:25 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:26 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_array_expand(char **old_envp, char *new_entry)
{
	size_t	env_count;
	char	**new_array;
	size_t	i;

	env_count = 0;
	while (old_envp && old_envp[env_count])
		env_count++;
	new_array = (char **)ft_calloc(env_count + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_array[i] = old_envp[i];
		i++;
	}
	new_array[env_count] = new_entry;
	new_array[env_count + 1] = NULL;
	return (new_array);
}

static int	env_entry_replace(t_ms *ms, const char *name, char *new_entry)
{
	int	entry_index;

	entry_index = env_key_find_index(ms->envp, name);
	if (entry_index >= 0)
	{
		free(ms->envp[entry_index]);
		ms->envp[entry_index] = new_entry;
		return (1);
	}
	return (0);
}

static char	**env_array_shrink(char **old_envp, int remove_index)
{
	size_t	env_count;
	char	**new_array;
	size_t	i;
	size_t	j;

	env_count = 0;
	while (old_envp && old_envp[env_count])
		env_count++;
	new_array = (char **)ft_calloc(env_count, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env_count)
	{
		if ((int)i == remove_index)
		{
			free(old_envp[i]);
			i++;
			continue ;
		}
		new_array[j++] = old_envp[i++];
	}
	new_array[j] = NULL;
	return (new_array);
}

int	env_variable_set(t_ms *ms, const char *name, const char *value)
{
	char		*new_entry;
	char		**new_array;
	const char	*safe_value;

	if (!env_name_validate(name))
		return (-1);
	safe_value = value;
	if (!safe_value)
		safe_value = "";
	new_entry = env_pair_create(name, safe_value);
	if (!new_entry)
		return (-1);
	if (env_entry_replace(ms, name, new_entry))
		return (0);
	new_array = env_array_expand(ms->envp, new_entry);
	if (!new_array)
	{
		free(new_entry);
		return (-1);
	}
	free(ms->envp);
	ms->envp = new_array;
	return (0);
}

int	env_variable_unset(t_ms *ms, const char *name)
{
	int		var_index;
	char	**new_array;

	if (!env_name_validate(name))
		return (-1);
	var_index = env_key_find_index(ms->envp, name);
	if (var_index < 0)
		return (0);
	new_array = env_array_shrink(ms->envp, var_index);
	if (!new_array)
		return (-1);
	free(ms->envp);
	ms->envp = new_array;
	return (0);
}
