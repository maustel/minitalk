/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:44:39 by maustel           #+#    #+#             */
/*   Updated: 2024/05/15 11:22:34 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
// #include "libft/libft.h"

void	received_signal(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("\x1b[32mSignal has been received!\n");
}

void	send_signals(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(250);
	}
}

int	main(int argc, char **argv)
{
	int					i;

	signal(SIGUSR2, received_signal);
	if (argc != 3)
	{
		ft_printf("\x1b[31mWrong input. Expected input: PID 'your text'\n");
		return (1);
	}
	i = 0;
	while (argv[2][i])
	{
		send_signals(ft_atoi(argv[1]), argv[2][i]);
		i++;
	}
	send_signals(ft_atoi(argv[1]), '\0');
	return (0);
}
