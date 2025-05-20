/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:43:20 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/20 19:57:38 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_if_died(t_sim *sim, t_philo *philo, int i, long time_last_meal)
{
	if (time_last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->log_mutex);
		printf("%d %d died\n", (int)(get_current_time()
				- sim->start_time), philo[i].id);
		pthread_mutex_unlock(&sim->log_mutex);
		pthread_mutex_lock(&sim->alive_mutex);
		sim->all_alive = 0;
		pthread_mutex_unlock(&sim->alive_mutex);
		pthread_mutex_unlock(&philo[i].state_mutex);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_sim *sim, int all_ate)
{
	if (sim->meals_required != -1 && all_ate)
	{
		pthread_mutex_lock(&sim->log_mutex);
		printf("All philosophers have eaten required meals\n");
		pthread_mutex_unlock(&sim->log_mutex);
		pthread_mutex_lock(&sim->alive_mutex);
		sim->all_alive = 0;
		pthread_mutex_unlock(&sim->alive_mutex);
		return (1);
	}
	return (0);
}



void	*checker(void *arg)
{
	t_sim	*sim;
	t_philo	*philo;

	sim = (t_sim *)arg;
	philo = sim->philos;
	while (1)
	{
		if (philos_checker(sim, philo))
			return (NULL);
	}
	return (NULL);
}
