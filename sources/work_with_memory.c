/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:07:23 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:07:23 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

/*
**	корректировка индекса массива памяти
*/

int		ft_get_pos_of_memory(int pos)
{
	if (pos >= MEM_SIZE)
		pos = pos % MEM_SIZE;
	if (pos < -MEM_SIZE)
		pos = (pos + 1) % MEM_SIZE - 1;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

/*
**	возвращаем число на указанное количество байт из памяти
*/

int		ft_value_from_memory(char *memory, int pos, int size)
{
	int		value;
	int		i;
	char	*byte;

	i = 0;
	value = 0;
	byte = (char *)(&value);
	while (i < size)
	{
		byte[i] = *(memory + ft_get_pos_of_memory(pos + size - i));
		i++;
	}
	if (size == IND_SIZE && (value & 0x8000))
		value = value + 0xFFFF0000;
	return (value);
}

/*
**	вписываем число на указанное количество байт в память
*/

void	ft_value_in_memory(t_car *car, int pos, int value, int size)
{
	int		i;
	int		mem_pos;
	char	*byte;
	char	*memory;
	char	*cod_owner;

	i = 0;
	memory = car->all->memory;
	cod_owner = car->all->code_owner;
	byte = (char *)(&value);
	while (i < size)
	{
		mem_pos = ft_get_pos_of_memory(pos + size - i - 1);
		*(memory + mem_pos) = byte[i];
		if (-car->reg[1] > 0 && -car->reg[1] <= MEM_SIZE &&
		car->all->player[-car->reg[1]])
		{
			*(cod_owner + mem_pos) = -car->reg[1];
			*(car->all->new_code + mem_pos) = DELAY_BOLD;
		}
		i++;
	}
}

int		ft_read_memory(t_all *all, char **argv, int argc)
{
	int i;
	int number;
	int flag;

	flag = 0;
	number = 0;
	i = 0;
	while (i < argc && all->players_count < MAX_PLAYERS)
	{
		if (!ft_strcmp(argv[i], "-n"))
			flag = 1;
		else if (flag && !ft_str_not_int_number(argv[i]) &&
		ft_atoi(argv[i]) > 0 && ft_atoi(argv[i]) <= MAX_PLAYERS &&
		(flag = 0) == 0)
			number = ft_atoi(argv[i]);
		else if (ft_read_player(all, argv[i], number) == SUCCESS)
		{
			flag = 0;
			number = 0;
		}
		else
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int		ft_read_player(t_all *all, char *name, int number)
{
	char	buf[MAX_CODE + 1];
	int		fd;
	int		reader;
	int		valid;

	valid = FAIL;
	fd = open(name, O_RDONLY);
	if (ft_strlen(name) <= 4 || ft_strcmp(name + ft_strlen(name) - 4, ".cor"))
		return (valid);
	if ((fd = open(name, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		return (valid);
	reader = read(fd, buf, MAX_CODE + 1);
	close(fd);
	if (ft_check_errors(all, buf, reader) && ft_add_player(all, buf, number))
		valid = SUCCESS;
	return (valid);
}
