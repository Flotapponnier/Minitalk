/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:36:20 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/14 15:43:22 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		usleep(50);
		i--;
	}
}

void	send_null(int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		kill(pid, SIGUSR1);
		usleep(500);
		i--;
	}
}

volatile sig_atomic_t	g_ack_received = 0;

void	handler_sig(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_printf("Message received by server\n");
		g_ack_received = 1;
	}
}

int	check_valid(int argc, char *argv[], int *pid, char **message)
{
	if (argc != 3)
	{
		ft_printf("usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	*pid = ft_atoi(argv[1]);
	*message = ft_strjoin(argv[2], "\n");
	if (!(*pid) || !(*message))
	{
		ft_printf("error: invalid pid or message\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa_newsig;
	int					pid;
	char				*message;
	int					i;

	if (check_valid(argc, argv, &pid, &message))
		return (1);
	sa_newsig.sa_handler = handler_sig;
	sa_newsig.sa_flags = 0;
	sigemptyset(&sa_newsig.sa_mask);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		ft_printf("Error setting up signal handler for SIGUSR2\n");
	i = -1;
	while (message[++i])
		send_bit(pid, message[i]);
	free(message);
	send_null(pid);
	while (!g_ack_received)
		pause();
	return (0);
}
