/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:47 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:49 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_handle_split_word(char *expanded_word, char ***argv_ptr,
		size_t *argc_ptr)
{
	char	**split_words;
	int		result;

	split_words = ft_split(expanded_word, ' ');
	if (!split_words)
	{
		free(expanded_word);
		return (-1);
	}
	result = parser_add_split_words(argv_ptr, argc_ptr, split_words);
	parser_free_split(split_words);
	free(expanded_word);
	return (result);
}

int	parser_handle_single_word(char *expanded_word, const char *raw_token,
		char ***argv_ptr, size_t *argc_ptr)
{
	if (expanded_word[0] == '\0' && !parser_is_quoted_token(raw_token))
	{
		free(expanded_word);
		return (0);
	}
	if (push_word(argv_ptr, argc_ptr, expanded_word) < 0)
	{
		free(expanded_word);
		return (-1);
	}
	return (0);
}
