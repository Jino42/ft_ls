/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 11:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 00:05:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

# define NUM_TYPE 0
# define NUM_USR 1
# define NUM_GRP 4
# define NUM_OTH 7
# define NUM_R 0
# define NUM_W 1
# define NUM_X 2
# define ALL_R 7894898
/*
static void right_usr(unsigned long st_mode, char *tab)
{
	if ((st_mode & S_IRWXU) == S_IRWXU)
		*((unsigned int*)&tab[NUM_USR]) = ALL_R;
	else
	{
		if (st_mode & S_IRUSR)
			tab[NUM_USR + NUM_R] = 'r';
		if (st_mode & S_IWUSR)
			tab[NUM_USR + NUM_W] = 'w';
		if (st_mode & S_IXUSR)
			tab[NUM_USR + NUM_X] = 'x';
	}
	if (st_mode & S_ISUID)
		tab[NUM_USR + NUM_X] = 'S';
}

static void right_grp(unsigned long st_mode, char *tab)
{
	if ((st_mode & S_IRWXG) == S_IRWXG)
		*((unsigned int*)&tab[NUM_GRP]) = ALL_R;
	else 
	{
		if (st_mode & S_IRGRP)
			tab[NUM_GRP + NUM_R] = 'r';
		if (st_mode & S_IWGRP)
			tab[NUM_GRP + NUM_W] = 'w';
		if (st_mode & S_IXGRP)
			tab[NUM_GRP + NUM_X] = 'x';
	}
	if (st_mode & S_ISGID)
		tab[NUM_GRP + NUM_X] = 'S';
}

static void right_oth(unsigned long st_mode, char *tab)
{
	if ((st_mode & S_IRWXO) == S_IRWXO)
		*((unsigned int*)&tab[NUM_OTH]) = ALL_R;
	else
	{
		if (st_mode & S_IROTH)
			tab[NUM_OTH + NUM_R] = 'r';
		if (st_mode & S_IWOTH)
			tab[NUM_OTH + NUM_W] = 'w';
		if (st_mode & S_IXOTH)
			tab[NUM_OTH + NUM_X] = 'x';
	}
	if (st_mode & S_ISVTX)
		tab[NUM_OTH + NUM_X] = 't';
}

static void	type_of_file(unsigned long st_mode, char *tab)
{
	if (st_mode & S_IFREG)
		tab[NUM_TYPE] = '-';
	else if (st_mode & S_IFDIR)
		tab[NUM_TYPE] = 'd';
	else if (st_mode & S_IFLNK)
		tab[NUM_TYPE] = 'l';
	else if (st_mode & S_IFSOCK)
		tab[NUM_TYPE] = 's';
	else if (st_mode & S_IFBLK)
		tab[NUM_TYPE] = 'b';
	else if (st_mode & S_IFCHR)
		tab[NUM_TYPE] = 'c';
	else if (st_mode & S_IFIFO)
		tab[NUM_TYPE] = 'p';
}

typedef struct	s_elem
{
	char		right[11];
	size_t		size_bits;
	size_t		last_change;
	size_t		nb_nlink;
	char		*p_name;
	char		*g_name;
}				t_elem;

	(void)argc;
	void	*ptr;
	struct dirent *c;
	struct stat buf;
	struct passwd *passwd;
	struct group *group;
	char	tab[11];
	char	path[20];

	ft_bzero(&tab, sizeof(char) * 11);
	ft_bzero(&path, sizeof(char) * 20);
	ptr = opendir(argv[1]);
	if (ptr)
	{
		ft_strcpy(path, argv[1]);
		while ((c = readdir(ptr)))
		{
			ft_printf("Nombre de lien : %i\n", buf.st_nlink);
			passwd = getpwuid(buf.st_uid);
			group = getgrgid(buf.st_gid);
			ft_printf("Propriétaire : %s\n", passwd->pw_name);
			ft_printf("Nom du groupe : %s\n", group->gr_name);
			ft_printf("Taille %li\n", buf.st_size);
			ft_printf("%.12s\n", ctime(&buf.st_atime) + 4);
			ft_printf("Time : %li\n", buf.st_atime);
		}
		closedir(ptr);
	}
	else
		perror("ls :  ");
*/

void		print_elem(t_env *e)
{
	t_list *l;
	t_list *save;

	l = e->dir;
	ft_printf("\033[31mIfdir :\n\033[0m");
	while (l)
	{
		ft_printf("%s\n", ((char*)(l->content)));
		save = l->next;
		l = save;
	}
	l = e->file;
	ft_printf("\033[31mIffile :\n\033[0m");
	while (l)
	{
		ft_printf("%s\n", ((char*)(l->content)));
		save = l->next;
		l = save;
	}
	l = e->not_here;
	ft_printf("\033[31mNote here : \n\033[0m");
	while (l)
	{
		ft_printf("%s\n", ((char*)(l->content)));
		save = l->next;
		l = save;
	}
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		i;

	ft_bzero(&e, sizeof(t_env));
	pars_arg(&e, argc, argv, &i);
	ls_recup_file_from_arg(&e);

	print_elem(&e);
//	rec = ft_lst_remove_index(&e.not_here, index);
//	if (rec)
//		ls_free_temp(&rec);
	ls_free_temp(&e.temp);
	ls_free_temp(&e.file);
	ls_free_temp(&e.not_here);
	ls_free_temp(&e.dir);
//	ft_bzero(&e, sizeof(t_env));
//	while (1);
	return (0);
}
