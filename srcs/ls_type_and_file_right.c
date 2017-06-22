/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_type_and_file_right.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:59:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/23 00:00:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void		ls_type_and_file_right(unsigned long st_mode, char *tab)
{
	type_of_file(st_mode, tab);
	right_usr(st_mode, tab);
	right_grp(st_mode, tab);
	right_oth(st_mode, tab);
}
