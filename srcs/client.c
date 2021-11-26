/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:24:49 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/26 20:37:52 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include <sys/types.h>
#include <signal.h>

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
		usleep(5000);
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
	int		server_pid;
	char	*message;

	message = NULL;
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
