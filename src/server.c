/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/14 16:18:04 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "corekit.h"

static void	signal_handler(int signal, siginfo_t *info, void *content);

int	main(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &signal_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		return (ft_printf("Error duging changing SIGUSR1's beahavior"), 0);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		return (ft_printf("Error duging changing SIGUSR2's beahavior"), 0);
	ft_printf("Server pid: %i\n\n", getpid());
	while (true)
		;
}

//SIGUSER1: 10=> 1
//SIGUSER2: 12=> 0
//link: https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf

static void	signal_handler(int signal, siginfo_t *info, void *content)
{
	static int	c;
	static int	bits_read;
	static int	current_client_pid;

	(void)content;
	if (current_client_pid != info->si_pid && current_client_pid != 0)
	{
		ft_printf("\n\n");
		bits_read = 0;
		c = 0;
	}
	current_client_pid = info->si_pid;
	if (signal == SIGUSR1)
		c |= (0x01 << bits_read);
	bits_read++;
	if (bits_read == 8)
	{
		ft_printf("%c", c);
		bits_read = 0;
		c = 0;
	}
}
