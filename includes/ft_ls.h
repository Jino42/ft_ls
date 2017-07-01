/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/30 10:52:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/includes/ft_printf.h"
#include <sys/stat.h> 
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

# define NUM_TYPE 0
# define NUM_USR 1
# define NUM_GRP 4
# define NUM_OTH 7
# define NUM_R 0
# define NUM_W 1
# define NUM_X 2
# define ALL_R 7894898

# define MAX_YEARS 253375970400
# define PRINT_DATE 15778800

# define FLAG_L (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_A (1 << 3)
# define FLAG_RV (1 << 4)
# define FLAG_T (1 << 5)

# define P_FILE 0
# define P_DIR 1

typedef struct	s_size_m
{
	size_t p_max;
	size_t g_max;
	size_t size_max;
	size_t nlink_max;
	size_t years_max;
	size_t total_blocks;
	size_t minor_max;
	size_t major_max;
}				t_size_m;

typedef struct	s_elem
{
	char		right;
	char		*path;
	char		mode[11];
	size_t		ind_curf;
	size_t		size;
	time_t		atime;
	time_t		mtime;
	time_t		ctime;
	size_t		nlink;
	size_t		blocks;
	char		*p_name;
	char		*g_name;
	char		*r_lnk;
	dev_t		st_dev;
}				t_elem;

typedef struct	s_env
{
	int			flag;
	int			nb_arg;
	int			cur_dir;
	t_list		*file;
	t_list		*dir;
	t_list		*temp;
	t_list		*not_here;
	t_list		*temp_dir;
}				t_env;

t_list			*ft_lst_remove_index(t_list **lst, size_t index);
t_list			*ft_lst_remove(t_list **lst, t_list *remove);
void			ft_lstinsert_alphabet(t_list **lst, t_list *new, int reverse);
void			ft_lstinsert_time(t_list **lst, t_list *new, int reverse);


int				pars_arg(t_env *e, int argc, char **argv, int *i);
int				ls_recup_file(t_env *e, int init);
int				ls_get_dir(t_env *e, t_elem *elem);
t_list			*ls_stat_to_list(t_env *e, struct stat buff, char *path);

void			ls_type_and_file_right(t_elem *elem, ssize_t st_mode, struct stat *ptr_buff);
int				ls_loop(t_env *e);
void			ls_print(t_env *e, t_list *lst, int dir);

void			ls_free_temp(t_list **lst);
void			ls_free_elem(t_list	**lst);

#endif
