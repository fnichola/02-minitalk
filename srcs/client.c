/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:24:49 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/30 22:21:45 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_server_ack = 0;

void	signal_handler(int signum, siginfo_t *info, void *uap)
{
	(void)uap;
	(void)info;
	g_server_ack = (signum == SIGUSR2);
}

void	wait_for_ack(void)
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

static void	send_line(int pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;

	if (argc != 3)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n" \
			"Please provide server PID and message.\n" \
			"ex: ./client 12345 \"Hello World\"\n");
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n" \
		"Invalid PID.\n");
		return (0);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);
	send_line(server_pid, argv[2]);
	return (0);
}
