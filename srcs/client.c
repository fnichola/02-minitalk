/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:24:49 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/24 23:30:07 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	if (argc = 2)
		kill(ft_atoi(argv[1]), SIGUSR1);
	return (0);
}
