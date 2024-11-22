/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:27:13 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/13 21:27:31 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle(int sig)
{
	static unsigned char	current_byte = 0;
	static int				bit_count = 0;

	if (sig == SIGUSR2)
		current_byte |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &current_byte, 1);
		if (current_byte == '\0')
			write(1, "\n", 1);
		current_byte = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	ft_printf("Listening on pid: %d\n", getpid());
	signal(SIGUSR1, handle);
	signal(SIGUSR2, handle);
	while (1)
		pause();
	return (0);
}
