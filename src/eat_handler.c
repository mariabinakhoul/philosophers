/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:29:18 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 17:14:59 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_philo_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_philo_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	print_philo_status(philo, "is eating");
	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_mutex);
	precise_sleep(philo->sim->time_to_eat);
}
