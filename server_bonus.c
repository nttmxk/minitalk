/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:22:28 by jinoh             #+#    #+#             */
/*   Updated: 2022/02/03 15:08:19 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_error(void)
{
	write(2, "Crash!\n", 7);
	exit(1);
}

int	check_pid(siginfo_t *info, int *pid)
{
	if (*pid == 0)
		*pid = info->si_pid;
	else if (*pid != info->si_pid)
	{
		kill(*pid, SIGUSR2);
		kill(info->si_pid, SIGUSR2);
		return (1);
	}
	return (0);
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	buf[500];
	static int				i;
	static int				bit;
	static int				pid;

	if (bit == 8)
	{
		bit = 0;
		buf[++i] = 0;
	}
	if (signo == SIGUSR1)
		++bit;
	else if (signo == SIGUSR2)
		buf[i] += 1 << (8 - ++bit);
	if (check_pid(info, &pid))
		ft_error();
	if (i > 499 || (bit == 8 && buf[i] == '\0'))
	{
		write(1, buf, i);
		write(1, "\n", 1);
		i = -1;
		pid = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	set_sig(struct sigaction *act)
{
	act->sa_sigaction = sig_handler;
	act->sa_flags = SA_SIGINFO;
}

int	main(void)
{
	struct sigaction	act1;

	printf("Server PID: %d\n", getpid());
	set_sig(&act1);
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act1, NULL);
	while (1)
		pause();
	return (0);
}
