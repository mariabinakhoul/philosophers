/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:47:35 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/20 23:32:59 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int) *str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

int	validate_args(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if ((ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
			|| (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
				|| ft_atoi(argv[4]) < 60) || (argc == 6
				&& ft_atoi(argv[5]) < 1))
		{
			printf("Invalid args\n");
			return (0);
		}
		return (1);
	}
	return (0);
}
