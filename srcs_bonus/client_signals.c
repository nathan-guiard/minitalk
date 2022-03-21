/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:47:02 by nguiard           #+#    #+#             */
/*   Updated: 2022/02/14 14:21:17 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_pid_client(pid_t pid)
{
	if (pid <= 100 || pid >= 99998)
		exit (print_err("Invalid PID\n"));
}

int	send_char(unsigned char c, pid_t pid, int slp_time)
{
	int	i;
	int	tmp;
	int	kill_status;

	i = 1;
	tmp = c;
	while (i <= 8)
	{
		if (tmp % 2 == 1)
			kill_status = kill(pid, SIGUSR2);
		else
			kill_status = kill(pid, SIGUSR1);
		tmp >>= 1;
		i++;
		if (kill_status == -1)
			return (-1);
		usleep(50);
	}
	return (0);
}

void	send_str(unsigned char *str, pid_t pid, int status)
{
	int	i;
	int	slp_time;

	if (ft_strlen((char *)str) <= 3000)
		slp_time = 40;
	else
		slp_time = 125;
	i = 0;
	while (str[i])
	{
		if (send_char(str[i], pid, slp_time) == -1)
		{
			free(str);
			exit (print_err("Kill failed, surely bad PID imput\n"));
		}
		i++;
	}
	if (status == NO_EMPTY)
		send_char(0, pid, 30);
	else
		kill(pid, SIGUSR1);
}

void	sig_back(int sig, siginfo_t *truc, void *context)
{
	if (sig == SIGUSR2)
	{
		set_layout(C_CYAN, C_RESET, C_ITALIC);
		ft_printf("Accusé de reception du serveur ");
		set_layout(C_CYAN, C_RESET, C_BOLD);
		ft_printf("recu");
		set_layout(C_CYAN, C_RESET, C_RESET);
		set_layout(C_CYAN, C_RESET, C_ITALIC);
		ft_printf("!\n");
		set_layout(C_RESET, C_RESET, C_RESET);
	}
	exit (0);
}
