/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/27 09:24:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	pars_file(t_env *e, int argc, char **argv, int *i)
{
	t_elem elem;

	ft_bzero(&elem, sizeof(t_elem));
	while (*i < argc)
	{
		ft_lstinsert_alphabet(&e->temp, ft_lstnew(argv[*i],
						ft_strlen(argv[*i]) + 1), e->flag & FLAG_RV);
		(*i)++;
		e->nb_arg++;
	}
}

static int	ft_strallcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (1)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (1);
}

static void	pars_flag(t_env *e, int argc, char **argv, int *i)
{
	int	i_in;
	int	option_;

	option_ = 0;
	while (*i < argc && argv[*i][0] == '-' &&
			argv[*i][1] != '\0')
	{
		if (!ft_strallcmp(argv[*i], "--"))
		{
			option_ = 1;
			return ;
		}
		else
		{
			i_in = 1;
			while (argv[*i][i_in])
			{
				if (argv[*i][i_in] == 'l')
					e->flag |= FLAG_L;
				else if (argv[*i][i_in] == 'R')
					e->flag |= FLAG_R;
				else if (argv[*i][i_in] == 'a')
					e->flag |= FLAG_A;
				else if (argv[*i][i_in] == 't')
					e->flag |= FLAG_T;
				else if (argv[*i][i_in] == 'r')
					e->flag |= FLAG_RV;
				else if (argv[*i][i_in] == '1')
					e->flag |= (1<<8);
				else
					ft_error("usage : ls [-Rlart] [file ...]\n");
				i_in++;
			}
		}
		(*i)++;
	}
}

void		pars_arg(t_env *e, int argc, char **argv, int *i)
{
	*i = 1;
	pars_flag(e, argc, argv, i);
	pars_file(e, argc, argv, i);
}
