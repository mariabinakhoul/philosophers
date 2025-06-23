/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:17:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/23 18:43:54 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	handle_thread_creating_error(t_sim *sim,
	t_philo *philos, int index)
{
	printf("Error creating thread for philosophers %d\n", index);
	free_resources(sim, philos);
	exit(EXIT_FAILURE);
}

void	join_philosopher_threads(t_sim *sim, t_philo *philos)
{
	int	i;

	while (i < sim->philos_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free_resources(sim, philos);
}

void	start_simulation(t_sim *sim, t_philo *philos)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	sim->start_time = get_current_time();
	while (i < sim->philos_count)
		philos[i++].last_meal_time = sim->start_time;
	i = 0;
	while (i < sim->philos_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]) != 0)
			handle_thread_creating_error(sim, philos, i);
		usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, checker, (void *)sim) != 0)
	{
		printf("Error creating monitor thread\n");
		free_resources(sim, philos);
		exit(EXIT_FAILURE);
	}
	pthread_join(monitor_thread, NULL);
	join_philosopher_threads(sim, philos);
}
