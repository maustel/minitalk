/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:44:34 by maustel           #+#    #+#             */
/*   Updated: 2024/05/15 12:24:36 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
// #include "libft/libft.h"

char	*ft_cjoin(char *s1, char c)
{
	char	*str;
	int		size;
	int		i;

	if (s1)
		size = ft_strlen(s1) + 1;
	else
		size = 1;
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	str[i++] = c;
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

void	write_to_string(int byte, siginfo_t *info)
{
	static char	*str = NULL;

	if (byte != '\0')
	{
		str = ft_cjoin(str, byte);
		if (!str)
			return ;
	}
	else
	{
		kill(info->si_pid, SIGUSR2);
		usleep(100);
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	i;
	static int	byte;

	if (sig == SIGUSR1)
		byte = byte * 2 + 1;
	if (sig == SIGUSR2)
		byte = byte * 2;
	i++;
	if (i == 8)
	{
		write_to_string(byte, info);
		i = 0;
		byte = 0;
	}
	(void) context;
}

		// exit(0);
// void	leak(void)
// {
// 	system("leaks server");
// }
	// atexit(leak);

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
