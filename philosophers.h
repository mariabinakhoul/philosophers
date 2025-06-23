/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:45:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/23 18:42:34 by mabi-nak         ###   ########.fr       */
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
	long			last_meal_time; //last meal time stamp
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_mutex; //mutex to protect philosopher state
	pthread_t		thread; //philosopher's thread
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
	long			start_time; //simulation start time
	pthread_mutex_t	*forks; //array of fork mutexes
	pthread_mutex_t	log_mutex; //mutex for logging access
	pthread_mutex_t	alive_mutex;
	t_philo			*philos; //array of philosopher structs
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
void	release_forks(t_philo *philo);
void	join_philosopher_threads(t_sim *sim, t_philo *philos);

#endif