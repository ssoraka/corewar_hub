/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:07:39 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:07:39 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_arifm_operations(t_car *car, int **arg)
{
	if (car->action == CMD_AND)
		*(arg[2]) = *(arg[0]) & *(arg[1]);
	else if (car->action == CMD_OR)
		*(arg[2]) = *(arg[0]) | *(arg[1]);
	else if (car->action == CMD_XOR)
		*(arg[2]) = *(arg[0]) ^ *(arg[1]);
	else if (car->action == CMD_ADD)
		*(arg[2]) = *(arg[0]) + *(arg[1]);
	else if (car->action == CMD_SUB)
		*(arg[2]) = *(arg[0]) - *(arg[1]);
	else if (car->action == CMD_LD || car->action == CMD_LLD)
		*(arg[1]) = *(arg[0]);
	else if (car->action == CMD_ZJMP && car->carry)
		car->pos_shift = *(arg[0]) % IDX_MOD - ONE_STEP;
	else if (car->action == CMD_FORK || car->action == CMD_LFORK)
		ft_copy_fork(car, *(arg[0]));
	else if (car->action == CMD_LIVE)
		ft_live(car, *(arg[0]));
	else if (car->action == CMD_AFF && car->all->flag_aff)
		ft_putchar((char)*(arg[0]));
}

void	ft_st_sti_lldi_ldi_cmd(t_car *car, int **arg)
{
	int adress;

	adress = 0;
	if (car->action == CMD_ST)
	{
		if (arg[1] > car->reg && arg[1] <= car->reg + REG_NUMBER)
			*(arg[1]) = *(arg[0]);
		else
		{
			adress = car->pos + (*arg[1]) % IDX_MOD;
			ft_value_in_memory(car, adress, *(arg[0]), DIR_SIZE);
		}
	}
	else if (car->action == CMD_STI)
	{
		adress = car->pos + (*(arg[1]) + *(arg[2])) % IDX_MOD;
		ft_value_in_memory(car, adress, *(arg[0]), DIR_SIZE);
	}
	else if (car->action == CMD_LLDI || car->action == CMD_LDI)
	{
		adress = car->pos + (*(arg[0]) + *(arg[1])) % IDX_MOD - 1;
		if (car->action == CMD_LLDI)
			adress = car->pos + *(arg[0]) + *(arg[1]) - 1;
		*(arg[2]) = ft_value_from_memory(car->all->memory, adress, DIR_SIZE);
	}
}

void	ft_copy_fork(t_car *car, int new_pos)
{
	t_car *new;

	if (car->action == CMD_FORK)
		new_pos = car->pos + new_pos % IDX_MOD;
	else if (car->action == CMD_LFORK)
		new_pos = car->pos + new_pos;
	new_pos = ft_get_pos_of_memory(new_pos);
	new = ft_create_car(-(car->reg[1]), car->all, new_pos);
	(car->all->car_station[new->pos])++;
	ft_memcpy((void *)new->reg, (void *)car->reg, 4 * (REG_NUMBER + 1));
	new->carry = car->carry;
	new->cycle_of_calling_life = car->cycle_of_calling_life;
}

void	ft_live(t_car *car, int value)
{
	t_all *all;

	all = car->all;
	value = -value;
	if (value > 0 && value <= MAX_PLAYERS && all->player[value])
	{
		(all->player[value])->points = all->total_cycle;
		all->last_live_player = value;
	}
	car->cycle_of_calling_life = all->total_cycle;
	(all->nbr_live)++;
}

void	ft_modify_carry(t_car *car, int **arg)
{
	int value;

	value = 0;
	if (!g_opt_tab[car->action][CARRY_ONE])
		return ;
	if (car->action == CMD_AND || car->action == CMD_OR ||
	car->action == CMD_XOR || car->action == CMD_ADD ||
	car->action == CMD_SUB || car->action == CMD_LLDI)
		value = *(arg[2]);
	if (car->action == CMD_LD || car->action == CMD_LLD)
		value = *(arg[1]);
	if (value)
		car->carry = 0;
	else
		car->carry = 1;
}
