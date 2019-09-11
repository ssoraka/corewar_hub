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

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include "libft.h"
# include <ncurses.h>
# include "op.h"



#define DUMP_LENGTH 64

/*
**	for visualisation
*/
#define DELAY 8
#define DELAY_BOLD 100
#define BYTE_IN_STRING 64
#define BATTLEFIELD_Y 2
#define BATTLEFIELD_X 4
#define BATTLEFIELD_L (BYTE_IN_STRING * 3)
#define BATTLEFIELD_H (MEM_SIZE / 64)
#define INFO_X (BATTLEFIELD_L + 2 * BATTLEFIELD_X + 2)
#define INFO_Y BATTLEFIELD_Y
#define INFO_L (40)
#define INFO_H (BATTLEFIELD_H)
#define FRAME_H (BATTLEFIELD_H + BATTLEFIELD_Y * 2)
#define FRAME_L (INFO_X + INFO_L + BATTLEFIELD_X)

/*
**	for visualisation
*/
#define ONE_STEP 1
#define MIN_CODE (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
#define MAX_CODE (MIN_CODE + CHAMP_MAX_SIZE)


#define ARG_MASK 0b00000011
#define T_REG			1
#define T_DIR			2
#define T_IND			4
#define T_REG_DIR		(T_REG + T_DIR)
#define T_REG_IND		(T_REG + T_IND)
#define T_DIR_IND		(T_DIR + T_IND)
#define T_REG_DIR_IND	(T_REG + T_DIR + T_IND)



#define CAPYBARA "\
                                      \n\
             **         **            \n\
            *w***      *w* **         \n\
            **  *****   *****         \n\
             ww*             ***      \n\
            *w*  w***          *ww    \n\
          *w*   *w* ***        *w *   \n\
        *w*      ***             **   \n\
      *ww*                         ** \n\
    *ww*                  *www*  **w**\n\
  *www*                   *wwwwwwwwwww\n\
*** **                     ww* *ww**w*\n\
                            **  *w* * \n\
                                *w*   \n\
                                *w  * \n\
                                *w  * \n\
                                *w ** \n\
                        **     *wwww* \n\
                           *******    \n"

#define SCHOOL_21 "\
##################      ######\n\
##################      ######\n\
##################      ######\n\
                  ######      ######\n\
                  ######      ######\n\
                  ######      ######\n\
      ############            ######\n\
      ############            ######\n\
      ############            ######\n\
######                        ######\n\
######                        ######\n\
######                        ######\n\
      ##################      ######\n\
      ##################      ######\n\
      ##################      ######\n"

#define CORE_WAR "\
\n\
 ####  ###  ####  #####     \n\
#     #   # #   # #         \n\
#     #   # ####  #####     \n\
#     #   # #  #  #         \n\
 ####  ###  #   # #####     \n\
                            \n\
            #           #  #   #### \n\
             #         #  # #  #   #\n\
              #   #   #  ##### #### \n\
               # # # #   #   # #  # \n\
                #   #    #   # #   #\n"

#define MANUAL "\
#### EXSAMPLE #########################################################\n\
	./corewar [-a][-dump N][-vis] [[-n number] champion1.cor] ...\n\
#### HELP #############################################################\n\
	-a        : Prints output from \"aff\" (Default is to hide it)\n\
	-dump N   : Dumps memory after N cycles then exits\n\
	-vis      : Ncurses output mode\n\
	-n number : Sets the number of the next player\n\
#######################################################################\n"


#include "ft_corewar_struct.h"

void	ft_putnbr_end(int num);
t_car	*ft_create_car(int player_num, t_all *all, int pos);
t_all	*ft_create_all(int players_count);
void	ft_print_byte(unsigned int byte);
void	ft_print_memory(t_all *all);
int		ft_read_memory(char *name, char *memory);
int		ft_get_pos_of_memory(int pos);
int		ft_value_from_memory(char *memory, int pos, int size);
void	ft_value_in_memory(t_car *car, int pos, int value, int size);
void	ft_copy_fork(t_car *car, int new_pos);
void	ft_live(t_car *car, int value);
int		ft_size_of_arg_by_type(int command, int arg_bit);
int		ft_arg_is_valid(t_car *car, int arg_bits, int arg_number);
void	ft_return_arg(t_car *car, int arg_bits, int **arg);
int		ft_parsing_of_args(t_car *car);
int		ft_valid_command(t_car *car);
void	ft_modify_carry(t_car *car, int **arg);
void	ft_arifm_operations(t_car *car, int **arg);
void	ft_st_sti_lldi_ldi_cmd(t_car *car, int **arg);
void	ft_print_arg(t_car *car, int *arg, int cmd, int arg_num);
void	ft_print_operation(t_car *car, int **arg);
void	ft_wait_or_do_command(t_car *car);
void	ft_choose_action(t_car *car);
void	ft_del_car(t_all *all, t_car *car);
void	ft_check_of_cars(t_all *all);
void	ft_cycle(t_all *all);
void	ft_destroy_windows(t_win *wins);
void	ft_error(t_all *all, char *error_msg);
int		ft_read_memory(char *name, char *memory);
t_play	*ft_add_player(t_all *all, char *buf, int number);
int		ft_check_errors(t_all *all, char *buf, int size);
int		ft_read_player(t_all *all, char *name, int number);
int		ft_is_not_number(char **str);
int		ft_str_not_int_number(char *str);
int		ft_check_flags(t_all *all, char *argv, char *flag);
void	ft_skip_flags(t_all *all, char ***argv, int *argc);
int		ft_read_memory2(t_all *all, char **argv, int argc);
void	ft_place_players_without_num(t_all *all);
void	ft_elevate_and_renum_players(t_all *all);
int		ft_arr_of_number_players(t_all *all);
void	ft_place_prog_and_cars(t_all *all);
void	ft_print_champ(t_all *all);
void	ft_print_winner(t_all *all);
void	ft_print_dump(t_all *all, char *memory);
t_win	*ft_create_windows(void);
void	set_color(void);
void	ft_init_ncurses(t_all *all);
void	ft_print_info(t_all *all);
void	ft_print_bonus(t_all *all);
attr_t	ft_get_colour(t_all *all, int pos);
void	ft_print_battlefield(t_all *all);
void	ft_print_frame(WINDOW *frame);
void	ft_key_control(t_all *all);
void	ft_refresh_windows(t_all *all);
void	ft_create_and_place_players(t_all *all, int argc, char **argv);

#endif
