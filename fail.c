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

#ifndef FT_PRINTF_ENUM_H
# define FT_PRINTF_ENUM_H
# define F_REG 1
# define F_DIR 2
# define F_IND 4
# define F_REG_DIR (F_REG + F_DIR)
# define F_REG_IND (F_REG + F_IND)
# define F_DIR_IND (F_DIR + F_IND)
# define F_REG_DIR_IND (F_REG + F_DIR + F_IND)

# define ARG_COUNT 1
# define ARG_BYTE 2
# define ARG_1 3
# define ARG_2 4
# define ARG_3 5

typedef enum	e_com1
{
	MOVE_NEXT = -1,
	READY_TO_ACTION,
	CMD_LIVE,
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
}				t_com1;


typedef enum	e_com1
{
	READY_TO_ACTION,
	CMD_LIVE,
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
	LAST_COUNT
}				t_com1;


g_arg_tab[command]


int g_arg_tab[17][100] =
{
	{0, ARG_COUNT, ARG_BYTE, ARG_1, ARG_2, ARG_3},
	{CMD_LIVE, 1, 0, 0, 0, 0},
	{CMD_LD, 2, 1, F_DIR_IND, F_REG, 0},
	{CMD_ST, 2, 1, F_REG, F_REG_IND, 0},
	{CMD_ADD, 3, 1, F_REG, F_REG, F_REG},
	{CMD_SUB, 3, 1, F_REG, F_REG, F_REG},
	{CMD_AND, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_OR, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_XOR, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_ZJMP, 1, 0, F_DIR, 0, 0},
	{CMD_LDI, 3, 1, F_REG_DIR_IND, F_REG_DIR, F_REG},
	{CMD_STI, 3, 1, F_REG, F_REG_DIR_IND, F_REG_DIR},
	{CMD_FORK, 1, 0, F_DIR, 0, 0},
	{CMD_LLD, 2, 1, F_DIR_IND, F_REG, 0},
	{CMD_LLDI, 3, 1, F_REG_DIR_IND, F_REG_DIR, F_REG},
	{CMD_LFORK, 1, 0, F_DIR, 0, 0},
	{"CMD_AFF"},
};




int g_arg_tab[17][10] =
{
	{0, ARG_COUNT, ARG_BYTE, ARG_1, ARG_2, ARG_3},
	{CMD_LIVE, 1, 0, 0, 0, 0},
	{CMD_LD, 2, 1, F_DIR_IND, F_REG, 0},
	{CMD_ST, 2, 1, F_REG, F_REG_IND, 0},
	{CMD_ADD, 3, 1, F_REG, F_REG, F_REG},
	{CMD_SUB, 3, 1, F_REG, F_REG, F_REG},
	{CMD_AND, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_OR, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_XOR, 3, 1, F_REG_DIR_IND, F_REG_DIR_IND, F_REG},
	{CMD_ZJMP, 1, 0, F_DIR, 0, 0},
	{CMD_LDI, 3, 1, F_REG_DIR_IND, F_REG_DIR, F_REG},
	{CMD_STI, 3, 1, F_REG, F_REG_DIR_IND, F_REG_DIR},
	{CMD_FORK, 1, 0, F_DIR, 0, 0},
	{CMD_LLD, 2, 1, F_DIR_IND, F_REG, 0},
	{CMD_LLDI, 3, 1, F_REG_DIR_IND, F_REG_DIR, F_REG},
	{CMD_LFORK, 1, 0, F_DIR, 0, 0},
	{CMD_AFF, 1, 1, F_REG, 0, 0},
};

#endif
