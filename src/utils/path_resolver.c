/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:19:53 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:19:54 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_extract_segment(const char *path, size_t start, size_t end)
{
	if (start == end)
		return (ft_strdup("."));
	return (ft_substr(path, start, end - start));
}

static char	*path_try_segment(const char *path, size_t start,
		size_t end, const char *cmd)
{
	char	*segdup;
	char	*cand;

	segdup = path_extract_segment(path, start, end);
	if (!segdup)
		return (NULL);
	cand = ms_path_build_candidate(segdup, cmd);
	free(segdup);
	if (!cand)
		return (NULL);
	if (ms_path_test_candidate(cand))
		return (cand);
	free(cand);
	return (NULL);
}

static size_t	path_find_next_separator(const char *path, size_t start)
{
	size_t	i;

	i = start;
	while (path[i] && path[i] != ':')
		i++;
	return (i);
}

char	*ms_resolve_path(t_ms *ms, const char *cmd)
{
	const char	*path;
	size_t		i;
	size_t		start;
	char		*result;

	path = env_value_get(ms, "PATH");
	if (!path || !*path)
		return (NULL);
	start = 0;
	while (path[start])
	{
		i = path_find_next_separator(path, start);
		result = path_try_segment(path, start, i, cmd);
		if (result)
			return (result);
		if (path[i] == '\0')
			break ;
		start = i + 1;
	}
	return (NULL);
}
