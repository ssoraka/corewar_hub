/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_del_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:07:05 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:07:06 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_error_and_del_all(t_all *all, char *error_msg)
{
	t_play *play;

	play = NULL;
	if (error_msg && !ft_strcmp(error_msg, MANUAL))
		ft_print_manual();
	else if (error_msg)
		ft_putstr(error_msg);
	while (all && all->cars)
		ft_del_car(all, all->cars);
	while (all && all->players)
	{
		play = all->players;
		all->players = all->players->next;
		free(play);
	}
	if (all->wins)
		ft_destroy_windows(all->wins);
	free(all->wins);
	free(all);
	exit(0);
}

t_all	*ft_create_all(int players_count)
{
	t_all *tmp;

	tmp = (t_all *)ft_memalloc(sizeof(t_all));
	if (!tmp)
		ft_error_and_del_all(NULL, MSG_ERROR0);
	tmp->cycle_to_die = CYCLE_TO_DIE;
	tmp->players_count = players_count;
	tmp->delay = DELAY;
	return (tmp);
}

t_car	*ft_create_car(int player_num, t_all *all, int pos)
{
	t_car *tmp;

	tmp = (t_car *)ft_memalloc(sizeof(t_car));
	if (!tmp)
		ft_error_and_del_all(all, MSG_ERROR0);
	tmp->reg[1] = -player_num;
	tmp->all = all;
	if (all->cars)
		all->cars->prev = tmp;
	tmp->next = all->cars;
	all->cars = tmp;
	(all->last_car_number)++;
	(all->cars_count)++;
	tmp->num = all->last_car_number;
	tmp->pos = pos;
	tmp->action = READY_TO_ACTION;
	return (tmp);
}

void	ft_del_car(t_all *all, t_car *car)
{
	t_car *tmp;

	if (!car || !all || !all->cars)
		return ;
	(all->cars_count)--;
	(all->car_station[car->pos])--;
	if (all->cars == car)
	{
		all->cars = car->next;
		if (all->cars)
			all->cars->prev = NULL;
	}
	else
	{
		tmp = car->prev;
		tmp->next = car->next;
		if (car->next)
			tmp->next->prev = tmp;
	}
	ft_memdel((void **)(&car));
}
