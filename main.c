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


#define TEST1212121
#define MAX_CYCLE 556

//5935 ld r14 -190
//7118 sti r15(ff0b640f) %0 r14(0)


#define BYTES_COUNT 20
char str[100] = {

0x0b, 0x78, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01,
0x09, 0xff, 0xf6,
0x00, 0x00
};


void	ft_write_new_champ(char *name)
{
	char	buf[5000];
	int		fd;
	int		lenght;
	int 	reader;

	fd = open("text.cor", O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return ;
	lenght = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	reader = read(fd, buf, lenght);
	close(fd);

	fd = open(name, O_RDWR | O_CREAT | O_APPEND | O_TRUNC);
	if (fd < 0)
		return ;

	int i;
	i = 0;
	while (i < lenght)
	{
		if (i == PROG_NAME_LENGTH + 4 + 4 + 3)
			ft_putchar_fd(BYTES_COUNT, fd);
		else
			ft_putchar_fd(buf[i], fd);
		i++;
	}
	i = 0;
	while (i < BYTES_COUNT)
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	close(fd);
}



/*
**	сделать и организовать маски для аргументов
*/



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
	CMD_PRICE = 1,
	CARRY_ONE,
	CARRY_NULL,
	SIZE_DIR
}				e_col_opt;

int    g_opt_tab[17][10] =
{
	{0,			CMD_PRICE, CARRY_ONE, CARRY_NULL, SIZE_DIR},
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


char    opt_cmd[17][10] =
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
	(all->cars_count)++;
	tmp->num = all->cars_count;
	#ifdef TEST123
	if (tmp->num == 28)
	{
		printf("%d\n", all->total_cycle);
		exit(0);
	}
	#endif
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
		if ((i + 1) % 64)
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



int		ft_read_memory(char *name, char *memory)
{
	char	buf[5000];
	int		fd;
	int		lenght;
	int 	reader;

	fd = open(name, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (FALSE);
	lenght = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	reader = read(fd, buf, lenght);



	reader = read(fd, buf, lenght);
	close(fd);
	ft_memcpy((void *)memory, (void *)buf, reader);
	return (TRUE);
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
	if (size == IND_SIZE && (value & 0x8000))
		value = value + 0xFFFF0000;
	return (value);
}

/*
**	вписываем число на указанное количество байт в память
*/

void	ft_value_in_memory(t_car *car, int pos, int value, int size)
{
	int i;
	int mem_pos;
	char *byte;
	char *memory;
	char *cod_owner;

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



t_car	*ft_add_car(int name, t_all *all)
{
	t_car *new;

	new = ft_create_car(name, all);
	if (new)
	{
		new->next = all->cars;
		all->cars = new;
	}
	return (new);
}


void	ft_copy_fork(t_car *car, int new_pos)
{
	t_car *new;

	new = ft_create_car(-(car->reg[1]), car->all);
	ft_memcpy((void *)new, (void *)car, sizeof(t_car));
	new->next = car->all->cars;
	car->all->cars = new;
	if (car->action == CMD_FORK)
		new_pos = car->pos + new_pos % IDX_MOD;
	else if (car->action == CMD_LFORK)
		new_pos = car->pos + new_pos;
	new->pos = ft_get_pos_of_memory(new_pos);
	(car->all->car_station[new->pos])++;
	new->action = READY_TO_ACTION;
	new->num = car->all->cars_count;
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
		length = g_opt_tab[command][DIR_SIZE];
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
	//reg = 0;
	if (valid && arg_bits == REG_CODE)
	{
		reg = ft_value_from_memory(car->all->memory, car->pos + car->pos_shift, 1);

		//ft_putnbr_end(car->action);
		//ft_putnbr_end(reg);

		if (reg > REG_NUMBER || reg <= 0)
			valid = FALSE;
	}
	return (valid);
}


void	ft_return_arg(t_car *car, int arg_bits, int **arg)
{
	int address;
	int size;

	//arg = ft_arg_by_number(car, number, *value);
	address = car->pos + car->pos_shift;
	size = ft_size_of_arg_by_type(car->action, arg_bits);
	**arg = ft_value_from_memory(car->all->memory, address, size);


	/*if (car->action == CMD_LLDI && arg_bits == 3)
	{

		ft_putstr("lldi\n");
		//ft_putnbr_end(arg_bits);
		ft_putnbr_end(car->pos);
		ft_putnbr_end(**arg);
		ft_putnbr_end((**arg)%IDX_MOD);
		ft_putnbr_end(car->pos + (**arg)%IDX_MOD);
		ft_putnbr_end(ft_value_from_memory(car->all->memory,car->pos + (**arg) % IDX_MOD - 1, DIR_SIZE));
		int mmm = car->pos + 4100 + ft_value_from_memory(car->all->memory,car->pos + (**arg) % IDX_MOD - 1, DIR_SIZE);
		ft_putnbr_end(mmm % MEM_SIZE);
		ft_putnbr_end(ft_value_from_memory(car->all->memory, mmm, 4));
		ft_putstr("_____________\n");
	}*/


//	ft_putnbr_end(arg);
//	ft_putnbr_end(**value);
	if (arg_bits == REG_CODE)
		*arg = &(car->reg[**arg]);
	else if (arg_bits == IND_CODE)
	{
		if (car->action == CMD_LLD || car->action == CMD_LLDI)
			address = car->pos + (**arg);
		else
			address = car->pos + (**arg) % IDX_MOD;
		if (car->action != CMD_ST)// || car->action != CMD_STI)
			**arg = ft_value_from_memory(car->all->memory, address - 1, DIR_SIZE);
		//else
			//**arg = (car->pos + **arg) % IDX_MOD;//address;
			//**arg = address;
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
			//ft_putnbr(car->pos_shift);
			//ft_putchar(' ');
			//ft_putnbr_end(arg_bits);
			if (ft_arg_is_valid(car, arg_bits, i) == FALSE)
				valid = FAIL;
			//else
			ft_return_arg(car, arg_bits, &(car->arg[i]));

/*			if (car->action == CMD_LLDI)
			{
				ft_putstr("lldi\n");
				ft_putnbr_end(*car->arg[i]);
				int tmp = ft_value_from_memory(car->all->memory, 83 + (-16030705), 4);
				ft_putnbr_end(((83 - 16030705) % MEM_SIZE) / 64);
				ft_putnbr_end(((83 - 16030705) % MEM_SIZE) % 64);
			}*/

			car->pos_shift += ft_size_of_arg_by_type(car->action, arg_bits);
			car->arg_byte = car->arg_byte | g_opt_tab2[arg_bits][1];
		}
		i++;
	}
	//////////////////////////
	//ft_putnbr_end(valid);
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
		//ft_putnbr_end(valid);
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
	{
		*(arg[1]) = *(arg[0]);
	//	if (car->num == 20)
	//		printf("%d_%d\n", car->action, car->all->total_cycle);
	}
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
			//ft_putnbr_end(*(arg[1]));
			//ft_putnbr_end(car->pos);
			adress = car->pos + (*arg[1]) % IDX_MOD;
			ft_value_in_memory(car, adress, *(arg[0]), DIR_SIZE);
		}
	}
	else if (car->action == CMD_STI)
	{
		adress = car->pos + (*(arg[1]) + *(arg[2])) % IDX_MOD;
		//ft_putnbr_end(*(arg[1]));
		ft_value_in_memory(car, adress, *(arg[0]), DIR_SIZE);
	}
	else if (car->action == CMD_LLDI || car->action == CMD_LDI)
	{
		if (car->action == CMD_LLDI)
			adress = car->pos + *(arg[0]) + *(arg[1]);
		else
			adress = car->pos + (*(arg[0]) + *(arg[1])) % IDX_MOD;
		*(arg[2]) = ft_value_from_memory(car->all->memory, adress - 1, DIR_SIZE);

	}
}



void	ft_print_arg(t_car *car, int *arg, int cmd, int arg_num)
{
	int num;
	int answer;

	num = 0;
	answer = 0;
	if (cmd == CMD_ST || cmd == CMD_STI)
		answer = 1;
	else if (cmd == CMD_LD || cmd == CMD_LLD)
		answer = 2;
	else if (cmd == CMD_ADD || cmd == CMD_SUB || cmd == CMD_AND ||
	cmd == CMD_XOR || cmd == CMD_OR || cmd == CMD_LDI || cmd == CMD_LLDI)
		answer = 3;
	//if (answer == arg_num && arg >= car->reg && arg <= car->reg + REG_NUMBER)
	if ((arg >= car->reg && arg <= car->reg + REG_NUMBER && cmd != CMD_STI && cmd != CMD_ST) ||
	(answer == arg_num && cmd == CMD_STI) || (answer == arg_num && cmd == CMD_ST))
	{
		num = (int)(arg - car->reg);
		printf(" r%d", num);
	}
	else
	{
		if (cmd == CMD_ST && arg >= car->reg && arg <= car->reg + REG_NUMBER)
		{
			num = (int)(arg - car->reg);
			printf(" %d", num);
		}
		else
		printf(" %d", *arg);
	}
}



void	ft_print_operation(t_car *car, int **arg)
{
	if (car->action == CMD_AFF)
		return ;
	printf("P %4d | %s", car->num, opt_cmd[car->action]);


	ft_print_arg(car, arg[0], car->action, 1);
	if (car->action == CMD_FORK || car->action == CMD_LFORK ||
	car->action == CMD_LIVE || car->action == CMD_ZJMP)
	{
		if (car->action == CMD_ZJMP)
			printf(" OK");
		else if (car->action == CMD_FORK)
			printf(" (%d)", car->pos + *arg[0] % IDX_MOD);
		else if (car->action == CMD_LFORK)
			printf(" (%d)", car->pos + *arg[0]);
		printf("\n");
		return ;
	}
	ft_print_arg(car, arg[1], car->action, 2);
	if (car->action == CMD_ST || car->action == CMD_LD ||
	car->action == CMD_LLD)
	{
		printf("\n");
		return ;
	}
	ft_print_arg(car, arg[2], car->action, 3);
	printf("\n");
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
			#ifdef TEST1
			ft_print_operation(car, car->arg);
			#endif
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

	(all->car_station[car->pos])--;
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
	#ifdef TEST1
	printf("It is now cycle %d\n", all->total_cycle);
	#endif
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

}


void	ft_destroy_windows(t_win *wins)
{
	delwin(wins->battlefield);
	delwin(wins->info);
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

/*
int		ft_read_memory(char *name, char *memory)
{
	char	buf[5000];
	int		fd;
	int		lenght;
	int 	reader;

	fd = open(name, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (FALSE);
	lenght = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	reader = read(fd, buf, lenght);



	reader = read(fd, buf, lenght);
	close(fd);
	ft_memcpy((void *)memory, (void *)buf, reader);
	return (TRUE);
}*/





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
	t_play *tmp;
	int i;

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

/*
void	ft_elevate_and_renum_players(t_all *all)
{
	t_play **tmp;
	int i;

	i = 1;
	while (i <= all->players_count)
	{
		if (!all->player[i])
		{
			tmp = &(all->player[i]);
			while (!(*tmp))
				tmp++;
			all->player[i] = *tmp;
			*tmp = NULL;
		}
		//all->player[i]->number = i;
		i++;
	}
}*/

int		ft_arr_of_number_players(t_all *all)
{
	t_play *tmp;
	int i;

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
	int i;
	int pos;
	t_car *car;
	t_play *p;

	i = 1;
	pos = 0;
	while (i < MAX_PLAYERS + 1)
	{
		if (all->player[i])
		{
			p = all->player[i];
			car = ft_create_car(i, all);
			car->next = all->cars;
			all->cars = car;
			car->pos = pos;
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
	t_play *play;

	play = all->player[all->last_live_player];
	ft_putstr("Contestant ");
	ft_putnbr(play->number);
	ft_putstr(", \"");
	ft_putstr(play->prog_name);
	ft_putstr("\", has won !\n");
}



void	ft_print_dump(t_all *all, char *memory)
{
	int i;
	unsigned char byte;
	char *num;

	#ifdef TEST
	char full[MEM_SIZE];
	t_car *car;

	ft_putnbr(all->total_cycle);
	ft_putchar('_');
	ft_putnbr(all->cycle_to_die);
	ft_putchar('\n');
	ft_bzero((void *)full, MEM_SIZE);
	car = all->cars;
	while (car)
	{
		//if (car->num == 141)
		full[car->pos] = 1;
		car = car->next;
	}
	#endif

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

		#ifdef TEST
		if (full[i])
			ft_putstr("\033[7m");
		#endif

		ft_print_byte((unsigned int)byte);

		#ifdef TEST
		if (full[i])
			ft_putstr("\033[00m");
		#endif
		if ((i + 1) % DUMP_LENGTH)
			ft_putchar(' ');
		else
			ft_putstr(" \n");
		i++;
	}
	#ifndef TEST
	ft_error(all, NULL);
	#endif

	#ifdef TEST
	ft_putchar('\n');
	ft_putnbr_end(all->cycle);

	car = all->cars;
	while (car)
	{
		if (car->action >= 0)
		{
			ft_putnbr(car->num);
			ft_putchar(' ');
			ft_putnbr(car->action);
			ft_putchar(' ');
			ft_putnbr(car->pos);
			ft_putchar(' ');
			ft_putnbr(car->cycle_of_calling_life);
			ft_putchar(' ');
			i = 0;
			while (i < 17)
			{
				ft_putnbr(car->reg[i]);
				ft_putchar(' ');
				i++;
			}
			ft_putchar('\n');
		}
		car = car->next;
	}
	ft_putchar('\n');
	#endif
}




t_win	*ft_create_windows(void)
{
	t_win *wins;

	wins = (t_win *)ft_memalloc(sizeof(t_win));
	if (!wins)
		return (NULL);
	wins->frame = newwin(FRAME_H, FRAME_L, 0, 0);
	wins->battlefield = subwin(wins->frame, BATTLEFIELD_H, BATTLEFIELD_L, BATTLEFIELD_Y, BATTLEFIELD_X);
	wins->info = subwin(wins->frame, INFO_H, INFO_L, INFO_Y, INFO_X);
	//wins->battlefield = newwin(BATTLEFIELD_H, BATTLEFIELD_L, BATTLEFIELD_Y, BATTLEFIELD_X);
	//keypad(wins->battlefield, TRUE);
	//nodelay(wins->battlefield, TRUE);
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
	//keypad(all->wins->battlefield, TRUE);
	//nodelay(all->wins->battlefield, TRUE);

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
	wattron(win, COLOR_PAIR(1));
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
	wprintw(win, "\n\n\n%s", CAPYBARA);
	wattroff(win, COLOR_PAIR(MAX_PLAYERS + 2) | A_BOLD);
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 3) | A_BOLD);
	wprintw(win, "\n\n\n%s", SCHOOL_21);
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
	//wattrset(win, PAIR_NUMBER(COLOR_PAIR(0)));
	i = 0;
	while (i < MEM_SIZE)
	{
		attrs = ft_get_colour(all, i);
		wattron(win, attrs);
		wprintw(win, "%02hhx", all->memory[i]);
		wattroff(win, attrs);
		//wprintw(win, "%d", all->code_owner[i]);
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




int main(int argc, char **argv)
{
	t_all *all;

	all = ft_create_all(0);
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

	//ft_elevate_and_renum_players(all);

	ft_place_prog_and_cars(all);


	if (all->visualisation)
		ft_init_ncurses(all);
	else
		ft_print_champ(all);
/*	int i = 0;
	printf("_%d_\n", all->players_count);
	while (i < MAX_PLAYERS + 1)
	{
		printf("%d_", i);
		if (all->player[i])
			printf("%s_%d", (all->player[i])->prog_name, (all->player[i])->number);
		printf("\n");
		i++;
	}*/

//	ft_print_memory(all);




	if (all->flag_dumb && all->dumb_cycle == 0)
		ft_print_dump(all, all->memory);


	while (all->cars || all->pause)
	{
		//ft_putnbr_end(all->total_cycle);
		if (!all->pause)
			ft_cycle(all);

		#ifdef TEST
		if (all->total_cycle > MAX_CYCLE - 7)
			ft_print_dump(all, all->memory);
		#endif
		//ft_putnbr_end(1);

		//ft_putnbr_end(2);
		if (all->cars && all->cycle >= all->cycle_to_die)
			ft_check_of_cars(all);

		if (all->flag_dumb && all->dumb_cycle == all->total_cycle)
			ft_print_dump(all, all->memory);
		//ft_putnbr_end(1);

		//ft_putnbr_end(2);
		#ifdef TEST
		if (all->total_cycle == MAX_CYCLE)
		{
			printf("%d_%d\n", (-16030705 % 512)/64, (-16030705 % 512)%64);
			exit(0);
		}
		#endif

		if (all->visualisation)
			ft_refresh_windows(all);
	}
	if (!all->visualisation)
		ft_print_winner(all);
	ft_error(all, NULL);

	return (0);
}
