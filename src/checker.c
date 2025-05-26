/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:43:20 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/26 19:51:24 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// int	check_if_died(t_sim *sim, t_philo *philo, int i, long time_last_meal)
// {
// 	if (time_last_meal > sim->time_to_die)
// 	{
// 		pthread_mutex_lock(&sim->log_mutex);
// 		printf("%d %d died\n", (int)(get_current_time()
// 				- sim->start_time), philo[i].id);
// 		pthread_mutex_unlock(&sim->log_mutex);
// 		pthread_mutex_lock(&sim->alive_mutex);
// 		sim->all_alive = 0;
// 		pthread_mutex_unlock(&sim->alive_mutex);
// 		pthread_mutex_unlock(&philo[i].state_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_all_ate(t_sim *sim, int all_ate)
// {
// 	if (sim->meals_required != -1 && all_ate)
// 	{
// 		pthread_mutex_lock(&sim->log_mutex);
// 		printf("All philosophers have eaten required meals\n");
// 		pthread_mutex_unlock(&sim->log_mutex);
// 		pthread_mutex_lock(&sim->alive_mutex);
// 		sim->all_alive = 0;
// 		pthread_mutex_unlock(&sim->alive_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// int	philos_checker(t_sim *sim, t_philo *philo)
// {
// 	int		i;
// 	int		all_ate;
// 	long	time_since_last_meal;

// 	all_ate = 1;
// 	i = -1;
// 	while (++i < sim->philos_count)
// 	{
// 		pthread_mutex_lock(&philo[i].state_mutex);
// 		time_since_last_meal = get_current_time() - philo[i].last_meal_time;
// 		if (check_if_died(sim, philo, i, time_since_last_meal))
// 			return (1);
// 		if (sim->meals_required != -1
// 			&& philo[i].meals_eaten < sim->meals_required)
// 			all_ate = 0;
// 		pthread_mutex_unlock(&philo[i].state_mutex);
// 	}
// 	if (check_all_ate(sim, all_ate))
// 		return (1);
// 	usleep(100);
// 	return (0);
// }


// void	*checker(void *arg)
// {
// 	t_sim	*sim;
// 	t_philo	*philo;

// 	sim = (t_sim *)arg;
// 	philo = sim->philos;
// 	while (1)
// 	{
// 		if (philos_checker(sim, philo))
// 			return (NULL);
// 	}
// 	return (NULL);
// }


int	check_if_died(t_sim *sim, t_philo *philo, int i, long time_last_meal)
{
	if (time_last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->log_mutex);
		printf("%d %d died\n",
			(int)(get_current_time() - sim->start_time),
			philo[i].id);
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

int	philos_checker(t_sim *sim, t_philo *philo)
{
	int		i;
	int		all_ate;
	long	time_since_last_meal;

	all_ate = 1;
	i = -1;
	while (++i < sim->philos_count)
	{
		pthread_mutex_lock(&philo[i].state_mutex);

		time_since_last_meal = get_current_time() - philo[i].last_meal_time;
		if (check_if_died(sim, philo, i, time_since_last_meal))
			return (1);

		if (sim->meals_required != -1 &&
			philo[i].meals_eaten < sim->meals_required)
			all_ate = 0;

		pthread_mutex_unlock(&philo[i].state_mutex);
	}
	if (check_all_ate(sim, all_ate))
		return (1);

	usleep(100);
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
			break ;
	}
	return (NULL);
}
