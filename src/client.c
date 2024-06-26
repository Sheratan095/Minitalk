/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/06/04 14:29:05 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "corekit.h"

//Acknowledgment ascii character
#define ACKNOWLEDGE	6

int	g_semaphore;
static void	send_string(char *string, int pid);
static void	send_char(char c, __pid_t pid);
static void	hanlde_signal(int signal, siginfo_t *info, void *content);

// sa_newsig.sa_sigaction = &hanlde_signal;
//	subscribes the function to singal reception
//Check argouments
//Check pid validity
//	link: ibm.com/docs/it/zos/2.4.0?topic=functions-kill-send-signal-process
//Sigaction() assign to the specified signal (SIGUSR1- SIGUSR2) the sigaction
int	main(int argc, char *argv[])
{
	__pid_t				srv_pid;
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &hanlde_signal;
	sa_newsig.sa_flags = SA_SIGINFO;
	g_semaphore = 1;
	if (argc != 3)
	{
		ft_printf("Error, right input format is:\n");
		ft_printf("./client <SERVER PID> <STRING TO SEND>\n");
		exit(0);
	}
	srv_pid = ft_atoi(argv[1]);
	if (srv_pid <= 0)
		return (ft_printf("Error, invalid pid"));
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR1's behavior"), 0);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		return (ft_printf("Failed to change SIGUSR2's behavior"), 0);
	send_string(argv[2], srv_pid);
}

//Send all char of the string
//At the end, send the acknowledgement
static void	send_string(char *string, int pid)
{
	int	i;

	i = 0;
	while (string[i])
		send_char(string[i++], pid);
	send_char(ACKNOWLEDGE, pid);
}

//Check_senging is used to check if the signal was
//	sent by return value of kill()
//Bits rappresent the number of bits already sent
//Send while i is less than 8 (number of bits in a char)
//	"Create" each time a new bit octet that has all 0 exept
//		Beacause rigth shift 1 (00000001) of nbits
//		for bits = 2 => 00000100 (first n zero goes behind number)
//	Do AND bit to bit between this 'octect' and the char
//		since all bits in the first octect are set to 0,
//		just that one set to one will metter in AND operation
//		that will determin if the corresponding bit in the char
//		in nbits position is 0 or 1 by AND
//	if (result == 1)
//		send SIGURS1 (1)
//	else (result = 1)
//		send SIGURS2 (1)
//	Check the return value of kill()
//	Uspleep is used to avoid sending bits too close to each other
//		because the server can't read them (set to 100 just for fan)
//Client wait until the server is ready to recive another bit
//	it's managed by a 'semaphore' that change its status when the server
//	send SIGUSR1 to client
static void	send_char(char c, __pid_t pid)
{
	int	bits;
	int	check_sending;

	bits = 0;
	while (bits < 8)
	{
		if (c & (0x01 << bits))
			check_sending = kill(pid, SIGUSR1);
		else
			check_sending = kill(pid, SIGUSR2);
		if (check_sending < 0)
		{
			ft_printf("Error during sending the bits\nCheck the pid\n");
			exit(0);
		}
		bits++;
		while (g_semaphore == 0)
			usleep(100);
		g_semaphore = 0;
		usleep(100);
	}
}

//SIGURS1 server is ready to recive another bit, semaphore is green
static void	hanlde_signal(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGUSR1)
		g_semaphore = 1;
}
