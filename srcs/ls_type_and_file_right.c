/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_type_and_file_right.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:59:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 07:41:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** #define __S_ISTYPE(mode, mask)  (((mode) & __S_IFMT) == (mask))
** ...
** #define S_ISREG(mode)    __S_ISTYPE((mode), __S_IFREG)
*/

static void	right_usr(ssize_t st_mode, char *tab)
{
	if (S_IXUSR & st_mode)
		tab[NUM_USR + NUM_X] = 'x';
	if (S_IWUSR & st_mode)
		tab[NUM_USR + NUM_W] = 'w';
	if (S_IRUSR & st_mode)
		tab[NUM_USR + NUM_R] = 'r';
	if (S_ISUID & st_mode)
		tab[NUM_USR + NUM_X] = 'S';
}

static void	right_grp(ssize_t st_mode, char *tab)
{
	if (S_IXGRP & st_mode)
		tab[NUM_GRP + NUM_X] = 'x';
	if (S_IWGRP & st_mode)
		tab[NUM_GRP + NUM_W] = 'w';
	if (S_IRGRP & st_mode)
		tab[NUM_GRP + NUM_R] = 'r';
	if (S_ISGID & st_mode)
		tab[NUM_GRP + NUM_X] = 'S';
}

static void	right_oth(ssize_t st_mode, char *tab)
{
	if (S_IXOTH & st_mode)
		tab[NUM_OTH + NUM_X] = 'x';
	if (S_IWOTH & st_mode)
		tab[NUM_OTH + NUM_W] = 'w';
	if (S_IROTH & st_mode)
		tab[NUM_OTH + NUM_R] = 'r';
	if (S_ISVTX & st_mode)
		tab[NUM_OTH + NUM_X] = 't';
}

static void	type_of_file(ssize_t st_mode, char *tab)
{
	if ((st_mode & S_IFMT) == S_IFREG)
		tab[NUM_TYPE] = '-';
	else if ((st_mode & S_IFMT) == S_IFDIR)
		tab[NUM_TYPE] = 'd';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		tab[NUM_TYPE] = 'l';
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		tab[NUM_TYPE] = 's';
	else if ((st_mode & S_IFMT) == S_IFBLK)
		tab[NUM_TYPE] = 'b';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		tab[NUM_TYPE] = 'c';
	else if ((st_mode & S_IFMT) == S_IFIFO)
		tab[NUM_TYPE] = 'p';
}

void		ls_type_and_file_right(t_elem *elem, ssize_t st_mode,
											struct stat *ptr_buff)
{
	struct stat	buff;
	char		*temp;

	lstat(elem->path, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFLNK)
	{
		if (!(temp = (char *)ft_memalloc(buff.st_size + 1)))
			exit(0);
		if (!(readlink(elem->path, temp, buff.st_size + 1)))
		{
			perror("readlink");
			exit(0);
		}
		elem->r_lnk = ft_sprintf(" -> %s", temp);
		elem->mode[NUM_TYPE] = 'l';
		st_mode = buff.st_mode;
		*ptr_buff = buff;
	}
	else
		type_of_file(st_mode, elem->mode);
	right_usr(st_mode, elem->mode);
	right_grp(st_mode, elem->mode);
	right_oth(st_mode, elem->mode);
}
