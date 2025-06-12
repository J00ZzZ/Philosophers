/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liyu-her <liyu-her@student.42.kl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:47:09 by liyu-her          #+#    #+#             */
/*   Updated: 2025/06/12 19:47:27 by liyu-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mod_usleep(int time, t_param *ptr)
{
	int	i;
	int	j;

	i = timestamp(ptr);
	j = 0;
	while (j < time)
	{
		j = timestamp(ptr) - i;
		usleep(50);
	}
}

void	destroy_mutex(t_param *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->philo_no)
		pthread_mutex_destroy(&ptr->fork[i++]);
	pthread_mutex_destroy(&ptr->init_lock);
	pthread_mutex_destroy(&ptr->eat_die);
	pthread_mutex_destroy(&ptr->write);
}

void	*start_philo(void *arg)
{
	t_param	*ptr;
	t_philo	philo;

	ptr = (t_param *)arg;
	init_philo(ptr, &philo);
	ptr->philo[philo.philo_no - 1] = &philo;
	while (!ptr->any_died)
	{
		if (ptr->num_fully_ate == ptr->philo_no)
			break ;
		eat(ptr, &philo);
		philo_sleep(ptr, &philo);
		think(ptr, &philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_param	ptr;
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (!init(&ptr, argc, argv))
		{
			printf(E_INIT);
			return (EXIT_SUCCESS);
		}
		if (ft_atoi(argv[1]) == 1)
		{
			printf("%d %d died\n", ft_atoi(argv[2]), 1);
			return (EXIT_SUCCESS);
		}
		while (i < ft_atoi(argv[1]))
			pthread_create(&ptr.thread[i++], NULL, start_philo, &ptr);
		check_died(&ptr);
		thread_join(&ptr, argv);
		destroy_mutex(&ptr);
	}
	else
		printf(E_PAR);
	return (EXIT_SUCCESS);
}
