/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:11 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/25 21:26:39 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void	signal_handler(int signum, siginfo_t *info, void *uap)
{
	static char	c;
	static int	bits;
	
	(void)uap;
	(void)info;
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
