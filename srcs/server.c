/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:11 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/24 16:52:59 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void	signal_handler()
{
	ft_printf("Signal received!\n");
	exit(1);
}

int	main(void)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	ft_printf("Server running, PID: %d\n", getpid());
	pause();
	return (0);
}
