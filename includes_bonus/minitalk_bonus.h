/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:37:57 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/14 12:37:58 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define MAX_BITS 8

// Function declarations
void    handle(int sig, siginfo_t *info, void *ucontext);
void send_bit(int pid, char a);

#endif

