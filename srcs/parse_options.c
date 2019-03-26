/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_options.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 08:18:16 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 10:28:17 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		add_option(t_option *options, const char opt)
{
	options->maj_r |= opt == 'R' ? 1 : 0;
	if (opt == 'U')
	{
		options->maj_u |= 1;
		options->u &= 0;
	}
	options->maj_g |= opt == 'G' ? 1 : 0;
	options->a |= opt == 'a' ? 1 : 0;
	options->l |= opt == 'l' ? 1 : 0;
	options->r |= opt == 'r' ? 1 : 0;
	options->t |= opt == 't' ? 1 : 0;
	options->f |= opt == 'f' ? 1 : 0;
	options->d |= opt == 'd' ? 1 : 0;
	if (opt == 'u')
	{
		options->u |= 1;
		options->maj_u &= 0;
	}
	options->g |= opt == 'g' ? 1 : 0;
	options->a |= options->f;
	options->l |= options->g;
}

static t_option	init_options(int *i, char **argv, int *err_opt)
{
	t_option	options;
	int			j;

	ft_bzero((void *)&options, sizeof(t_option));
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1])
	{
		j = 1;
		if (!ft_strcmp(argv[*i], "--") && (++(*i)))
			return (options);
		while (argv[*i][j])
		{
			if (!(ft_strchr(SUPP_FLAGS, argv[*i][j])))
			{
				ft_printf("./ft_ls: illegal option -- %c\n%s"
					, argv[*i][j], USAGE);
				*err_opt = 1;
				return (options);
			}
			add_option(&options, argv[*i][j++]);
		}
		(*i)++;
	}
	return (options);
}

static int		alloc_data_content(t_data *data, const int i, const int argc)
{
	int		j;

	j = 0;
	if (!(data->files = (char **)malloc(sizeof(char *) * (argc - i + 2)))
		|| !(data->fds = (int *)malloc(sizeof(int) * (argc - i + 1)))
			|| !(data->types = (int *)malloc(sizeof(int) * (argc - i + 1))))
		return (0);
	while (j < argc - i)
	{
		data->files[j] = NULL;
		data->types[j++] = -1;
	}
	data->files[j] = NULL;
	return (1);
}

t_data			*init_data(const int argc, char **argv)
{
	t_data	*data;
	int		i;
	int		err_opt;

	i = 1;
	err_opt = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->options = init_options(&i, argv, &err_opt);
	if (err_opt)
	{
		free(data);
		return (NULL);
	}
	alloc_data_content(data, i, argc);
	sort_argv(argv, i, data);
	if (data->files[0] == NULL)
	{
		add_file(ft_strdup("."), 2, data, data->options);
		data->files[1] = NULL;
	}
	return (data);
}
