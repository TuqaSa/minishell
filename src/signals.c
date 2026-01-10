/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:20 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:18:21 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	ms_signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_sigint_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
}
