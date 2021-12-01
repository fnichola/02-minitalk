/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:24:49 by fnichola          #+#    #+#             */
/*   Updated: 2021/12/01 18:18:41 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

volatile sig_atomic_t	g_server_ack = 0;

static void	exit_error(char *error_message)
{
	if (error_message)
		ft_printf_fd(STDERR_FILENO, "Error!\n%s\n", error_message);
	else
		ft_printf_fd(STDERR_FILENO, "Error!\n");
	exit(EXIT_FAILURE);
}

static void	init_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	int		fd;

	init_sigaction();
	fd = STDIN_FILENO;
	if (argc < 2)
	{
		exit_error(USAGE_INSTRUCTIONS);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		exit_error("Invalid PID.");
	if (argc == 2)
		send_file(fd, server_pid);
	else if (argc == 3)
		send_line(server_pid, argv[2]);
	else if (argc == 4 && ft_strncmp(argv[2], "-f", 2) == 0)
	{
		fd = open(argv[3], O_RDONLY);
		send_file(fd, server_pid);
		close(fd);
	}
	return (0);
}
