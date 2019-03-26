/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 07:32:20 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:13:23 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	loop_on_dir(t_data *data, const int check)
{
	int		i;
	int		max_len;
	char	**tmp;
	DIR		*rep;
	t_sort	sort;

	max_len = 0;
	i = 0;
	rep = NULL;
	while (data->files[i])
		if ((int)ft_strlen(data->files[i++]) > max_len)
			max_len = (int)ft_strlen(data->files[i - 1]);
	sort = init_sort_arg(NULL, max_len + 1, i, 0);
	sort_files(data->options, &data->files, &sort, &tmp);
	i = 0;
	while (data->files[i])
	{
		if (i != 0 || (check & 1))
			write(1, "\n", 1);
		if (i != 0 || check || data->files[1])
			ft_printf("%s:\n", data->files[i]);
		display_dir(data->files[i], data->options, rep);
		i++;
	}
}

int			main(int argc, char **argv)
{
	int			i;
	int			check;
	int			max_len;
	t_data		*data;

	i = -1;
	check = 0;
	data = NULL;
	if (!(data = init_data(argc, argv)))
		return (0);
	check |= list_errorfiles(data);
	i = 0;
	max_len = 0;
	check |= list_argvfiles(data);
	loop_on_dir(data, check);
	free_all(data, NULL);
	return (0);
}
