/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:12 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 17:05:11 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	start_routine(t_philo *philo)
{
	print_philo_status(philo, "is thinking");
	precise_sleep(9);
	take_forks(philo);
	eat(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_philo_status(philo, "is sleeping");
	precise_sleep(philo->sim->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		all_alive;
	int		meals_eaten;

	philo = (t_philo *)arg;
	sim = philo->sim;
	while (1)
	{
		pthread_mutex_lock(&sim->alive_mutex);
		all_alive = sim->all_alive;
		pthread_mutex_unlock(&sim->alive_mutex);
		if (!all_alive)
			break ;
		start_routine(philo);
		pthread_mutex_lock(&philo->state_mutex);
		meals_eaten = philo->meals_eaten;
		pthread_mutex_unlock(&philo->state_mutex);
		if (sim->meals_required != -1 && meals_eaten >= sim->meals_required)
			break ;
	}
	return (NULL);
}
