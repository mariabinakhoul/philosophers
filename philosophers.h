/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:45:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/26 13:12:30 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex;
	pthread_t		thread;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				all_alive;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	alive_mutex;
	t_philo			*philos;
}	t_sim;

int		ft_atoi(const char *str);
int		validate_args(int argc, char **argv);
long	get_current_time(void);
void	cleanup_sim(t_sim *sim, int i);
void	precise_sleep(long duration_ms);
void	print_philo_status(t_philo *philo, const char *status);
void	free_resources(t_sim *sim, t_philo *philos);
void	init_all(char **argv);
void	*checker(void *arg);
int		philos_checker(t_sim *sim, t_philo *philo);
int		check_all_ate(t_sim *sim, int all_ate);
int		check_if_died(t_sim *sim, t_philo *philo, int i, long time_last_meal);
void	start_simulation(t_sim *sim, t_philo *philos);
void	*philosopher_routine(void *arg);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	join_philosopher_threads(t_sim *sim, t_philo *philos);

#endif