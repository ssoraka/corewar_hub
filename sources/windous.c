/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windous.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:09:49 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:09:49 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

t_win	*ft_create_windows(void)
{
	t_win *wins;

	wins = (t_win *)ft_memalloc(sizeof(t_win));
	if (!wins)
		return (NULL);
	wins->frame = newwin(FRAME_H, FRAME_L, 0, 0);
	wins->battlefield = subwin(wins->frame, BATTLEFIELD_H, BATTLEFIELD_L,
		BATTLEFIELD_Y, BATTLEFIELD_X);
	wins->info = subwin(wins->frame, INFO_H, INFO_L, INFO_Y, INFO_X);
	keypad(wins->frame, TRUE);
	nodelay(wins->frame, TRUE);
	return (wins);
}

void	ft_destroy_windows(t_win *wins)
{
	delwin(wins->battlefield);
	delwin(wins->info);
	delwin(wins->frame);
	endwin();
}

void	ft_refresh_windows(t_all *all)
{
	ft_key_control(all);
	ft_print_frame(all->wins->frame);
	ft_print_info(all);
	ft_print_bonus(all);
	ft_print_battlefield(all);
	wrefresh(all->wins->frame);
	usleep(all->delay);
}

void	ft_key_control(t_all *all)
{
	int		button;

	if (!all->cars)
		all->pause = TRUE;
	button = wgetch(all->wins->frame);
	if (button == '+' && all->delay > 4)
		all->delay /= 2;
	if (button == '-' && all->delay < 0x8FFF)
		all->delay *= 2;
	if (button == 'p')
		all->pause = !(all->pause);
	if (button == 'q')
		ft_error_and_del_all(all, NULL);
}
