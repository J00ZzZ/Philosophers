/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liyu-her <liyu-her@student.42.kl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:41:21 by liyu-her          #+#    #+#             */
/*   Updated: 2025/06/12 19:49:13 by liyu-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(const char *str)
{
	if (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r')
		return (1);
	else if (*str == '\t' || *str == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	positive;
	int	negative;

	result = 0;
	positive = 0;
	negative = 0;
	while (*str && is_space(str))
		str++;
	while (*str && ((*str == '-' && !negative && !positive)
			|| (*str == '+' && !positive && !negative)))
	{
		if (*str == '-')
			negative = 1;
		if (*str == '+')
			positive = 1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
		result = (result * 10) + *str++ - '0';
	if (negative)
		return (-1 * result);
	else
		return (result);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char str[] = "-+42";

	printf("%d\n",atoi(str));
	printf("%d\n",ft_atoi(str));
	return (0);
}
*/
