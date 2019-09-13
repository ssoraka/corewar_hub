/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:14:21 by ljalikak          #+#    #+#             */
/*   Updated: 2019/06/19 14:14:22 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_H
# define FT_COREWAR_H
# include <ncurses.h>
# include "libft.h"
# include "op.h"
# include "ft_corewar_enum.h"
# include "ft_corewar_struct.h"

# define DUMP_LENGTH 32

/*
**	for visualisation
*/

# define DELAY 8
# define DELAY_BOLD 100
# define BYTE_IN_STRING 64
# define BATTLEFIELD_Y 2
# define BATTLEFIELD_X 4
# define BATTLEFIELD_L (BYTE_IN_STRING * 3)
# define BATTLEFIELD_H (MEM_SIZE / 64)
# define INFO_X (BATTLEFIELD_L + 2 * BATTLEFIELD_X + 2)
# define INFO_Y BATTLEFIELD_Y
# define INFO_L (40)
# define INFO_H (BATTLEFIELD_H)
# define FRAME_H (BATTLEFIELD_H + BATTLEFIELD_Y * 2)
# define FRAME_L (INFO_X + INFO_L + BATTLEFIELD_X)

# define MSG_ERROR0 "Error of malloc\n"
# define MSG_ERROR1 "Can't read this files\n"
# define MSG_ERROR2 "Colors are not supported\n"
# define MSG_ERROR3 "Repeat of numbers\n"
# define MSG_ERROR4 "Code to big\n"
# define MSG_ERROR5 "Code to small\n"
# define MSG_ERROR6 "No magic\n"
# define MSG_ERROR7 "Differen byte size of programm\n"
# define MSG_ERROR8 "No null-terminator\n"
# define MSG_ERROR9 "No players\n"

# define MANUAL "MAN"

/*
**	for validations
*/

# define ONE_STEP 1
# define MIN_CODE (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
# define MAX_CODE (MIN_CODE + CHAMP_MAX_SIZE)

extern int		g_arg_tab[17][10];
extern int		g_opt_tab[17][6];
extern int		g_opt_tab2[4][10];

/*
**	create_del_errors.c
*/

t_car	*ft_create_car(int player_num, t_all *all, int pos);
t_all	*ft_create_all(int players_count);
void	ft_del_car(t_all *all, t_car *car);
void	ft_error_and_del_all(t_all *all, char *error_msg);

/*
**	work_with_memory.c
*/

int		ft_get_pos_of_memory(int pos);
int		ft_value_from_memory(char *memory, int pos, int size);
void	ft_value_in_memory(t_car *car, int pos, int value, int size);
int		ft_read_memory(t_all *all, char **argv, int argc);
int		ft_read_player(t_all *all, char *name, int number);

/*
**	operations.c
*/

void	ft_arifm_operations(t_car *car, int **arg);
void	ft_st_sti_lldi_ldi_cmd(t_car *car, int **arg);
void	ft_copy_fork(t_car *car, int new_pos);
void	ft_live(t_car *car, int value);
void	ft_modify_carry(t_car *car, int **arg);

/*
**	arg_for_operations.c
*/

int		ft_size_of_arg_by_type(int command, int arg_bit);
int		ft_arg_is_valid(t_car *car, int arg_bits, int arg_number);
void	ft_return_arg(t_car *car, int arg_bits, int **arg);
int		ft_parsing_of_args(t_car *car);
int		ft_valid_command(t_car *car);

/*
**	corewar.c
*/

void	ft_cycle(t_all *all);
void	ft_wait_or_do_command(t_car *car);
void	ft_choose_action(t_car *car);
void	ft_check_of_cars(t_all *all);

/*
**	validations.c
*/

void	ft_skip_flags(t_all *all, char ***argv, int *argc);
int		ft_check_errors(t_all *all, char *buf, int size);
int		ft_is_not_number(char **str);
int		ft_str_not_int_number(char *str);

/*
**	create_players.c
*/

void	ft_create_and_place_players(t_all *all, int argc, char **argv);
t_play	*ft_add_player(t_all *all, char *buf, int number);
void	ft_place_players_without_num(t_all *all);
int		ft_arr_of_number_players(t_all *all);
void	ft_place_prog_and_cars(t_all *all);

/*
**	print.c
*/

void	ft_print_champ(t_all *all);
void	ft_print_winner(t_all *all);
void	ft_print_dump(t_all *all, char *memory);
void	ft_print_byte(unsigned int byte);
void	ft_print_manual(void);

/*
**	windous.c
*/

t_win	*ft_create_windows(void);
void	ft_destroy_windows(t_win *wins);
void	ft_key_control(t_all *all);
void	ft_refresh_windows(t_all *all);

/*
**	incurses_colors.c
*/

void	set_color(void);
attr_t	ft_get_colour(t_all *all, int pos);
void	ft_init_ncurses(t_all *all);

/*
**	print_incurses.c
*/

void	ft_print_frame(WINDOW *frame);
void	ft_print_info(t_all *all);
void	ft_print_bonus(t_all *all);
void	ft_print_battlefield(t_all *all);
void	ft_print_picture(WINDOW *win, char *picture, int str_count);

#endif
