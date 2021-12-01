/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:36:29 by fnichola          #+#    #+#             */
/*   Updated: 2021/12/01 10:46:28 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

void	signal_handler(int signum, siginfo_t *info, void *uap)
{
	(void)uap;
	(void)info;
	g_server_ack = (signum == SIGUSR2);
}

static void	wait_for_ack(void)
{
	int	t;

	t = 0;
	while (t++ < 10000)
	{
		if (g_server_ack)
			break ;
		usleep(1);
	}
}

static void	send_char(int pid, char c)
{
	int		i;
	int		t;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		wait_for_ack();
		if (!g_server_ack)
		{
			ft_printf("Transmission failure!\n" \
			"Please check PID or restart server.\n");
			exit(EXIT_FAILURE);
		}
		else
			g_server_ack = 0;
		i--;
	}
}

void	send_line(int pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}

void	send_file(int fd, int server_pid)
{
	char	*message;

	message = get_next_line(fd);
	while (message)
	{
		send_line(server_pid, message);
		free(message);
		message = get_next_line(fd);
	}
}
