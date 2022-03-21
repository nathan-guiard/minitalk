/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_putbin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:01:53 by nguiard           #+#    #+#             */
/*   Updated: 2022/01/31 17:17:31 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_putbin(unsigned int n)
{
	static int	i;

	i = 0;
	if (n <= 1)
	{
		i += count_putchar(n + '0');
		return (i);
	}
	else
	{
		count_putbin(n / 2);
		i += count_putchar((n % 2) + 48);
	}
	return (i);
}
