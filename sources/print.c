/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:09:33 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:09:34 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

char	g_man[8][100] =
{
	"#### EXSAMPLE #########################################################\n",
	"	./corewar [-a][-dump N][-vis] [[-n number] champion1.cor] ...\n",
	"#### HELP #############################################################\n",
	"	-a        : Prints output from \"aff\" (Default is to hide it)\n",
	"	-dump N   : Dumps memory after N cycles then exits\n",
	"	-vis      : Ncurses output mode\n",
	"	-n number : Sets the number of the next player\n",
	"#######################################################################\n"
};

void	ft_print_dump(t_all *all, char *memory)
{
	int				i;
	unsigned char	byte;
	char			*num;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % DUMP_LENGTH))
		{
			ft_putstr("0x");
			num = (char *)(&i);
			ft_print_byte((unsigned int)(unsigned char)num[1]);
			ft_print_byte((unsigned int)(unsigned char)num[0]);
			ft_putstr(" : ");
		}
		byte = (unsigned char)(*(memory + i));
		ft_print_byte((unsigned int)byte);
		if ((i + 1) % DUMP_LENGTH)
			ft_putchar(' ');
		else
			ft_putstr(" \n");
		i++;
	}
}

void	ft_print_byte(unsigned int byte)
{
	unsigned int four_bits;

	four_bits = byte / 16;
	if (four_bits < 10)
		ft_putnbr(four_bits);
	else
		ft_putchar((four_bits + 'a' - 10));
	four_bits = byte % 16;
	if (four_bits < 10)
		ft_putnbr(four_bits);
	else
		ft_putchar(four_bits + 'a' - 10);
}

void	ft_print_champ(t_all *all)
{
	int i;

	i = 1;
	ft_putstr("Introducing contestants...\n");
	while (i <= MAX_PLAYERS)
	{
		if (all->player[i])
		{
			ft_putstr("* Player ");
			ft_putnbr(i);
			ft_putstr(", weighing ");
			ft_putnbr(all->player[i]->prog_size);
			ft_putstr(" bytes, \"");
			ft_putstr(all->player[i]->prog_name);
			ft_putstr("\" (\"");
			ft_putstr(all->player[i]->comment);
			ft_putstr("\") !\n");
		}
		i++;
	}
}

void	ft_print_winner(t_all *all)
{
	t_play	*play;

	play = all->player[all->last_live_player];
	ft_putstr("Contestant ");
	ft_putnbr(play->number);
	ft_putstr(", \"");
	ft_putstr(play->prog_name);
	ft_putstr("\", has won !\n");
}

void	ft_print_manual(void)
{
	int i;

	i = 0;
	while (i < 8)
	{
		ft_putstr(g_man[i]);
		i++;
	}
}
