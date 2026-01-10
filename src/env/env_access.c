/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:03 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:04 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*env_value_get(t_ms *ms, const char *name)
{
	size_t	name_len;
	size_t	i;

	name_len = ft_strlen(name);
	i = 0;
	while (ms->envp && ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[i], name, name_len)
			&& ms->envp[i][name_len] == '=')
			return (ms->envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
