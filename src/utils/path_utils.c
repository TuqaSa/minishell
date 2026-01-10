/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:19:58 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:19:59 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_path_join3(const char *a, const char *b, const char *c)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(a, b);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, c);
	free(temp);
	return (result);
}
