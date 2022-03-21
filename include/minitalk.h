/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:59:24 by nguiard           #+#    #+#             */
/*   Updated: 2022/02/14 14:23:59 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <unistd.h>
# include "libft.h"
# include <signal.h>

# define EMPTY		1
# define NO_EMPTY	0

int		get_pre_signal(int sig);
char	*get_string_in_signal(int sig, int len);
void	get_sig(int sig, siginfo_t *truc, void *context);
int		print_err(char *s);
int		sig_to_char(int sig);
void	send_str(unsigned char *str, pid_t pid, int status);
int		send_char(unsigned char c, pid_t pid, int slp_time);
void	sig_back(int sig, siginfo_t *truc, void *context);
int		error_pid(pid_t pid);
void	error_pid_client(pid_t pid);

#endif