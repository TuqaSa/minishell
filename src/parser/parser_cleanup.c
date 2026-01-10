/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:51 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:53 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_cmd_free_argv(t_cmd *command)
{
	size_t	arg_index;

	if (!command || !command->argv)
		return ;
	arg_index = 0;
	while (command->argv[arg_index])
	{
		free(command->argv[arg_index]);
		arg_index++;
	}
	free(command->argv);
	command->argv = NULL;
}

static void	parser_cmd_free_reds(t_cmd *command)
{
	size_t	redir_index;

	if (!command || !command->reds)
		return ;
	redir_index = 0;
	while (redir_index < command->nreds)
	{
		parser_cleanup_redir(&command->reds[redir_index]);
		redir_index++;
	}
	free(command->reds);
	command->reds = NULL;
	command->nreds = 0;
}

/* Public functions */
int	parser_cleanup_parse_error(char **argv_array,
		size_t argc_count, t_cmd *output_cmd)
{
	size_t	arg_index;

	(void)argc_count;
	if (argv_array)
	{
		arg_index = 0;
		while (argv_array[arg_index])
		{
			free(argv_array[arg_index]);
			arg_index++;
		}
		free(argv_array);
	}
	ms_cmd_free(output_cmd);
	return (-1);
}

void	ms_cmd_free(t_cmd *command)
{
	if (!command)
		return ;
	parser_cmd_free_argv(command);
	parser_cmd_free_reds(command);
}
