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

typedef enum	s_col_opt
{
	CMD_NAME = 0,
	CMD_PRICE = 1,
	CARRY_ONE,
	CARRY_NULL,
	SIZE_DIR
}				e_col_opt;

int    g_opt_tab[17][6] =
{
	{CMD_NAME, CMD_PRICE, CARRY_ONE, CARRY_NULL, SIZE_DIR},
	{CMD_LIVE,	10, 0, 0, 4},
	{CMD_LD,	5, 1, 0, 4},
	{CMD_ST,	5, 0, 0, 4},
	{CMD_ADD,	10, 1, 0, 4},
	{CMD_SUB,	10, 1, 0, 4},
	{CMD_AND,	6, 1, 0, 4},
	{CMD_OR,	6, 1, 0, 4},
	{CMD_XOR,	6, 1, 0, 4},
	{CMD_ZJMP,	20, 0, 1, 2},
	{CMD_LDI,	25, 0, 1, 2},
	{CMD_STI,	25, 0, 1, 2},
	{CMD_FORK,	800, 0, 1, 2},
	{CMD_LLD,	10, 1, 0, 4},
	{CMD_LLDI,	50, 1, 1, 2},
	{CMD_LFORK,	1000, 0, 1, 2},
	{CMD_AFF,	2, 0, 0, 4}
};


char    opt_cmd[17][7] =
{
	"",
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};




#define MASKS 0

int    g_opt_tab2[4][10] =
{
	{0,			MASKS},
	{REG_CODE,	T_REG},
	{DIR_CODE,	T_DIR},
	{IND_CODE,	T_IND}
};



typedef enum	s_col_arg
{
	ARG_COUNT = 1,
	ARG_BYTE,
	ARG_1,
	ARG_2,
	ARG_3
}				e_col_arg;


int    g_arg_tab[17][10] =
{
	{0,		ARG_COUNT, ARG_BYTE, ARG_1,ARG_2,ARG_3},
	{CMD_LIVE,	1,	0,	0,				0,				0},
	{CMD_LD,	2,	1,	T_DIR_IND,		T_REG,			0},
	{CMD_ST,	2,	1,	T_REG,			T_REG_IND,		0},
	{CMD_ADD,	3,	1,	T_REG,			T_REG,			T_REG},
	{CMD_SUB,	3,	1,	T_REG,			T_REG,			T_REG},
	{CMD_AND,	3,	1,	T_REG_DIR_IND,	T_REG_DIR_IND,	T_REG},
	{CMD_OR,	3,	1,	T_REG_DIR_IND,	T_REG_DIR_IND,	T_REG},
	{CMD_XOR,	3,	1,	T_REG_DIR_IND,	T_REG_DIR_IND,	T_REG},
	{CMD_ZJMP,	1,	0,	T_DIR,			0,				0},
	{CMD_LDI,	3,	1,	T_REG_DIR_IND,	T_REG_DIR,		T_REG},
	{CMD_STI,	3,	1,	T_REG,			T_REG_DIR_IND,	T_REG_DIR},
	{CMD_FORK,	1,	0,	T_DIR,			0,				0},
	{CMD_LLD,	2,	1,	T_DIR_IND,		T_REG,			0},
	{CMD_LLDI,	3,	1,	T_REG_DIR_IND,	T_REG_DIR,		T_REG},
	{CMD_LFORK,	1,	0,	T_DIR,			0,				0},
	{CMD_AFF,	1,	1,	T_REG,			0,				0},
};

char    g_errors_tab[10][200] =
{
	"Error of malloc",
	"Can't read this files\n",
	"Colors are not supported\n",
	"Repeat of numbers\n",
	"Code to big\n",
	"Code to small\n",
	"No magic\n",
	"Differen byte size of programm\n",
	"No null-terminator\n",
};



t_car	*ft_create_car(int player_num, t_all *all, int pos)
{
	t_car *tmp;

	tmp = (t_car *)ft_memalloc(sizeof(t_car));
	if (!tmp)
		ft_error(all, g_errors_tab[0]);
	tmp->reg[1] = -player_num;
	tmp->all = all;
	if (all->cars)
		all->cars->prev = tmp;
	tmp->next = all->cars;
	all->cars = tmp;
	(all->last_car_number)++;
	(all->cars_count)++;
	tmp->num = all->last_car_number;
	tmp->pos = pos;
	tmp->action = READY_TO_ACTION;
	return (tmp);
}



t_all	*ft_create_all(int players_count)
{
	t_all *tmp;

	tmp = (t_all *)ft_memalloc(sizeof(t_all));
	if (!tmp)
		ft_error(NULL, g_errors_tab[0]);
	tmp->cycle_to_die = CYCLE_TO_DIE;
	tmp->players_count = players_count;
	tmp->delay = DELAY;
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
		reg = ft_value_from_memory(car->all->memory, car->pos + car->pos_shift, 1);
		if (reg > REG_NUMBER || reg <= 0)
			valid = FALSE;
	}
	return (valid);
}


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
			address = car->pos + (**arg);
		else
			address = car->pos + (**arg) % IDX_MOD;
		if (car->action != CMD_ST)
			**arg = ft_value_from_memory(car->all->memory, address - 1, DIR_SIZE);
	}
}


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
		adress = car->pos + (*(arg[0]) + *(arg[1])) % IDX_MOD;
		if (car->action == CMD_LLDI)
			adress = car->pos + *(arg[0]) + *(arg[1]);
		*(arg[2]) = ft_value_from_memory(car->all->memory, adress - 1, DIR_SIZE);
	}
}


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


void	ft_del_car(t_all *all, t_car *car)
{
	t_car *tmp;

	if (!car || !all || !all->cars)
		return ;
	(all->cars_count)--;
	(all->car_station[car->pos])--;
	if (all->cars == car)
	{
		all->cars = car->next;
		if (all->cars)
			all->cars->prev = NULL;
	}
	else
	{
		tmp = car->prev;
		tmp->next = car->next;
		if (car->next)
			tmp->next->prev = tmp;
	}
	ft_memdel((void **)(&car));
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
	ft_bzero((void *)all->car_station, MEM_SIZE * 4);
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


void	ft_destroy_windows(t_win *wins)
{
	delwin(wins->battlefield);
	delwin(wins->info);
	delwin(wins->frame);
	endwin();
}


void	ft_error(t_all *all, char *error_msg)
{
	t_play *play;

	play = NULL;
	if (error_msg)
		ft_putstr(error_msg);
	while (all && all->cars)
		ft_del_car(all, all->cars);
	while (all && all->players)
	{
		play = all->players;
		all->players = all->players->next;
		free(play);
	}
	if (all->wins)
		ft_destroy_windows(all->wins);
	free(all->wins);
	free(all);
	exit (0);
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





int		ft_check_errors(t_all *all, char *buf, int size)
{
	int len;

	len = 4 + PROG_NAME_LENGTH + 7;
	if (size > MAX_CODE)
		ft_error(all, g_errors_tab[4]);
	if (size < MIN_CODE)
		ft_error(all, g_errors_tab[5]);
	if (COREWAR_EXEC_MAGIC != ft_value_from_memory(buf, -1, 4))
		ft_error(all, g_errors_tab[6]);
	if (size - MIN_CODE != ft_value_from_memory(buf, len - 4, 4))
		ft_error(all, g_errors_tab[7]);
	if (0 != ft_value_from_memory(buf, len - 8, 4))
		ft_error(all, g_errors_tab[8]);
	if (0 != ft_value_from_memory(buf, MIN_CODE - 5, 4))
		ft_error(all, g_errors_tab[8]);
	return(TRUE);
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




/*
**	проверка наличия лишних символов в строке и
*/

int		ft_is_not_number(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (**str == '0' && (*str + 1) && ft_isdigit(*(*str + 1)))
		(*str)++;
	tmp = *str;
	if (!ft_isdigit(*tmp))
		return (1);
	while (*tmp && ft_isdigit(*tmp))
		tmp++;
	i = ft_strlen(tmp);
	while (i > 0)
	{
		if (ft_isspace(tmp[i - 1]))
			tmp[i - 1] = '\0';
		else
			break ;
		i--;
	}
	if (*tmp)
		return (1);
	return (0);
}

/*
**	проверка наличия лишних символов в строке и
**	принадлежности числа к integer
*/

int		ft_str_not_int_number(char *str)
{
	int i;
	int minus;

	i = 0;
	minus = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		minus = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (ft_is_not_number(&str))
		return (1);
	if (ft_strlen(str) > 10)
		return (1);
	if (ft_strlen(str) == 10)
	{
		if (minus && ft_strcmp("2147483648", str) < 0)
			return (1);
		if (!minus && ft_strcmp("2147483647", str) < 0)
			return (1);
	}
	return (0);
}


int		ft_check_flags(t_all *all, char *argv, char *flag)
{
	if (!ft_strcmp(flag, "-n") && ft_atoi(argv) > 0 &&
	ft_atoi(argv) <= MAX_PLAYERS)
		return (ft_atoi(argv));
	else if (!ft_strcmp(flag, "-dump") && ft_atoi(argv) > 0)
	{
		all->flag_dumb = 1;
		all->dumb_cycle = ft_atoi(argv);
	}
	else if (!ft_strcmp(flag, "-a"))
		all->flag_aff = 1;
	else if (!ft_strcmp(flag, "-vis"))
		all->visualisation = 1;
	return (0);
}



void	ft_skip_flags(t_all *all, char ***argv, int *argc)
{
	(*argv)++;
	(*argc)--;
	if (*argc > 0 && !ft_strcmp(**argv, "-a"))
	{
		all->flag_aff = 1;
		(*argv)++;
		(*argc)--;
	}
	if (*argc > 1 && !ft_strcmp(**argv, "-dump") &&
	!ft_str_not_int_number(*(*argv + 1)))
	{
		all->dumb_cycle = ft_atoi(*(*argv + 1));
		all->flag_dumb = 1;
		*argv = *argv + 2;
		*argc = *argc - 2;
	}
	if (*argc > 0 && !ft_strcmp(**argv, "-vis"))
	{
		all->visualisation = 1;
		all->flag_dumb = 0;
		(*argv)++;
		(*argc)--;
	}
}




int		ft_read_memory2(t_all *all, char **argv, int argc)
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
		ft_atoi(argv[i]) > 0 && ft_atoi(argv[i]) <= MAX_PLAYERS)
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
			ft_memcpy((void *)all->memory + pos, (void *)p->programm, p->prog_size);
			ft_memset((void *)all->code_owner + pos, i, p->prog_size);
			pos += MEM_SIZE / (all->players_count);
		}
		i++;
	}
	all->last_live_player = -(car->reg[1]);
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


t_win	*ft_create_windows(void)
{
	t_win *wins;

	wins = (t_win *)ft_memalloc(sizeof(t_win));
	if (!wins)
		return (NULL);
	wins->frame = newwin(FRAME_H, FRAME_L, 0, 0);
	wins->battlefield = subwin(wins->frame, BATTLEFIELD_H,\
		BATTLEFIELD_L, BATTLEFIELD_Y, BATTLEFIELD_X);
	wins->info = subwin(wins->frame, INFO_H, INFO_L, INFO_Y, INFO_X);
	keypad(wins->frame, TRUE);
	nodelay(wins->frame, TRUE);
	return (wins);
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

void	ft_init_ncurses(t_all *all)
{
	initscr();
	noecho();
	curs_set(FALSE);

	if (!(all->wins = ft_create_windows()))
		ft_error(all, g_errors_tab[0]);
	if (!has_colors())
		ft_error(all, g_errors_tab[2]);
	start_color();
	set_color();
}



void	ft_print_info(t_all *all)
{
	WINDOW *win;
	int i;
	t_play *player;

	win = all->wins->info;
	wmove(win, 0, 0);
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 4));
	wprintw(win, "%s\n", CORE_WAR);
	wprintw(win, "Total cycle: %d\n", all->total_cycle);
	wprintw(win, "Cycle: %d\n", all->cycle);
	wprintw(win, "Cycle to die: %d\n", all->cycle_to_die);
	wprintw(win, "Count of process: %d\nWinner: ", all->cars_count);
	wattron(win, COLOR_PAIR(all->last_live_player));
	wprintw(win, "%s\n", (all->player[all->last_live_player])->prog_name);
	wattroff(win, COLOR_PAIR(all->last_live_player));
	wprintw(win, "\nChampions:\n");
	i = 1;
	while (i <= MAX_PLAYERS)
	{
		wattron(win, COLOR_PAIR(i));
		if ((player = all->player[i]))
			wprintw(win, "%d - %s\n", player->number ,player->prog_name);
		wattroff(win, COLOR_PAIR(i));
		i++;
	}
}

void	ft_print_bonus(t_all *all)
{
	WINDOW *win;

	win = all->wins->info;
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 2) | A_BOLD);
	wprintw(win, "\n\n%s", CAPYBARA);
	wattroff(win, COLOR_PAIR(MAX_PLAYERS + 2) | A_BOLD);
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 3) | A_BOLD);
	wprintw(win, "\n\n%s", SCHOOL_21);
	wattroff(win, COLOR_PAIR(MAX_PLAYERS + 3) | A_BOLD);
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


void	ft_print_battlefield(t_all *all)
{
	WINDOW *win;
	attr_t attrs;
	int i;

	win = all->wins->battlefield;
	wmove(win, 0, 0);
	i = 0;
	while (i < MEM_SIZE)
	{
		attrs = ft_get_colour(all, i);
		wattron(win, attrs);
		wprintw(win, "%02hhx", all->memory[i]);
		wattroff(win, attrs);
		wprintw(win, " ");
		i++;
	}

}


void	ft_print_frame(WINDOW *frame)
{
	int i;
	int j;
	int colour;

	colour = MAX_PLAYERS + 1;
	i = 0;
	while (i < FRAME_H)
	{
		j = 0;
		while (j < FRAME_L)
		{
			if ((j < 1 && i < 1) || (i == FRAME_H - 1 && j == FRAME_L - 1) ||
			(i == FRAME_H - 1 && j < 1) || (i < 1 && j == FRAME_L - 1))
				mvwaddch(frame, i, j, 'X' | COLOR_PAIR(colour) | A_BOLD);
			else if (i < 1 || i == FRAME_H - 1)
				mvwaddch(frame, i, j, 'X' | COLOR_PAIR(colour) | A_BOLD);
			else if (j < 1 || j >= FRAME_L - 1 || j == INFO_X - 4)
				mvwaddch(frame, i, j, 'X' | COLOR_PAIR(colour) | A_BOLD);
			j++;
		}
		i++;
	}
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
		ft_error(all, NULL);
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



void	ft_create_and_place_players(t_all *all, int argc, char **argv)
{
	ft_skip_flags(all, &argv, &argc);
	if (!argc)
		ft_error(all, MANUAL);
	if (ft_read_memory2(all, argv, argc) == FAIL)
		ft_error(all, g_errors_tab[1]);
	if (!all->players_count)
		ft_error(all, g_errors_tab[3]);
	if (ft_arr_of_number_players(all) == FAIL)
		ft_error(all, g_errors_tab[4]);
	ft_place_players_without_num(all);
}



int main(int argc, char **argv)
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
		ft_print_dump(all, all->memory);
	while (all->cars || all->pause)
	{
		if (!all->pause)
			ft_cycle(all);
		if (all->flag_dumb && all->dumb_cycle == all->total_cycle)
			ft_print_dump(all, all->memory);
		if (all->visualisation)
			ft_refresh_windows(all);
	}
	if (!all->visualisation)
		ft_print_winner(all);
	ft_error(all, NULL);
	return (0);
}
