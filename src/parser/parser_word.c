/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:57 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:59 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_is_quoted_token(const char *raw_input)
{
	size_t	string_length;

	if (!raw_input || !*raw_input)
		return (0);
	string_length = ft_strlen(raw_input);
	return ((raw_input[0] == '"' && raw_input[string_length - 1] == '"')
		|| (raw_input[0] == '\'' && raw_input[string_length - 1] == '\''));
}

int	parser_add_split_words(char ***argv_ptr,
		size_t *argc_ptr, char **split_words)
{
	size_t	word_index;

	word_index = 0;
	while (split_words[word_index])
	{
		if (push_word(argv_ptr, argc_ptr,
				ft_strdup(split_words[word_index])) < 0)
			return (-1);
		word_index++;
	}
	return (0);
}

void	parser_free_split(char **split_words)
{
	size_t	word_index;

	if (!split_words)
		return ;
	word_index = 0;
	while (split_words[word_index])
	{
		free(split_words[word_index]);
		word_index++;
	}
	free(split_words);
}
