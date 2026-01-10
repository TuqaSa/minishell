/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:31 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:32 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_pair_create(const char *key, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

int	env_key_find_index(char **envp, const char *name)
{
	size_t	name_len;
	size_t	i;

	name_len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], name, name_len) && envp[i][name_len] == '=')
			return ((int)i);
		i++;
	}
	return (-1);
}

int	env_name_validate(const char *s)
{
	size_t	i;

	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
