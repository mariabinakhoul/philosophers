/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:20:24 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/26 13:40:33 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	mutex_init(t_sim *sim, int i)
{
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
	{
		printf("log mutex initialization failed\n");
		cleanup_sim(sim, i);
	}
	if (pthread_mutex_init(&sim->alive_mutex, NULL) != 0)
	{
		printf("alive mutex initialization failed\n");
		pthread_mutex_destroy(&sim->log_mutex);
		i = 0;
		cleanup_sim(sim, i);
	}
}

void	init_sim(t_sim *sim, char **argv)
{
	int	i;

	sim->philos_count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->meals_required = ft_atoi(argv[5]);
	else
		sim->meals_required = -1;
	sim->all_alive = 1;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philos_count);
	i = -1;
	while (++i < sim->philos_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Error initializing mutex for fork %d\n", i);
			cleanup_sim(sim, i);
		}
	}
	mutex_init(sim, i);
}

void	init_philos(t_sim *sim, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < sim->philos_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &sim->forks[i];
		philos[i].right_fork = &sim->forks[(i + 1) % sim->philos_count];
		philos[i].sim = sim;
		if (pthread_mutex_init(&philos[i].state_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&philos[--i].state_mutex);
			free(philos);
			return ;
		}
		i++;
	}
}

void	init_all(char **argv)
{
	t_philo		*philos;
	t_sim		*simulation;

	simulation = malloc(sizeof(t_sim));
	init_sim(simulation, argv);
	philos = malloc(sizeof(t_philo) * simulation->philos_count);
	if (!philos)
		return ;
	init_philos(simulation, philos);
	simulation->philos = philos;
	simulation->start_time = get_current_time();
	if (simulation->philos_count == 1)
	{
		print_philo_status(&philos[0], "has taken a fork");
		precise_sleep(simulation->time_to_die);
		print_philo_status(&philos[0], "died");
		free_resources(simulation, philos);
		exit(0);
	}
	start_simulation(simulation, philos);
	join_philosopher_threads(simulation, philos);
}
