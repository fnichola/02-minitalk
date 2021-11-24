/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:11 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/24 11:04:56 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <unistd.h>

int	main(void)
{
	ft_printf("Server running, PID: %d\n", getpid());
	pause();
	return (0);
}
