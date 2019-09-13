/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar_struct.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:14:21 by ljalikak          #+#    #+#             */
/*   Updated: 2019/06/19 14:14:22 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_STRUCT_H
# define FT_COREWAR_STRUCT_H
# include "op.h"
# include <ncurses.h>

typedef struct		s_win
{
	WINDOW			*frame;
	WINDOW			*battlefield;
	WINDOW			*info;
	WINDOW			*headers;
}					t_win;

typedef struct		s_play
{
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			programm[CHAMP_MAX_SIZE];
	int				points;
	int				number;
	int				prog_size;
	struct s_play	*next;
}					t_play;

typedef struct		s_all
{
	char			memory[MEM_SIZE];
	char			code_owner[MEM_SIZE];
	char			new_code[MEM_SIZE];
	int				car_station[MEM_SIZE];
	int				cycle_to_die;
	int				cycle;
	int				total_cycle;
	int				last_live_player;
	int				players_count;
	int				cars_count;
	int				last_car_number;
	int				visualisation;
	int				pause;
	int				delay;
	int				flag_aff;
	int				flag_dumb;
	int				dumb_cycle;
	int				nbr_live;
	int				nbr_check;
	struct s_win	*wins;
	struct s_play	*players;
	struct s_play	*player[MAX_PLAYERS + 2];
	struct s_car	*cars;
}					t_all;

typedef struct		s_car
{
	int				pos;
	int				pos_shift;
	int				reg[REG_NUMBER + 1];
	int				action;
	int				arg_byte;
	int				wait;
	int				carry;
	int				cycle_of_calling_life;
	int				num;
	int				*arg[3];
	struct s_all	*all;
	struct s_car	*prev;
	struct s_car	*next;
}					t_car;

#endif
