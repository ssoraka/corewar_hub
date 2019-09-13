/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_for_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:07:51 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:07:52 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

/*
**	проверяет валидность команды,
*/

int		ft_valid_command(t_car *car)
{
	int valid;

	valid = TRUE;
	if ((g_arg_tab[car->action][ARG_BYTE]))
	{
		car->pos_shift = ONE_STEP;
		if (ft_parsing_of_args(car) == FAIL)
			valid = FALSE;
	}
	else
	{
		ft_return_arg(car, DIR_CODE, &(car->arg[0]));
		car->pos_shift = g_opt_tab[car->action][SIZE_DIR];
	}
	return (valid);
}

/*
**	парсит команду на аргументы
*/

int		ft_parsing_of_args(t_car *car)
{
	int args_byte;
	int arg_bits;
	int valid;
	int i;

	valid = SUCCESS;
	args_byte = ft_value_from_memory(car->all->memory, car->pos, 1);
	i = 0;
	while (i < 4)
	{
		arg_bits = (args_byte >> (2 * (3 - i))) & ARG_MASK;
		car->arg_byte = car->arg_byte << 8;
		if (i < g_arg_tab[car->action][ARG_COUNT])
		{
			if (ft_arg_is_valid(car, arg_bits, i) == FALSE)
				valid = FAIL;
			ft_return_arg(car, arg_bits, &(car->arg[i]));
			car->pos_shift += ft_size_of_arg_by_type(car->action, arg_bits);
			car->arg_byte = car->arg_byte | g_opt_tab2[arg_bits][1];
		}
		i++;
	}
	return (valid);
}

/*
**	проверяет валидность одного аргумента
*/

int		ft_arg_is_valid(t_car *car, int arg_bits, int arg_number)
{
	int valid;
	int reg;
	int arg_type;
	int cmd_arg_mask;

	valid = FALSE;
	arg_type = g_opt_tab2[arg_bits][1];
	cmd_arg_mask = g_arg_tab[car->action][ARG_1 + arg_number];
	if (arg_type & cmd_arg_mask)
		valid = TRUE;
	if (valid && arg_bits == REG_CODE)
	{
		reg = ft_value_from_memory(car->all->memory, car->pos +
			car->pos_shift, 1);
		if (reg > REG_NUMBER || reg <= 0)
			valid = FALSE;
	}
	return (valid);
}

/*
**	хитрая функция: вставляет в переменную на стеке значения DIR или IND,
**	в случае с регистром подменяет указатель на сам регистр
*/

void	ft_return_arg(t_car *car, int arg_bits, int **arg)
{
	int address;
	int size;

	address = car->pos + car->pos_shift;
	size = ft_size_of_arg_by_type(car->action, arg_bits);
	**arg = ft_value_from_memory(car->all->memory, address, size);
	if (arg_bits == REG_CODE)
		*arg = &(car->reg[**arg]);
	else if (arg_bits == IND_CODE)
	{
		if (car->action == CMD_LLD || car->action == CMD_LLDI)
			address = car->pos + (**arg) - 1;
		else
			address = car->pos + (**arg) % IDX_MOD - 1;
		if (car->action != CMD_ST)
			**arg = ft_value_from_memory(car->all->memory, address, DIR_SIZE);
	}
}

int		ft_size_of_arg_by_type(int command, int arg_bit)
{
	int length;

	length = 0;
	if (arg_bit == REG_CODE)
		length = 1;
	else if (arg_bit == DIR_CODE)
		length = g_opt_tab[command][SIZE_DIR];
	else if (arg_bit == IND_CODE)
		length = 2;
	return (length);
}
