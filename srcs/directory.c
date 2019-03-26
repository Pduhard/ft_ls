/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   directory.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 02:31:12 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 14:41:43 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	print_dir_error(const char *dir_name)
{
	char	*tmp;
	int		start;
	int		len;

	if (ft_strchr(dir_name, '/'))
	{
		start = ft_strrchr(dir_name, '/') - dir_name + 1;
		len = ft_strlen(dir_name) - (ft_strrchr(dir_name, '/') - dir_name);
		tmp = ft_strsub(dir_name, start, len);
		ft_fdprintf(2, "./ft_ls: %s: ", tmp);
		ft_strdel(&tmp);
	}
	else
		ft_fdprintf(2, "./ft_ls: %s: ", dir_name);
	perror("");
}

static int	get_max_path_len(DIR *rep, const t_option options, int *i)
{
	struct dirent	*file;
	int				max_length;

	max_length = 0;
	*i = 0;
	while ((file = readdir(rep)))
		if ((options.a || file->d_name[0] != '.') && (++(*i))
				&& (int)ft_strlen(file->d_name) > max_length)
			max_length = (int)ft_strlen(file->d_name);
	closedir(rep);
	return (max_length);
}

static char	**init_file_list(const char *dir_name,
		const int len, const t_option options)
{
	char			**file_list;
	int				i;
	DIR				*rep;
	struct dirent	*file;

	if (!(rep = opendir(dir_name))
			|| !(file_list = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while ((file = readdir(rep)))
		if ((options.a || file->d_name[0] != '.') && file->d_name[0])
			file_list[i++] = ft_strdup(file->d_name);
	file_list[i] = NULL;
	closedir(rep);
	return (file_list);
}

static void	recurse_on_dir(const t_option options, char **file_list,
				const char *new_path, const int nb)
{
	int			start;
	DIR			*rep;
	struct stat	info;
	char		*path;

	start = 0;
	rep = NULL;
	while (start != nb)
	{
		path = ft_strjoin(new_path, file_list[start]);
		if (!lstat(path, &info))
		{
			if (file_list[start][0] && ft_strcmp(file_list[start], ".")
				&& ft_strcmp(file_list[start], "..")
					&& (info.st_mode & S_IFMT) == S_IFDIR)
			{
				ft_printf("\n%s:\n", path);
				display_dir(path, options, rep);
			}
		}
		ft_strdel(&path);
		start++;
	}
}

void		display_dir(const char *dir_name, const t_option options, DIR *rep)
{
	char			**file_list;
	int				i;
	char			*new_path;
	char			**list_to_recurse;
	t_sort			sort;

	if (!(rep = opendir(dir_name)))
		print_dir_error(dir_name);
	else
	{
		sort.path_len = get_max_path_len(rep, options, &i);
		if (!(file_list = init_file_list(dir_name, i, options)))
			return ;
		new_path = (dir_name && dir_name[ft_strlen(dir_name) - 1] != '/')
			? ft_strjoin(dir_name, "/") : ft_strdup(dir_name);
		list_to_recurse = file_list;
		sort = init_sort_arg(new_path, sort.path_len + 1, i, 1);
		sort_files(options, &file_list, &sort, &list_to_recurse);
		print_file_list(options,
			build_flist(file_list, sort.path_len, i, new_path));
		if (options.maj_r)
			recurse_on_dir(options, list_to_recurse, new_path, i);
		free_dir(file_list, &new_path, list_to_recurse);
	}
}
