/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar_enum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:13:40 by ssoraka           #+#    #+#             */
/*   Updated: 2019/08/25 17:13:40 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_ENUM_H
# define FT_COREWAR_ENUM_H
# include "op.h"
# include "ft_corewar.h"
# include <ncurses.h>

typedef enum	e_com
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
}				t_com;

typedef enum	e_col_opt
{
	CMD_NAME = 0,
	CMD_PRICE = 1,
	CARRY_ONE,
	CARRY_NULL,
	SIZE_DIR
}				t_col_opt;

# define MASKS 0

typedef enum	e_col_arg
{
	ARG_COUNT = 1,
	ARG_BYTE,
	ARG_1,
	ARG_2,
	ARG_3
}				t_col_arg;

# define ARG_MASK		0b00000011
# define T_REG			1
# define T_DIR			2
# define T_IND			4
# define T_REG_DIR		(T_REG + T_DIR)
# define T_REG_IND		(T_REG + T_IND)
# define T_DIR_IND		(T_DIR + T_IND)
# define T_REG_DIR_IND	(T_REG + T_DIR + T_IND)

#endif
