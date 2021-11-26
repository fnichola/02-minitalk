/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:24:49 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/26 21:51:33 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include <sys/types.h>
#include <signal.h>

sig_atomic_t	g_server_ack = 0;

void	signal_handler(int signum, siginfo_t *info, void *uap)
{
	(void)uap;
	(void)info;
	g_server_ack = (signum == SIGUSR2);
}

static void	init_sigaction()
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = 0 | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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
		usleep(100);
		i--;
	}
}

static void	send_line(int pid, char *message)
{
	size_t	i;
	int		t;

	i = 0;
	t = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		while (t++ < 100000)
		{
			if (g_server_ack)
				break ;
			usleep(1);
		}
		if (!g_server_ack)
		{
			ft_printf("Transmission failure!\n");
			exit(EXIT_FAILURE);
		}
		else
			g_server_ack = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	message = NULL;
	init_sigaction();
	if (argc < 2)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n" \
			"Please provide server PID.\n" \
			"./client server_pid [message]\n");
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (argc == 3)
		send_line(server_pid, argv[2]);
	else if (argc == 2)
	{
		message = get_next_line(STDIN_FILENO);
		while (message)
		{
			send_line(server_pid, message);
			message = get_next_line(STDIN_FILENO);
		}
	}
	return (0);
}
