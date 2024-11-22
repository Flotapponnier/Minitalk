/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:27:04 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/14 15:27:28 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, char a)
{
	int				i;
	unsigned char	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (a >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	if (!pid || !message)
	{
		ft_printf("error pid or message incorrect\n");
		return (1);
	}
	i = 0;
	while (message[i])
	{
		send_bit(pid, message[i]);
		i++;
	}
	return (0);
}
