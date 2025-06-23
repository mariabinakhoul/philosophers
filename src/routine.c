/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:12 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/23 18:16:34 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	start_routine(t_philo *philo)
{
	take_forks(philo);

	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->state_mutex);
	print_philo_status(philo, "is eating");
	precise_sleep(philo->sim->time_to_eat);
	release_forks(philo);
	print_philo_status(philo, "is sleeping");
	precise_sleep(philo->sim->time_to_sleep);
	print_philo_status(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if ((philo->id % 2) == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&sim->alive_mutex);
		if (!sim->all_alive)
		{
			pthread_mutex_unlock(&sim->alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->alive_mutex);
		start_routine(philo);
		pthread_mutex_lock(&philo->state_mutex);
		if (sim->meals_required != -1
			&& philo->meals_eaten >= sim->meals_required)
		{
			pthread_mutex_unlock(&philo->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->state_mutex);
	}
	return (NULL);
}
