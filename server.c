/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:45:24 by maustel           #+#    #+#             */
/*   Updated: 2024/04/26 12:45:24 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
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

void	write_to_string(int byte)
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
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
	}
}

void	handle_signal(int sig)
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
		write_to_string(byte);
		i = 0;
		byte = 0;
	}
}

		// exit(0);
// void	leak(void)
// {
// 	system("leaks server");
// }
	// atexit(leak);

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, handle_signal);
		signal(SIGUSR2, handle_signal);
		pause();
	}
	return (0);
}
