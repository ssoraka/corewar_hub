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

#include "libft.h"
#include "op.h"


#define ONE_STEP 1


#define MAX_CYCLE 64
#define CHECK_COMMAND 0x04
#define CHECK_ARG_BYTE 0b01010100
#define CHECK_REG1 0x00
#define CHECK_REG2 0x10
#define CHECK_REG3 0x02

#define BYTES_COUNT 16
char str[100] = {

0x09, 0x00, 0x0a,
0x01, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x00, 0x00,
0x09, 0xff, 0xf6,
0x00, 0x00
};
				/*{
				0x03,
				0b01010100,
				0x01, 0x00, 0x05, 0x07,
				0x07, 0x07, 0x07, 0x07,
				0x02,
				0x02, 0x02};*/




/*
**	сделать и организовать маски для аргументов
*/



#define ARG_MASK 0b00000011
#define REG_MASK 0b00000001
#define DIR_MASK 0b00000010
#define IND_MASK 0b00000011

typedef enum	s_com
{
	MOVE_NEXT = -1,
	READY_TO_ACTION = 0,
	CMD_LIVE = 1,
	CMD_LD,
	CMD_ST,
	CMD_ADD,
	CMD_SUB,
	CMD_AND,
	CMD_OR,
	CMD_XOR,
	CMD_ZJMP,
	CMD_LDI,
	CMD_STI,
	CMD_FORK,
	CMD_LLD,
	CMD_LLDI,
	CMD_LFORK,
	CMD_AFF,
	CMD_COUNT
}				e_com;


#define CMD_PRICE 1
#define CARRY_ONE 2
#define CARRY_NULL 3
#define SIZE_DIR 4

int    opt_tab[17][10] =
{
	{0,			CMD_PRICE, CARRY_ONE, CARRY_NULL, SIZE_DIR},
	{CMD_LIVE,	10, 0, 0, 4},
	{CMD_LD,	5, 1, 0, 4},
	{CMD_ST,	5, 1, 0, 4},
	{CMD_ADD,	10, 1, 0, 4},
	{CMD_SUB,	10, 1, 0, 4},
	{CMD_AND,	6, 1, 0, 4},
	{CMD_OR,	6, 1, 0, 4},
	{CMD_XOR,	6, 1, 0, 4},
	{CMD_ZJMP,	20, 0, 1, 2},
	{CMD_LDI,	25, 1, 1, 2},
	{CMD_STI,	25, 1, 1, 2},
	{CMD_FORK,	800, 0, 1, 2},
	{CMD_LLD,	10, 1, 0, 4},
	{CMD_LLDI,	50, 1, 1, 2},
	{CMD_LFORK,	1000, 0, 1, 2},
	{CMD_AFF,	2, 1, 0, 4}
};

#define F_REG			1
#define F_DIR			2
#define F_IND			4
#define F_REG_DIR		(F_REG + F_DIR)
#define F_REG_IND		(F_REG + F_IND)
#define F_DIR_IND		(F_DIR + F_IND)
#define F_REG_DIR_IND	(F_REG + F_DIR + F_IND)

#define ARG_COUNT	1
#define ARG_BYTE	2
#define ARG_1		3
#define ARG_2		4
#define ARG_3		5


int    arg_tab[17][10] =
{
	{0,		ARG_COUNT, ARG_BYTE, ARG_1,ARG_2,ARG_3},
	{CMD_LIVE,	1,	0,	0,				0,				0},
	{CMD_LD,	2,	1,	F_DIR_IND,		F_REG,			0},
	{CMD_ST,	2,	1,	F_REG,			F_REG_IND,		0},
	{CMD_ADD,	3,	1,	F_REG,			F_REG,			F_REG},
	{CMD_SUB,	3,	1,	F_REG,			F_REG,			F_REG},
	{CMD_AND,	3,	1,	F_REG_DIR_IND,	F_REG_DIR_IND,	F_REG},
	{CMD_OR,	3,	1,	F_REG_DIR_IND,	F_REG_DIR_IND,	F_REG},
	{CMD_XOR,	3,	1,	F_REG_DIR_IND,	F_REG_DIR_IND,	F_REG},
	{CMD_ZJMP,	1,	0,	F_DIR,			0,				0},
	{CMD_LDI,	3,	1,	F_REG_DIR_IND,	F_REG_DIR,		F_REG},
	{CMD_STI,	3,	1,	F_REG,			F_REG_DIR_IND,	F_REG_DIR},
	{CMD_FORK,	1,	0,	F_DIR,			0,				0},
	{CMD_LLD,	2,	1,	F_DIR_IND,		F_REG,			0},
	{CMD_LLDI,	3,	1,	F_REG_DIR_IND,	F_REG_DIR,		F_REG},
	{CMD_LFORK,	1,	0,	F_DIR,			0,				0},
	{CMD_AFF,	1,	1,	F_REG,			0,				0},
};



typedef struct		s_all
{
	char			memory[MEM_SIZE];
	int				cycle_to_die;
	int				cycle;
	int				total_cycle;
	int				points_of_players[MAX_PLAYERS];
	int				last_live_player;
	int				players_count;
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
	struct s_all	*all;
	struct s_car	*next;
}					t_car;



void	ft_putnbr_end(int num)
{
	ft_putnbr(num);
	ft_putchar('\n');
}

t_car	*ft_create_car(int player_num, t_all *all)
{
	t_car *tmp;

	tmp = (t_car *)ft_memalloc(sizeof(t_car));
	if (!tmp)
		return (NULL);
	tmp->reg[1] = -player_num;
	tmp->all = all;
	return (tmp);
}


t_all	*ft_create_all(int players_count)
{
	t_all *tmp;

	tmp = (t_all *)ft_memalloc(sizeof(t_all));
	if (!tmp)
		return (NULL);
	tmp->cycle_to_die = CYCLE_TO_DIE;
	tmp->players_count = players_count;
	return (tmp);
}


void ft_print_byte(unsigned int byte)
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


void ft_print_memory(t_all *all)
{
	int i;
	unsigned char byte;
	char full[MEM_SIZE];
	t_car *car;

	ft_putnbr(all->total_cycle);
	ft_putchar('\n');

	ft_bzero((void *)full, MEM_SIZE);
	car = all->cars;
	while (car)
	{
		full[car->pos] = 1;
		car = car->next;
	}


	i = 0;
	while (i < MEM_SIZE)
	{
		byte = (unsigned char)(*(all->memory + i));
		if (full[i])
			ft_putstr("\033[7m");
		ft_print_byte((unsigned int)byte);
		if (full[i])
			ft_putstr("\033[00m");
		if ((i + 1) % 25)
			ft_putchar(' ');
		else
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
	car = all->cars;
	while (car)
	{
		i = 0;
		while (i < 17)
		{
			ft_putnbr(car->reg[i]);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		car = car->next;
	}

	ft_putchar('\n');
}

void ft_read_memory(char *memory)
{
/*	char str[100] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x0b, 0x68, 0x10, 0x00, 0x07, 0x00, 0x01,
					0x01, 0x00, 0x00, 0x00, 0x00,
					0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0x02,
					0x00, 0x00};
	ft_memcpy((void *)memory, (void *)str, 27);
*/
/*
//jump
	char str[100] = {0x09, 0xFF, 0xEB};
	ft_memcpy((void *)memory, (void *)str, 4);
*/
/*
//fork
	char str[100] = {0x0c, 0x00, 0x14, 0x00};
	ft_memcpy((void *)memory, (void *)str, 4);
*/


//ld
	//char str[100] = {CHECK_COMMAND, CHECK_ARG_BYTE, CHECK_REG1, CHECK_REG2, CHECK_REG3};
	ft_memcpy((void *)memory, (void *)str, BYTES_COUNT);


}


/*
**	корректировка индекса массива памяти
*/

int		ft_get_pos_of_memory(int pos)
{
	if (pos >= MEM_SIZE || pos < -MEM_SIZE)
		pos = pos % MEM_SIZE;
	else if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}


/*
**	возвращаем число на указанное количество байт из памяти
*/

int		ft_value_from_memory(char *memory, int pos, int size)
{
	int value;
	int i;
	char *byte;

	i = 0;
	value = 0;
	byte = (char *)(&value);
	while (i < size)
	{
		byte[i] = *(memory + ft_get_pos_of_memory(pos + size - i));
		i++;
	}
	return (value);
}


void	ft_value_in_memory(char *memory, int pos, int value, int size)
{
	int i;
	char *byte;

	i = 0;
	byte = (char *)(&value);
	while (i < size)
	{
		*(memory + ft_get_pos_of_memory(pos + size - i - 1)) = byte[i];
		i++;
	}
}

/*
void	ft_make_car_jump(t_car *car)
{
	int jump_length;
	int size;

	if (car->carry)
	{
		size = opt_tab[car->action][SIZE_DIR];
		jump_length = ft_value_from_memory(car->all->memory, car->pos, size);
		jump_length = jump_length % IDX_MOD;
		car->pos = ft_get_pos_of_memory(car->pos + jump_length);
		car->carry = 0;
	}
}
*/


void	ft_copy_fork(t_car *car, int new_pos)
{
	t_car *last_car;

	last_car = car;
	while (last_car->next)
		last_car = last_car->next;
	last_car->next = ft_create_car(-(car->reg[1]), car->all);
	last_car = last_car->next;
	ft_memcpy((void *)last_car, (void *)car, sizeof(car));
	if (car->action == CMD_FORK)
		new_pos = car->pos + new_pos % IDX_MOD - 1;
	else if (car->action == CMD_LFORK)
		new_pos = car->pos + new_pos - 1;
	last_car->pos = ft_get_pos_of_memory(new_pos);
	last_car->pos_shift = 0;
	//last_car->wait = 0;
	last_car->action = READY_TO_ACTION;
}



void	ft_live(t_car *car, int value)
{
	t_all *all;

	all = car->all;
	value = -value;
	if (value > 0 && value <= all->players_count)
	{
		(all->points_of_players[value])++;
		all->last_live_player = value;
	}
	car->cycle_of_calling_life = all->total_cycle;
}



int		ft_args_type(int bits_of_arg, int arg_number, int command)
{
	int type_of_arg;
	int cmd_arg_mask;
	int bits_shift_value;

	bits_shift_value = 2 * (3 - arg_number);
	bits_of_arg = (bits_of_arg >> bits_shift_value) & ARG_MASK;
	type_of_arg = 0;
	if (bits_of_arg == REG_MASK)
		type_of_arg = F_REG;
	else if (bits_of_arg == DIR_MASK)
		type_of_arg = F_DIR;
	else if (bits_of_arg == IND_MASK)
		type_of_arg = F_IND;
	cmd_arg_mask = arg_tab[command][ARG_1 + arg_number];
	if (type_of_arg & cmd_arg_mask)
		return (type_of_arg);
	return (0);
}

int		ft_args_byte_is_valid(t_car *car)
{
	int args_byte;
	int args_count;
	int arg_type_flag;
	int args_flags;
	int i;

	args_byte = ft_value_from_memory(car->all->memory, car->pos, 1);
	args_count = arg_tab[car->action][ARG_COUNT];
	i = 0;
	args_flags = 0;
	while (i < 4)
	{
		args_flags = args_flags << 8;
		if (i < args_count)
		{
			arg_type_flag = ft_args_type(args_byte, i, car->action);
			if (arg_type_flag == 0)
				return (0);
			args_flags = args_flags + arg_type_flag;
		}
		i++;
	}
	return (args_flags);
}




int		ft_valid_reg(t_car *car)
{
	int valid;
	int shift;
	int reg;
	char *byte;

	valid = TRUE;
	shift = 1;
	byte = (char *)(&(car->arg_byte)) + 3;
	while (*byte && valid)
	{
		if (*byte == F_REG)
		{
			reg = ft_value_from_memory(car->all->memory, car->pos + shift, 1);
			if (reg > REG_NUMBER || reg <= 0)
				valid = FALSE;
			shift++;
		}
		else if (*byte == F_IND)
			shift += IND_SIZE;
		else
			shift += opt_tab[car->action][SIZE_DIR];
		byte--;
	}
	car->pos_shift = shift;
	return (valid);
}



int		ft_valid_command(t_car *car)
{
	int valid;

	valid = FALSE;
	car->arg_byte = 0;
	if ((arg_tab[car->action][ARG_BYTE]))
	{
		car->arg_byte = ft_args_byte_is_valid(car);
		if (car->arg_byte && ft_valid_reg(car))
			valid = TRUE;
	}
	else
	{
		car->pos_shift = opt_tab[car->action][SIZE_DIR];
		valid = TRUE;
	}
	return (valid);
}


int		ft_arg_by_number(t_car *car, int number, int *value)
{
	int shift;
	int size;
	char *byte;

	shift = opt_tab[car->action][ARG_BYTE];
	byte = (char *)(&(car->arg_byte)) + 3;
	size = opt_tab[car->action][SIZE_DIR];
	while (*byte)
	{
		if (*byte == F_REG)
			size = 1;
		else if (*byte == F_DIR)
			size = opt_tab[car->action][SIZE_DIR];
		else
			size = IND_SIZE;
		if (!number)
			break ;
		shift += size;
		number--;
		byte--;
	}
	*value = ft_value_from_memory(car->all->memory, car->pos + shift, size);
	return ((int)(*byte));
}


void	ft_ptr_on_arg_by_number(t_car *car, int number, int **value)
{
	int arg;
	int size;
	int address;

	address = 0;
	size = opt_tab[car->action][SIZE_DIR];
	arg = ft_arg_by_number(car, number, *value);
//	ft_putnbr_end(arg);
//	ft_putnbr_end(**value);
	if (arg == F_REG)
		*value = &(car->reg[**value]);
	else if (arg == F_IND)
	{
		address = car->pos + (**value) % IDX_MOD;
		if (car->action != CMD_ST)// || car->action != CMD_STI)
			**value = ft_value_from_memory(car->all->memory, address, IND_SIZE);
		else
			**value = address;
	}
}

/*
void	ft_make_and_or_xor_summ_sub(t_car *car)
{
	int *ptr[3];
	int value[3];

	ft_bzero((void *)value, 3 * 4);
	ptr[0] = &(value[0]);
	ptr[1] = &(value[1]);
	ptr[2] = &(value[2]);
	ft_ptr_on_arg_by_number(car, 0, &(ptr[0]));
	ft_ptr_on_arg_by_number(car, 1, &(ptr[1]));
	ft_ptr_on_arg_by_number(car, 2, &(ptr[2]));
	if (car->action == CMD_AND)
		*(ptr[2]) = *(ptr[0]) & *(ptr[1]);
	else if (car->action == CMD_OR)
		*(ptr[2]) = *(ptr[0]) | *(ptr[1]);
	else if (car->action == CMD_XOR)
		*(ptr[2]) = *(ptr[0]) ^ *(ptr[1]);
	else if (car->action == CMD_ADD)
		*(ptr[2]) = *(ptr[0]) + *(ptr[1]);
	else if (car->action == CMD_SUB)
		*(ptr[2]) = *(ptr[0]) - *(ptr[1]);
	if (*(ptr[2]))
		car->carry = 0;
	else
		car->carry = 1;
}
*/


void	ft_modify_carry(t_car *car, int value)
{

	if (car->action == CMD_AND || car->action == CMD_OR ||
	car->action == CMD_XOR || car->action == CMD_ADD || car->action == CMD_SUB)
	{
		if (value)
			car->carry = 0;
		else
			car->carry = 1;
	}
	else if (car->action == CMD_ZJMP)
		car->carry = 0;

/*	car->carry += opt_tab[car->action][CARRY_ONE];
	if (car->carry > 1)
		car->carry = 1;
	car->carry -= opt_tab[car->action][CARRY_NULL];
	if (car->carry < 0)
		car->carry = 0;*/
}


void	ft_arifm_operations(t_car *car, int **ptr)
{
	if (car->action == CMD_AND)
		*(ptr[2]) = *(ptr[0]) & *(ptr[1]);
	else if (car->action == CMD_OR)
		*(ptr[2]) = *(ptr[0]) | *(ptr[1]);
	else if (car->action == CMD_XOR)
		*(ptr[2]) = *(ptr[0]) ^ *(ptr[1]);
	else if (car->action == CMD_ADD)
		*(ptr[2]) = *(ptr[0]) + *(ptr[1]);
	else if (car->action == CMD_SUB)
		*(ptr[2]) = *(ptr[0]) - *(ptr[1]);
	else if (car->action == CMD_LDI)
		*(ptr[2]) = car->pos + (*(ptr[0]) + *(ptr[1])) % IDX_MOD;
	else if (car->action == CMD_LLD)
		*(ptr[1]) = car->pos + *(ptr[0]);
	else if (car->action == CMD_LLDI)
		*(ptr[2]) = car->pos + *(ptr[0]) + *(ptr[1]);
	else if (car->action == CMD_ZJMP && car->carry)
		car->pos_shift = *(ptr[0]) % IDX_MOD;
	else if (car->action == CMD_AFF)
		ft_putchar((char)*(ptr[0]));
	else if (car->action == CMD_FORK || car->action == CMD_LFORK)
		ft_copy_fork(car, *(ptr[0]));
	else if (car->action == CMD_LIVE)
		ft_live(car, *(ptr[0]));
	ft_modify_carry(car, *(ptr[2]));
}


void	ft_st_sti_operations(t_car *car, int **ptr)
{
	int adress;

	adress = 0;
	if (car->action == CMD_ST)
	{
		if (ptr[1] >= car->reg && ptr[1] <= car->reg + REG_NUMBER)
			*(ptr[1]) = *(ptr[0]);
		else
			ft_value_in_memory(car->all->memory, *(ptr[1]), *(ptr[0]), DIR_SIZE);
	}
	else if (car->action == CMD_STI)
	{
		adress = car->pos + (*(ptr[2]) + *(ptr[3])) % IDX_MOD;
		ft_value_in_memory(car->all->memory, adress, *(ptr[0]), DIR_SIZE);
	}
}




void	ft_use_command(t_car *car)
{
	int *ptr[3];
	int value[3];


	ft_bzero((void *)value, 3 * 4);
	ptr[0] = &(value[0]);
	ptr[1] = &(value[1]);
	ptr[2] = &(value[2]);
	ft_ptr_on_arg_by_number(car, 0, &(ptr[0]));
	ft_ptr_on_arg_by_number(car, 1, &(ptr[1]));
	ft_ptr_on_arg_by_number(car, 2, &(ptr[2]));
	ft_arifm_operations(car, ptr);
	ft_st_sti_operations(car, ptr);
	/*
	if (car->action == CMD_LDI)
		*(ptr[2]) = car->pos + (*(ptr[0]) + *(ptr[1])) % IDX_MOD;
	else if (car->action == CMD_LLD)
		*(ptr[1]) = car->pos + *(ptr[0]);
	else if (car->action == CMD_LLDI)
		*(ptr[2]) = car->pos + *(ptr[0]) + *(ptr[1]);
	*/
//	ft_putstr("    Валидная команда!!\n");
//	exit(0);
}





void	ft_wait_or_do_command(t_car *car)
{
	if (car->wait)
		(car->wait)--;
	else
	{
		//активация команды
		if (ft_valid_command(car))
			ft_use_command(car);
		car->pos = ft_get_pos_of_memory(car->pos + ONE_STEP + car->pos_shift);
		car->action = READY_TO_ACTION;
	}
}



void	ft_choose_action(t_car *car)
{
	unsigned char command;

	command = *(car->all->memory + car->pos);
	if (command && command < CMD_COUNT)
	{
		//car->wait = ft_need_waiting_for_action(command);
		car->wait = opt_tab[command][CMD_PRICE] - 1;
		car->action = command;
	}
	else
		car->action = MOVE_NEXT;
}



void	ft_del_car(t_all *all, t_car *car)
{
	t_car *tmp;

	tmp = all->cars;
	if (all->cars == car)
		all->cars = car->next;
	else
	{
		while (tmp->next != car)
			tmp = tmp->next;
		tmp->next = car->next;
	}
	free(car);
}





void	ft_check_of_cars(t_all *all)
{
	t_car	*car;
	int		cycles;

	car = all->cars;
	while (car)
	{
		cycles = all->total_cycle - car->cycle_of_calling_life;
			if (cycles > all->cycle_to_die)
				ft_del_car(all, car);
		car = car->next;
	}
	all->cycle_to_die -= CYCLE_DELTA;
	all->cycle = 0;
}




void	ft_cycle(t_all *all)
{
	t_car *car;

	car = all->cars;
	while (car)
	{
		if (car->action == READY_TO_ACTION)
			ft_choose_action(car);
		if (car->action == MOVE_NEXT)
		{
			car->pos = ft_get_pos_of_memory(car->pos + ONE_STEP);
			car->pos_shift = 0;
			car->action = READY_TO_ACTION;
		}
		else
			ft_wait_or_do_command(car);
		car = car->next;
	}
	(all->cycle)++;
	(all->total_cycle)++;
	if (all->cycle == all->cycle_to_die || all->cycle_to_die < 0)
		ft_check_of_cars(all);

	ft_print_memory(all);
	if (all->total_cycle == MAX_CYCLE)
		exit(0);
}


int main()
{
	t_all *all;
	all = ft_create_all(1);



	all->cars = ft_create_car(1, all);
	//all->cars->next = ft_create_car(2);
	all->cars->pos = 0;
	//all->cars->next->pos = 3;


	ft_read_memory(all->memory);
	ft_print_memory(all);

	while (all->cars)
	{
		ft_cycle(all);
	}

	//write(1,"qazwsxedcrfvtgbyhnujmik,ol.p;/[]\n",20);
	//lseek(1, -10, SEEK_END);
	//write(1,"qazwsxedcrfvtgbyhnujmik,ol.p;/[]\n",20);

	return (0);
}
