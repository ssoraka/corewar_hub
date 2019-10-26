/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:13:40 by ssoraka           #+#    #+#             */
/*   Updated: 2019/08/25 17:13:40 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

int		g_arg_tab[17][10] =
{
	{CMD_NAME, ARG_COUNT, ARG_BYTE, ARG_1, ARG_2, ARG_3},
	{CMD_LIVE, 1, 0, 0, 0, 0},
	{CMD_LD, 2, 1, T_DIR_IND, T_REG, 0},
	{CMD_ST, 2, 1, T_REG, T_REG_IND, 0},
	{CMD_ADD, 3, 1, T_REG, T_REG, T_REG},
	{CMD_SUB, 3, 1, T_REG, T_REG, T_REG},
	{CMD_AND, 3, 1, T_REG_DIR_IND, T_REG_DIR_IND, T_REG},
	{CMD_OR, 3, 1, T_REG_DIR_IND, T_REG_DIR_IND, T_REG},
	{CMD_XOR, 3, 1, T_REG_DIR_IND, T_REG_DIR_IND, T_REG},
	{CMD_ZJMP, 1, 0, T_DIR, 0, 0},
	{CMD_LDI, 3, 1, T_REG_DIR_IND, T_REG_DIR, T_REG},
	{CMD_STI, 3, 1, T_REG, T_REG_DIR_IND, T_REG_DIR},
	{CMD_FORK, 1, 0, T_DIR, 0, 0},
	{CMD_LLD, 2, 1, T_DIR_IND, T_REG, 0},
	{CMD_LLDI, 3, 1, T_REG_DIR_IND, T_REG_DIR, T_REG},
	{CMD_LFORK, 1, 0, T_DIR, 0, 0},
	{CMD_AFF, 1, 1, T_REG, 0, 0}
};

int		g_opt_tab[17][6] =
{
	{CMD_NAME, CMD_PRICE, CARRY_ONE, CARRY_NULL, SIZE_DIR},
	{CMD_LIVE, 10, 0, 0, 4},
	{CMD_LD, 5, 1, 0, 4},
	{CMD_ST, 5, 0, 0, 4},
	{CMD_ADD, 10, 1, 0, 4},
	{CMD_SUB, 10, 1, 0, 4},
	{CMD_AND, 6, 1, 0, 4},
	{CMD_OR, 6, 1, 0, 4},
	{CMD_XOR, 6, 1, 0, 4},
	{CMD_ZJMP, 20, 0, 1, 2},
	{CMD_LDI, 25, 0, 1, 2},
	{CMD_STI, 25, 0, 1, 2},
	{CMD_FORK, 800, 0, 1, 2},
	{CMD_LLD, 10, 1, 0, 4},
	{CMD_LLDI, 50, 1, 1, 2},
	{CMD_LFORK, 1000, 0, 1, 2},
	{CMD_AFF, 2, 0, 0, 4}
};

int		g_opt_tab2[4][10] =
{
	{0, MASKS},
	{REG_CODE, T_REG},
	{DIR_CODE, T_DIR},
	{IND_CODE, T_IND}
};

void	ft_wait_or_do_command(t_car *car)
{
	int arg[3];

	if (car->wait)
		(car->wait)--;
	else
	{
		ft_bzero((void *)arg, 3 * 4);
		car->arg[0] = &(arg[0]);
		car->arg[1] = &(arg[1]);
		car->arg[2] = &(arg[2]);
		car->pos_shift = 0;
		if (ft_valid_command(car))
		{
			ft_arifm_operations(car, car->arg);
			ft_st_sti_lldi_ldi_cmd(car, car->arg);
			ft_modify_carry(car, car->arg);
		}
		car->pos = ft_get_pos_of_memory(car->pos + ONE_STEP + car->pos_shift);
		car->action = READY_TO_ACTION;
	}
}

void	ft_choose_action(t_car *car)
{
	unsigned char command;

	command = *(car->all->memory + car->pos);
	if (command > 0 && command < CMD_COUNT)
	{
		car->wait = g_opt_tab[command][CMD_PRICE] - 1;
		car->action = command;
	}
	else
		car->action = MOVE_NEXT;
}

void	ft_check_of_cars(t_all *all)
{
	t_car	*car;
	t_car	*tmp;
	int		cycles;

	car = all->cars;
	while (car)
	{
		tmp = car;
		cycles = all->total_cycle - car->cycle_of_calling_life;
		car = car->next;
		if (cycles >= all->cycle_to_die || all->cycle_to_die <= 0)
			ft_del_car(all, tmp);
	}
	(all->nbr_check)++;
	if (all->nbr_live >= NBR_LIVE || all->nbr_check >= MAX_CHECKS)
	{
		all->nbr_check = 0;
		all->cycle_to_die -= CYCLE_DELTA;
	}
	all->nbr_live = 0;
	all->cycle = 0;
}

void	ft_cycle(t_all *all)
{
	t_car *car;

	(all->cycle)++;
	(all->total_cycle)++;
	ft_bzero((void *)(all->car_station), (MEM_SIZE + MEM_SIZE + MEM_SIZE +
		MEM_SIZE));
	car = all->cars;
	while (car)
	{
		if (car->action == READY_TO_ACTION)
			ft_choose_action(car);
		if (car->action == MOVE_NEXT)
		{
			car->pos = ft_get_pos_of_memory(car->pos + ONE_STEP);
			car->action = READY_TO_ACTION;
		}
		else
			ft_wait_or_do_command(car);
		(all->car_station[car->pos])++;
		car = car->next;
	}
	if (all->cars && all->cycle >= all->cycle_to_die)
		ft_check_of_cars(all);
}

int		main(int argc, char **argv)
{
	t_all *all;

	all = ft_create_all(0);
	ft_create_and_place_players(all, argc, argv);
	ft_place_prog_and_cars(all);
	if (all->visualisation)
		ft_init_ncurses(all);
	else
		ft_print_champ(all);
	if (all->flag_dumb && all->dumb_cycle == 0)
		ft_print_dump(all);
	while (all->cars || all->pause > 0)
	{
		if (!all->pause || (all->pause > 1 && (all->pause)--))
			ft_cycle(all);
		if (all->flag_dumb && all->dumb_cycle == all->total_cycle)
			ft_print_dump(all);
		if (all->visualisation)
			ft_refresh_windows(all);
	}
	if (!all->visualisation)
		ft_print_winner(all);
	ft_error_and_del_all(all, NULL);
	return (0);
}
