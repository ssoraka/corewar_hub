/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incurses_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:10:00 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:10:00 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_init_ncurses(t_all *all)
{
	initscr();
	noecho();
	curs_set(FALSE);
	if (!(all->wins = ft_create_windows()))
		ft_error_and_del_all(all, MSG_ERROR0);
	if (!has_colors())
		ft_error_and_del_all(all, MSG_ERROR2);
	start_color();
	set_color();
}

void	set_color(void)
{
	int i;
	int colour;

	init_pair(MAX_PLAYERS + 1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 2, COLOR_RED, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 3, COLOR_GREEN, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 4, COLOR_WHITE, COLOR_BLACK);
	i = 1;
	while (i <= MAX_PLAYERS)
	{
		colour = 7 - (COLOR_BLACK + i - 1) % 7;
		init_pair(i, colour, COLOR_BLACK);
		i++;
	}
}

attr_t	ft_get_colour(t_all *all, int pos)
{
	attr_t attrs;

	attrs = COLOR_PAIR(MAX_PLAYERS + 1) | A_BOLD;
	if (all->code_owner[pos])
		attrs = COLOR_PAIR(all->code_owner[pos]);
	if (all->car_station[pos])
	{
		if (!all->code_owner[pos])
			attrs = A_NORMAL;
		attrs = attrs | A_REVERSE;
	}
	else if (all->new_code[pos])
	{
		all->new_code[pos]--;
		attrs = attrs | A_BOLD;
	}
	return (attrs);
}
