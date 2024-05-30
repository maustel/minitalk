/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:48:55 by maustel           #+#    #+#             */
/*   Updated: 2024/04/26 12:48:55 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
// #include "libft/libft.h"

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
	pid_t	server_pid;
	int		i;

	if (argc != 3)
	{
		ft_printf("\x1b[31mWrong input. Expected input: PID 'your text'\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_signals(server_pid, argv[2][i]);
		i++;
	}
	send_signals(server_pid, '\0');
	return (0);
}
