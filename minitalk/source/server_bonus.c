/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:45:10 by husamuel          #+#    #+#             */
/*   Updated: 2024/11/21 14:01:14 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minitalk.h"

char	*join_bit(char *str, char n)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char) + 1);
		str[i] = n;
		str[++i] = '\0';
		return (str);
	}
	new = (char *)malloc((ft_strlen(str) + 1) * sizeof(char) + 1);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = n;
	new[++i] = '\0';
	free(str);
	return (new);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int	current_char;
	static int	bit;
	static char	*string;

	(void)context;
	if (sig == SIGUSR1)
		current_char |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (current_char == '\0')
		{
			ft_printf("%s\n", string);
			free(string);
			string = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		else
			string = join_bit(string, current_char);
		bit = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	int	id;

	id = getpid();
	ft_printf("%d\n", id);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
	}
}
