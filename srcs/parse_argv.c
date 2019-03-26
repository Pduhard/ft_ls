/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_argv.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 07:04:12 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 14:45:21 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				check_comp(const char *str1, const char *str2, const int opt_f)
{
	if (opt_f)
		return (1);
	return (ft_strcmp(str1, str2) <= 0 ? 1 : 0);
}

void			add_file(char *file, int type,
		t_data *data, const t_option options)
{
	int		j;

	j = 0;
	while (data->files[j] && data->types[j] < type)
		j++;
	while (data->files[j] && data->types[j] == type
			&& check_comp(data->files[j], file, options.f))
		j++;
	while (data && data->files[j])
	{
		ft_strswap(&data->files[j], &file);
		ft_swap(&type, &data->types[j++]);
	}
	data->files[j] = file;
	data->types[j] = type;
}

void			sort_argv(char **argv, int i, t_data *data)
{
	struct stat	info;

	while (argv[i])
	{
		if (lstat(argv[i], &info) == -1)
			add_file(ft_strdup(argv[i]), 0, data, data->options);
		else if ((info.st_mode & S_IFMT) == S_IFDIR)
			add_file(ft_strdup(argv[i])
				, data->options.d ? 1 : 2, data, data->options);
		else
			add_file(ft_strdup(argv[i]), 1, data, data->options);
		i++;
	}
}
