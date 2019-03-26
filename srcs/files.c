/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 04:57:46 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:10:03 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	remove_file(char **files, int *types, const int cases)
{
	int		j;

	j = 0;
	while (files[j + 1])
	{
		ft_swap(&types[j], &types[j + 1]);
		ft_strswap(&files[j], &files[j + 1]);
		j++;
	}
	if (cases == 1)
		ft_strdel(&files[j]);
	else
		files[j] = NULL;
	types[j] = -1;
}

int			list_errorfiles(t_data *data)
{
	int		fd;
	int		check;

	check = 0;
	while (data->files[0] && data->types[0] == 0)
	{
		ft_printf("./ft_ls: %s: "
			, data->files[0][0] ? data->files[0] : "fts_open");
		fd = open(data->files[0], O_RDONLY);
		perror("");
		if (!data->files[0][0])
		{
			free_all(data, NULL);
			exit(EXIT_SUCCESS);
		}
		remove_file(data->files, data->types, 1);
		check = 2;
	}
	return (check);
}

static char	**init_file_list(t_data *data, int *index)
{
	char	**file_list;
	int		i;

	i = 0;
	while (data->files[i] && data->types[i] == 1)
		i++;
	if (i == 0)
		return (NULL);
	if (!(file_list = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	*index = 0;
	return (file_list);
}

t_sort		init_sort_arg(char *parent_name, int path_len, int nb, int type)
{
	t_sort	sort;

	sort.parent_name = parent_name;
	sort.path_len = path_len;
	sort.nb = nb;
	sort.type = type;
	return (sort);
}

int			list_argvfiles(t_data *data)
{
	int		i;
	char	**list_to_recurse;
	char	**list;
	int		check;
	t_sort	sort;

	check = 0;
	sort.path_len = 0;
	if (!(list = init_file_list(data, &i)))
		return (0);
	while (data->files[0] && data->types[0] != 2)
	{
		list[i++] = data->files[0];
		if ((int)ft_strlen(data->files[0]) > sort.path_len)
			sort.path_len = (int)ft_strlen(data->files[0]);
		remove_file(data->files, data->types, 2);
		check = 1;
	}
	list[i] = NULL;
	list_to_recurse = list;
	sort = init_sort_arg(NULL, sort.path_len + 1, i, 1);
	sort_files(data->options, &list, &sort, &list_to_recurse);
	print_file_list(data->options, build_flist(list, sort.path_len, i, NULL));
	free_dir(list, NULL, list_to_recurse);
	return (check);
}
