/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:58:34 by ealshari          #+#    #+#             */
/*   Updated: 2024/12/30 12:35:22 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees memory allocated for the array of words up to the given size
static int	free_memory(char **word_array, int words_allocated)
{
	while (words_allocated--)
		free(word_array[words_allocated]);
	free(word_array);
	return (-1);
}

// Counts the number of words in the string based on the given delimiter
static int	get_word_count(const char *str, char delimiter)
{
	int	word_count;
	int	in_word;

	word_count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delimiter && in_word == 0)
		{
			in_word = 1;
			word_count++;
		}
		else if (*str == delimiter)
			in_word = 0;
		str++;
	}
	return (word_count);
}

// Copies a word from the source string to a new string and returns it
static char	*allocate_and_copy_word(const char *str, int word_length)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < word_length)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// Splits the string into individual words and stores them in the word_array
static int	split_into_words(char **word_array, const char *str, char delimiter)
{
	int	word_length;
	int	word_index;

	word_index = 0;
	while (*str)
	{
		if (*str != delimiter)
		{
			word_length = 0;
			while (str[word_length] && str[word_length] != delimiter)
				word_length++;
			word_array[word_index] = allocate_and_copy_word(str, word_length);
			if (!word_array[word_index])
				return (free_memory(word_array, word_index));
			str += word_length;
			word_index++;
		}
		else
			str++;
	}
	word_array[word_index] = 0;
	return (0);
}

// Main function to split the string into an array of words based on a delimiter
char	**ft_split(const char *str, char delimiter)
{
	char	**word_array;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = get_word_count(str, delimiter);
	word_array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!word_array)
		return (NULL);
	if (split_into_words(word_array, str, delimiter) == -1)
		return (NULL);
	return (word_array);
}
