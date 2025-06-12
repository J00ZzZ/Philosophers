/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liyu-her <liyu-her@student.42.kl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:47:09 by liyu-her          #+#    #+#             */
/*   Updated: 2025/06/12 19:48:36 by liyu-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_fully_ate(t_param *ptr, t_philo *philo)
{
	if (philo->ate == ptr->num_to_eat)
		ptr->num_fully_ate++;
}

void	eat(t_param *ptr, t_philo *philo)
{
	int	fork_left;
	int	fork_right;

	fork_right = philo->philo_no - 1;
	if (philo->philo_no == ptr->philo_no)
		fork_left = 0;
	else
		fork_left = philo->philo_no;
	if (philo->t_last_eat == 0 && philo->philo_no % 2 == 0)
		mod_usleep(ptr->t_to_eat, ptr);
	pthread_mutex_lock(&ptr->fork[fork_left]);
	display(ptr, philo, "fork");
	pthread_mutex_lock(&ptr->fork[fork_right]);
	display(ptr, philo, "fork");
	pthread_mutex_lock(&ptr->eat_die);
	philo->t_last_eat = timestamp(ptr);
	pthread_mutex_unlock(&ptr->eat_die);
	display(ptr, philo, "eating");
	mod_usleep(ptr->t_to_eat, ptr);
	pthread_mutex_unlock(&ptr->fork[fork_right]);
	pthread_mutex_unlock(&ptr->fork[fork_left]);
}

void	philo_sleep(t_param *ptr, t_philo *philo)
{
	display(ptr, philo, "sleeping");
	mod_usleep(ptr->t_to_sleep, ptr);
}

void	think(t_param *ptr, t_philo *philo)
{
	display(ptr, philo, "thinking");
}

void	check_died(t_param *ptr)
{
	int	i;

	while (!ptr->any_died)
	{
		if (ptr->decrem_philo == 0)
		{
			if (ptr->num_to_eat != -1 && ptr->num_fully_ate == ptr->philo_no)
				break ;
			i = 0;
			while (i < ptr->philo_no)
			{
				pthread_mutex_lock(&ptr->eat_die);
				if ((timestamp(ptr) - ptr->philo[i]->t_last_eat)
					> ptr->t_to_die)
					display(ptr, ptr->philo[i], "died");
				pthread_mutex_unlock(&ptr->eat_die);
				if ((timestamp(ptr) - ptr->philo[i]->t_last_eat)
					> ptr->t_to_die)
					break ;
				i++;
			}
		}
	}
}
