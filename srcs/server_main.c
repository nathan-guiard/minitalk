/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:49:39 by nguiard           #+#    #+#             */
/*   Updated: 2022/02/06 17:33:59 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	print_err(char *s)
{
	set_layout(C_RED, C_RESET, C_BOLD);
	ft_putstr_fd(s, 2);
	set_layout(C_RESET, C_RESET, C_RESET);
	return (1);
}

int	error_pid(pid_t pid)
{
	if (pid == -1)
		return (1);
	if (pid <= 100 || pid >= 99998)
		exit (print_err("Invalid PID\n"));
	return (2);
}

void	print_pid(void)
{
	ft_printf("Server PID: ");
	set_layout(C_HYELLOW, C_RESET, C_RESET);
	ft_printf("%d\n", getpid());
	set_layout(C_RESET, C_RESET, C_RESET);
}

int	main(void)
{
	struct sigaction	sa;

	print_pid();
	sa.sa_sigaction = get_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
}
