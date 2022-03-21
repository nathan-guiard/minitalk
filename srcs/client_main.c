/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:36:45 by nguiard           #+#    #+#             */
/*   Updated: 2022/02/14 14:14:05 by nguiard          ###   ########.fr       */
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

void	error_pid_client(pid_t pid)
{
	if (pid <= 100 || pid >= 99998)
		exit (print_err("Invalid PID\n"));
}

unsigned char	*build_tab(char **argv)
{
	unsigned char	*to_free;
	unsigned char	*tab;
	char			*itoa_tab;

	itoa_tab = ft_itoa(getpid());
	tab = (unsigned char *)ft_strjoin(itoa_tab, "|");
	free(itoa_tab);
	to_free = tab;
	tab = (unsigned char *)ft_strjoin("|", (char *)tab);
	free(to_free);
	to_free = tab;
	itoa_tab = ft_itoa(ft_strlen(argv[2]));
	tab = (unsigned char *)ft_strjoin(itoa_tab, (char *)tab);
	free(to_free);
	free(itoa_tab);
	to_free = tab;
	tab = (unsigned char *)ft_strjoin((char *)tab, argv[2]);
	free(to_free);
	return (tab);
}

unsigned char	*build_tab_empty(void)
{
	unsigned char	*to_free;
	unsigned char	*tab;
	char			*itoa_tab;

	itoa_tab = ft_itoa(getpid());
	tab = (unsigned char *)ft_strjoin(itoa_tab, "|");
	free(itoa_tab);
	to_free = tab;
	tab = (unsigned char *)ft_strjoin("|", (char *)tab);
	free(to_free);
	return (tab);
}

int	main(int argc, char **argv)
{
	unsigned char		c;
	unsigned char		*tab;
	int					pid;

	if (argc != 3)
		exit(print_err("Must be: ./cilent <server_PID> <message>\n"));
	if (ft_strlen(argv[2]) != 0)
		tab = build_tab(argv);
	else
		tab = build_tab_empty();
	if (ft_strlen(argv[1]) >= 6)
		exit (print_err("Invalid PID\n"));
	pid = ft_atoi(argv[1]);
	error_pid_client(pid);
	if (ft_strlen(argv[2]) != 0)
		send_str(tab, pid, NO_EMPTY);
	else
		send_str(tab, pid, EMPTY);
	return (0);
}
