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

#define MAX_CYCLE 836


#define BYTES_COUNT 20
char str[100] = {

0x04, 0b00000010, 0x0c, 0x0c, 0x0c,
0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
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

#define ONE_STEP 1
#define MIN_CODE (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
#define MAX_CODE (MIN_CODE + CHAMP_MAX_SIZE)

#define ARG_MASK 0b00000011
//#define REG_MASK 0b00000001
//#define DIR_MASK 0b00000010
//#define IND_MASK 0b00000011

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
	{CMD_ST,	5, 0, 0, 4},
	{CMD_ADD,	10, 1, 0, 4},
	{CMD_SUB,	10, 1, 0, 4},
	{CMD_AND,	6, 1, 0, 4},
	{CMD_OR,	6, 1, 0, 4},
	{CMD_XOR,	6, 1, 0, 4},
	{CMD_ZJMP,	20, 0, 1, 2},
	{CMD_LDI,	25, 1, 1, 2},
	{CMD_STI,	25, 0, 1, 2},
	{CMD_FORK,	800, 0, 1, 2},
	{CMD_LLD,	10, 1, 0, 4},
	{CMD_LLDI,	50, 1, 1, 2},
	{CMD_LFORK,	1000, 0, 1, 2},
	{CMD_AFF,	2, 0, 0, 4}
};






#define T_REG			1
#define T_DIR			2
#define T_IND			4
#define T_REG_DIR		(T_REG + T_DIR)
#define T_REG_IND		(T_REG + T_IND)
#define T_DIR_IND		(T_DIR + T_IND)
#define T_REG_DIR_IND	(T_REG + T_DIR + T_IND)

#define MASKS			0
#define SIZE_BYTE		2
#define LEN_BYTE		3

int    opt_tab2[4][10] =
{
	{0,			MASKS},
	{REG_CODE,	T_REG},
	{DIR_CODE,	T_DIR},
	{IND_CODE,	T_IND}
};


#define ARG_COUNT	1
#define ARG_BYTE	2
#define ARG_1		3
#define ARG_2		4
#define ARG_3		5


int    arg_tab[17][10] =
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



#define MSG_ERROR1 "No arguments\n"
#define MSG_ERROR2 "Can't read source file"


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
	int				cycle_to_die;
	int				cycle;
	int				total_cycle;
	//int				points_of_players[MAX_PLAYERS];
	int				last_live_player;
	int				players_count;
	int				flag_dumb;
	struct s_play	*players;
	struct s_play	*player[MAX_PLAYERS];
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
	int				*arg[3];
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
	if (size == IND_SIZE && (value & 0x8000))
		value = value + 0xFFFF0000;
	return (value);
}

/*
**	вписываем число на указанное количество байт в память
*/

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

	new = ft_add_car(-(car->reg[1]), car->all);
	ft_memcpy((void *)new, (void *)car, sizeof(car));
	if (car->action == CMD_FORK)
		new_pos = car->pos + new_pos % IDX_MOD;
	else if (car->action == CMD_LFORK)
		new_pos = car->pos + new_pos;
	new->pos = ft_get_pos_of_memory(new_pos);
	new->action = READY_TO_ACTION;
}

void	ft_live(t_car *car, int value)
{
	t_all *all;

	all = car->all;
	value = -value;
	if (value > 0 && value <= all->players_count)
	{
		((all->player[value])->points)++;
		all->last_live_player = value;
	}
	car->cycle_of_calling_life = all->total_cycle;
}



int		ft_size_of_arg_by_type(int command, int arg_bit)
{
	int length;

	length = 0;
	if (arg_bit == REG_CODE)
		length = 1;
	else if (arg_bit == DIR_CODE)
		length = opt_tab[command][DIR_SIZE];
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

	valid = TRUE;
	reg = 0;
	if (arg_bits == REG_CODE)
	{
		reg = ft_value_from_memory(car->all->memory, car->pos + car->pos_shift, 1);
		if (reg > REG_NUMBER || reg <= 0)
			valid = FALSE;
	}
	arg_type = opt_tab2[arg_bits][1];
	cmd_arg_mask = arg_tab[car->action][ARG_1 + arg_number];
	if (arg_type & cmd_arg_mask)
		valid = FALSE;
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
//	ft_putnbr_end(arg);
//	ft_putnbr_end(**value);
	if (arg_bits == REG_CODE)
		*arg = &(car->reg[**arg]);
	else if (arg_bits == IND_CODE)
	{
		address = car->pos + (**arg) % IDX_MOD;
		if (car->action != CMD_LLD)
			address = car->pos + (**arg);
		if (car->action != CMD_ST)// || car->action != CMD_STI)
			**arg = ft_value_from_memory(car->all->memory, address - 1, DIR_SIZE);
		else
			**arg = address;
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
		if (i < arg_tab[car->action][ARG_COUNT])
		{
			if (ft_arg_is_valid(car, arg_bits, i) == FAIL)
				valid = FAIL;
			else
				ft_return_arg(car, arg_bits, &(car->arg[i]));
			car->pos_shift += ft_size_of_arg_by_type(car->action, arg_bits);
			car->arg_byte = car->arg_byte | opt_tab2[arg_bits][1];
		}
		i++;
	}
	return (valid);
}



int		ft_valid_command(t_car *car)
{
	int valid;


	valid = TRUE;
	if ((arg_tab[car->action][ARG_BYTE]))
	{
		car->pos_shift = ONE_STEP;
		if (ft_parsing_of_args(car) == FAIL)
			valid = FALSE;
		//ft_putnbr_end(car->pos_shift);
	}
	else
	{
		ft_return_arg(car, DIR_CODE, &(car->arg[0]));
		car->pos_shift = opt_tab[car->action][SIZE_DIR];
	}
	return (valid);
}



void	ft_modify_carry(t_car *car, int **arg)
{
	int value;

	value = 0;
	if (!opt_tab[car->action][CARRY_ONE])
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
	else if (car->action == CMD_AFF)
		ft_putchar((char)*(arg[0]));
	ft_modify_carry(car, arg);
}


void	ft_st_sti_lldi_ldi_cmd(t_car *car, int **arg)
{
	int adress;

	adress = 0;
	if (car->action == CMD_ST)
	{
		if (arg[1] >= car->reg && arg[1] <= car->reg + REG_NUMBER)
			*(arg[1]) = *(arg[0]);
		else
			ft_value_in_memory(car->all->memory, *(arg[1]), *(arg[0]), DIR_SIZE);
	}
	else if (car->action == CMD_STI)
	{
		adress = car->pos + (*(arg[1]) + *(arg[2])) % IDX_MOD;
		ft_value_in_memory(car->all->memory, adress, *(arg[0]), DIR_SIZE);
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
			//ft_use_command(car);
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



void	ft_error(t_all *all, char *error_msg)
{
	if (error_msg)
		ft_putendl(error_msg);
	while (all && all->cars)
		ft_del_car(all, all->cars);
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

	tmp = (t_play *)ft_memalloc(sizeof(t_play));
	if (tmp)
	{
		buf = buf + 4;
		ft_memcpy((void *)tmp->prog_name, (void *)buf, PROG_NAME_LENGTH);
		buf = buf + PROG_NAME_LENGTH + 4 + 3;
		tmp->prog_size = *((int *)(buf));
		buf++;
		ft_memcpy((void *)tmp->comment, (void *)buf, COMMENT_LENGTH);
		buf = buf + COMMENT_LENGTH + 4;
		ft_memcpy((void *)tmp->programm, (void *)buf, tmp->prog_size);
		tmp->number = number;
		tmp->next = all->players;
		all->players = tmp;
		(all->players_count)++;
	}
	return (tmp);
}





int		ft_read_player(t_all *all, char *name, int number)
{
	char	buf[MAX_CODE + 1];
	int		fd;
	int		reader;
	int		valid;
	int		len;

	valid = FAIL;
	len = 4 + PROG_NAME_LENGTH + 8;
	fd = open(name, O_RDONLY);
	if ((fd = open(name, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		return (valid);
	if (((reader = read(fd, buf, MAX_CODE + 1)) <= MAX_CODE) &&
	reader >= MIN_CODE && //проверить
	reader - MIN_CODE == *((int *)(buf + len - 1)) && //проверить
	buf[0] == 0 && buf[1] == (char)0xea &&
	buf[2] == (char)0x83 && buf[3] == (char)0xf3 &&
	*((int *)(buf + len - 4)) == 0 && *((int *)(buf + len + COMMENT_LENGTH)) == 0)
		valid = SUCCESS;
	if (!(ft_add_player(all, buf, number)))
		valid = FAIL;
	close(fd);
	return (valid);
}




int		ft_read_memory2(t_all *all, char **argv, int argc)
{
	int i;
	int number;
	int flag_n;

	flag_n = FALSE;
	i = 0;
	while (i < argc)
	{
		if (flag_n == FALSE)
			number = 0;
		if (flag_n == TRUE) // && ft_is_int_num(argv)
		{
			flag_n = FALSE;
			number = ft_atoi(argv[i]);
		}
		if (!ft_strcmp(argv[i], "-n"))
			flag_n = TRUE;
		else if (!ft_strcmp(argv[i], "-dumb"))
			all->flag_dumb = 1;
		else if (ft_read_player(all, argv[i], number) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}






int main(int argc, char **argv)
{
	t_all *all;

	all = ft_create_all(1);
	if (argc == 1)
		ft_error(all, MSG_ERROR1);
	if (ft_read_memory2(all, argv + 1, argc - 1) == FAIL)
		ft_error(all, MSG_ERROR2);

exit(0);
	if (ft_read_memory(argv[1], all->memory))
		ft_print_memory(all);
	else
		ft_putstr("не прочел память\n");


		//all->cars = ft_create_car(1, all);
		ft_add_car(1, all);
		//all->cars->next = ft_create_car(2);
		all->cars->pos = 0;
		//all->cars->next->pos = 3;


	//ft_write_new_champ("text2.cor");

	while (all->cars)
	{
		ft_cycle(all);
	}

	//write(1,"qazwsxedcrfvtgbyhnujmik,ol.p;/[]\n",20);
	//lseek(1, -10, SEEK_END);
	//write(1,"qazwsxedcrfvtgbyhnujmik,ol.p;/[]\n",20);

	return (0);
}
