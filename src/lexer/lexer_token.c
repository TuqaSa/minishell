/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:25 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:26 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_vector_expand(t_tokvec *token_vector)
{
	size_t	new_capacity;
	t_token	*new_vector;
	size_t	token_index;

	if (token_vector->cap > 0)
		new_capacity = token_vector->cap * 2;
	else
		new_capacity = 8;
	new_vector = (t_token *)ft_calloc(new_capacity, sizeof(t_token));
	if (!new_vector)
		return (-1);
	token_index = 0;
	while (token_index < token_vector->n)
	{
		new_vector[token_index] = token_vector->v[token_index];
		token_index++;
	}
	free(token_vector->v);
	token_vector->v = new_vector;
	token_vector->cap = new_capacity;
	return (0);
}

int	lexer_tokvec_push(t_tokvec *token_vector,
		t_toktype token_type, char *raw_content)
{
	if (token_vector->n + 1 > token_vector->cap)
	{
		if (token_vector_expand(token_vector) < 0)
			return (-1);
	}
	token_vector->v[token_vector->n].type = token_type;
	token_vector->v[token_vector->n].raw = raw_content;
	token_vector->n++;
	return (0);
}

void	lexer_tokvec_free(t_tokvec *token_vector)
{
	size_t	token_index;

	if (!token_vector || !token_vector->v)
		return ;
	token_index = 0;
	while (token_index < token_vector->n)
	{
		free(token_vector->v[token_index].raw);
		token_index++;
	}
	free(token_vector->v);
	token_vector->v = NULL;
	token_vector->n = 0;
	token_vector->cap = 0;
}
