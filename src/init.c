/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:20:24 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/20 20:14:43 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_sim(t_sim *sim, char **argv)
{
	int	i;

	i = -1;
	sim->philos_count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->meals_required = ft_atoi(argv[5]);
	else
		sim->meals_required = -1;
	sim->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * sim->philos_count);
	while (++i < sim->philos_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Mutex init failed for fork\n");
			cleanup_sim(sim, i);
			exit (1);
		}
	}
	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->philos_count);
	sim->start_time = get_current_time();
	pthread_mutex_init(&sim->log_mutex, NULL);
}

static void	init_philos(t_philo *philos, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->philos_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &sim->forks[i];
		philos[i].right_fork = &sim->forks[(i + 1) % sim->philos_count];
		philos[i].last_meal_time = sim->start_time;
		pthread_mutex_init(&philos[i].state_mutex, NULL);
		philos[i].thread = 0;
		i++;
	}
}

void	init_all(char **argv)
{
	t_philo	*philos;
	t_sim	*sim;

	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
	{
		printf("Failed to allocate memory for simulation\n");
		return ;
	}
	init_sim(sim, argv);
	philos = (t_philo *)malloc(sizeof(t_philo) * sim->philos_count);
	if (!philos)
	{
		printf("Failed to allocate memory for philosophers");
		cleanup_sim(sim, sim->philos_count);
		return ;
	}
	init_philos(philos, sim);
	sim->philos = philos;
	sim->start_time = get_current_time();
	if (sim->philos_count == 1)
	{
		log_state(&philos[0], "has taken a fork");
		accurate_sleep(sim->time_to_die);
	}
}
