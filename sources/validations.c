/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:09:05 by ssoraka           #+#    #+#             */
/*   Updated: 2019/09/12 17:09:06 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

int		ft_check_errors(t_all *all, char *buf, int size)
{
	int len;

	len = 4 + PROG_NAME_LENGTH + 7;
	if (size > MAX_CODE)
		ft_error_and_del_all(all, MSG_ERROR4);
	if (size < MIN_CODE)
		ft_error_and_del_all(all, MSG_ERROR5);
	if (COREWAR_EXEC_MAGIC != ft_value_from_memory(buf, -1, 4))
		ft_error_and_del_all(all, MSG_ERROR6);
	if (size - MIN_CODE != ft_value_from_memory(buf, len - 4, 4))
		ft_error_and_del_all(all, MSG_ERROR7);
	if (0 != ft_value_from_memory(buf, len - 8, 4))
		ft_error_and_del_all(all, MSG_ERROR8);
	if (0 != ft_value_from_memory(buf, MIN_CODE - 5, 4))
		ft_error_and_del_all(all, MSG_ERROR8);
	return (TRUE);
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
		all->flag_aff = 0;
		*argv = *argv + 2;
		*argc = *argc - 2;
	}
	if (*argc > 0 && !ft_strcmp(**argv, "-vis"))
	{
		all->visualisation = 1;
		all->flag_dumb = 0;
		all->flag_aff = 0;
		(*argv)++;
		(*argc)--;
	}
}
