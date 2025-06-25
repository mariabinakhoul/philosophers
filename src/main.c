/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:51:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 16:03:46 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	if (validate_args(argc, argv))
		init_all(argv);
	else
	{
		printf("You need to enter these arguments ");
		printf("(the last one is not a must):\n");
		printf("number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	return (0);
}

