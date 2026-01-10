/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:26 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:27 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_echoctl(bool enable)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	if (enable)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}
