/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/06/04 14:33:10 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "corekit.h"

//Acknowledgment ascii character
#define ACKNOWLEDGE	6

static void	signal_handler(int signal, siginfo_t *info, void *content);
static void	reset_integers(int *c, int *bits);

int	main(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &signal_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR1's behavior"), 0);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR2's behavior"), 0);
	ft_printf("Server pid: %i\n\n", getpid());
	while (true)
		pause();
}

//SIGUSER1: 10=> 1
//SIGUSER2: 12=> 0
//link: https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf
//when the char is 6 (Acknowledgment) => the message is end
//=> printf '\n' and send the reply
//	(void)content; => for flags
//uslpeep interrupt the process until recive a signal
//Last singal sent if for confirm that server is ready to recive again
//Last printf is done inside return() beacause of norminette
static void	signal_handler(int signal, siginfo_t *info, void *content)
{
	static int	c;
	static int	bits_read;
	static int	current_client_pid;

	(void)content;
	if (current_client_pid != info->si_pid)
	{
		ft_printf("\n\n");
		reset_integers(&c, &bits_read);
	}
	current_client_pid = info->si_pid;
	if (signal == SIGUSR1)
		c |= (0x01 << bits_read);
	bits_read++;
	if (bits_read == 8)
	{
		if (c != ACKNOWLEDGE)
			ft_printf("%c", c);
		else if (kill(info->si_pid, SIGUSR2) < 0)
			ft_printf("Error sending response to client\n");
		reset_integers(&c, &bits_read);
	}
	usleep(100);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_printf("Error: unexpected signal behavior\n", 35);
}

//Just for normi
static void	reset_integers(int *c, int *bits)
{
	*bits = 0;
	*c = 0;
}
