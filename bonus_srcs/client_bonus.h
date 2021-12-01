/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:37:36 by fnichola          #+#    #+#             */
/*   Updated: 2021/12/01 10:57:04 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H
# include "../libft/libft.h"
# include "gnl/get_next_line.h"
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>

extern volatile sig_atomic_t	g_server_ack;

void	signal_handler(int signum, siginfo_t *info, void *uap);
void	send_line(int pid, char *message);
void	send_file(int fd, int server_pid);

#endif
