/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/14 16:17:58 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "corekit.h"

//Acknowledgment ascii character
#define ACKNOWLEDGE	6

static void	signal_handler(int signal, siginfo_t *info, void *content);

int	main(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &signal_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR1's behavior"), 0);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR2's behavior"), 0);
	ft_printf("Server pid: %i\n", getpid());
	// signal(SIGUSR1, signal_handler);
	// signal(SIGUSR2, signal_handler);
	while (true)
		;
}

//SIGUSER1: 10=> 1
//SIGUSER2: 12=> 0
//link: https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf
//when the char is 6 (Acknowledgment) => the message is end
//=> printf '\n' and send the reply
static void	signal_handler(int signal, siginfo_t *info, void *content)
{
	static int	c;
	static int	bits_read;

	(void)content;
	if (signal == SIGUSR1)
		c |= (0x01 << bits_read);
	bits_read++;
	if (bits_read == 8)
	{
		if (c == ACKNOWLEDGE)
		{
			ft_printf("\n");
			kill(info->si_pid, ACKNOWLEDGE);
			bits_read = 0;
			c = 0;
			return;
		}
		ft_printf("%c", c);
		bits_read = 0;
		c = 0;
	}
}
