/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:11 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/27 14:37:21 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

sig_atomic_t	g_client_pid = 0;

void	signal_handler(int signum, siginfo_t *info, void *uap)
{
	static char	c;
	static int	bits;
	
	(void)uap;
	g_client_pid = info->si_pid;
	c |= (signum == SIGUSR2);
	bits++;
	if (bits == 8)
	{
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
	else
		c <<= 1;
	kill(g_client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = 0 | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	ft_printf("Server running, PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
