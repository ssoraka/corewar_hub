/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:09:17 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:09:17 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_create_and_place_players(t_all *all, int argc, char **argv)
{
	ft_skip_flags(all, &argv, &argc);
	if (!argc)
		ft_error_and_del_all(all, MANUAL);
	if (ft_read_memory(all, argv, argc) == FAIL)
		ft_error_and_del_all(all, MSG_ERROR1);
	if (!all->players_count)
		ft_error_and_del_all(all, MSG_ERROR9);
	if (ft_arr_of_number_players(all) == FAIL)
		ft_error_and_del_all(all, MSG_ERROR3);
	ft_place_players_without_num(all);
}

t_play	*ft_add_player(t_all *all, char *buf, int number)
{
	t_play	*tmp;
	t_play	*player;

	tmp = (t_play *)ft_memalloc(sizeof(t_play));
	if (!tmp)
		return (tmp);
	buf = buf + 4;
	ft_memcpy((void *)tmp->prog_name, (void *)buf, PROG_NAME_LENGTH);
	buf = buf + PROG_NAME_LENGTH + 3;
	tmp->prog_size = ft_value_from_memory(buf, 0, 4);
	buf = buf + 5;
	ft_memcpy((void *)tmp->comment, (void *)buf, COMMENT_LENGTH);
	buf = buf + COMMENT_LENGTH + 4;
	ft_memcpy((void *)tmp->programm, (void *)buf, tmp->prog_size);
	tmp->number = number;
	(all->players_count)++;
	if (!all->players)
		return ((all->players = tmp));
	player = all->players;
	while (player->next)
		player = player->next;
	player->next = tmp;
	return (tmp);
}

void	ft_place_players_without_num(t_all *all)
{
	t_play	*tmp;
	int		i;

	tmp = all->players;
	i = 1;
	while (i <= all->players_count && tmp)
	{
		if (tmp->number != 0 || all->player[i] == tmp)
			tmp = tmp->next;
		else if (all->player[i])
			i++;
		else
		{
			all->player[i] = tmp;
			all->player[i]->number = i;
		}
	}
}

int		ft_arr_of_number_players(t_all *all)
{
	t_play	*tmp;
	int		i;

	i = 1;
	while (i < MAX_PLAYERS + 1)
	{
		tmp = all->players;
		while (tmp)
		{
			if (all->player[i] && tmp->number == i && all->player[i] != tmp)
				return (FAIL);
			if (!(all->player[i]) && tmp->number == i)
				all->player[i] = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

void	ft_place_prog_and_cars(t_all *all)
{
	int		i;
	int		pos;
	t_car	*car;
	t_play	*p;

	i = 1;
	pos = 0;
	while (i < MAX_PLAYERS + 1)
	{
		if (all->player[i])
		{
			p = all->player[i];
			car = ft_create_car(i, all, pos);
			(all->car_station[pos])++;
			ft_memcpy((void *)all->memory + pos, (void *)p->programm,
				p->prog_size);
			ft_memset((void *)all->code_owner + pos, i, p->prog_size);
			pos += MEM_SIZE / (all->players_count);
		}
		i++;
	}
	all->last_live_player = -(car->reg[1]);
}
