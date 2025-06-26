/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:17:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/26 14:18:13 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	join_philosopher_threads(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->philos_count)
		pthread_join(philos[i++].thread, NULL);
	free_resources(sim, philos);
}

void	start_simulation(t_sim *sim, t_philo *philos)
{
	int			i;
	pthread_t	monitor_thread;

	sim->start_time = get_current_time();
	i = -1;
	while (++i < sim->philos_count)
		philos[i].last_meal_time = sim->start_time;
	i = -1;
	while (++i < sim->philos_count)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			printf("Error creating threads");
			exit(1);
		}
		usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, checker, (void *)sim) != 0)
	{
		printf("Error creating threads");
		exit(1);
	}
	pthread_join(monitor_thread, NULL);
}
