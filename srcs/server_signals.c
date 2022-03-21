/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:38:47 by nguiard           #+#    #+#             */
/*   Updated: 2022/02/06 17:34:45 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	sig_to_char(int sig)
{
	static unsigned char	c;
	static int				count;
	unsigned char			tmp;
	static int				i;

	tmp = 0;
	if (count < 8 && (sig == SIGUSR1 || sig == SIGUSR2))
	{
		if (sig == SIGUSR2)
			tmp = 1;
		tmp = tmp << count;
		c |= tmp;
		count++;
	}
	if (count == 8)
	{
		count = 0;
		tmp = c;
		c = 0;
		return (tmp);
	}
	return (-1);
}

int	get_pre_signal(int sig)
{
	static char	len_or_pid[10];
	static int	i;
	int			c;

	c = sig_to_char(sig);
	if (c != -1)
	{
		len_or_pid[i] = (char)c;
		i++;
	}
	if (c == 124)
	{
		i = 0;
		return (ft_atoi(len_or_pid));
	}
	return (-1);
}

char	*get_string_in_signal(int sig, int len)
{
	static int	i;
	static int	first_entry;
	int			c;
	static char	*str;

	c = sig_to_char(sig);
	if (len == 0 && c != -1)
		return (ft_strdup(""));
	if (first_entry == 0)
	{
		str = ft_calloc(sizeof(char), len + 1);
		first_entry = 1;
	}
	if (c != -1)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	if (c == 0)
	{
		first_entry = 0;
		i = 0;
		return (str);
	}
	return (NULL);
}

void	final_step(int *len, int *status, int *pid, char *final_string)
{
	if (*len != 0)
	{
		ft_printf("%s", final_string);
		free(final_string);
	}
	*status = 0;
	*pid = -1;
	*len = -1;
}

void	get_sig(int sig, siginfo_t *truc, void *context)
{
	static int		status;
	char			*final_string;
	static pid_t	pid;
	static int		len;

	if (status == 0)
	{
		len = get_pre_signal(sig);
		if (len != -1)
			status = 1;
		return ;
	}
	if (status == 1)
	{
		pid = get_pre_signal(sig);
		status = error_pid(pid);
		if (len == 0 && status == 2)
			status = 3;
		return ;
	}
	if (status == 2)
		final_string = get_string_in_signal(sig, len);
	if (final_string == NULL)
		return ;
	final_step(&len, &status, &pid, final_string);
}
