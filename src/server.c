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

static void	signal_handler(int signal);

int	main(void)
{
	ft_printf("Server pid: %i\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (true)
		;
}

//SIGUSER1: 10=> 1
//SIGUSER2: 12=> 0
//link: https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf

static void	signal_handler(int signal)
{
	static int	c;
	static int	bits_read;

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
