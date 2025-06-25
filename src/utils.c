/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:46:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 17:04:27 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup_sim(t_sim *sim, int i)
{
	while (i > 0)
		pthread_mutex_destroy(&sim->forks[--i]);
	free(sim->forks);
}

void	precise_sleep(long duration_ms)
{
	long	start;
	long	current;

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if ((current - start) >= duration_ms)
			break ;
		usleep(500);
	}
}


void	print_philo_status(t_philo *philo, const char *status)
{
	int	is_alive;

	pthread_mutex_lock(&philo->sim->alive_mutex);
	is_alive = philo->sim->all_alive;
	pthread_mutex_unlock(&philo->sim->alive_mutex);
	if (!is_alive)
		return ;
	pthread_mutex_lock(&philo->sim->log_mutex);
	printf("%ld %d %s\n", get_current_time() - philo->sim->start_time,
		philo->id, status);
	pthread_mutex_unlock(&philo->sim->log_mutex);
}

void	free_resources(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->philos_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->alive_mutex);
	free(sim->forks);
	free(philos);
	free(sim);
}
