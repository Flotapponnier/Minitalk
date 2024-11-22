/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:36:05 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/14 15:27:05 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handle(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	current_byte = 0;
	static int				bit_count = 0;

	(void)ucontext;
	if (sig == SIGUSR2)
		current_byte |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (current_byte == '\0')
			kill(info->si_pid, SIGUSR2);
		else
			write(1, &current_byte, 1);
		current_byte = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = handle;
	sa_newsig.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_newsig.sa_mask);
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		ft_printf("Error setting up signal handler for SIGUSR1\n");
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		ft_printf("Error setting up signal handler for SIGUSR2\n");
	ft_printf("Listening on pid: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
