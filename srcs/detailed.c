/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   detailed.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 13:54:26 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:05:02 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		get_block_size(DIR *rep, const char *dir_name,
		const int a, int check)
{
	int				size;
	char			*new_path;
	char			*path;
	struct stat		info;
	struct dirent	*file;

	size = 0;
	while (rep && (file = readdir(rep)))
	{
		if (a || file->d_name[0] != '.')
		{
			new_path = ft_strjoin(dir_name, "/");
			path = ft_strjoin(new_path, file->d_name);
			ft_strdel(&new_path);
			if (lstat(path, &info) != -1)
				size += info.st_blocks;
			ft_strdel(&path);
			check = 1;
		}
	}
	if (rep)
		closedir(rep);
	return (check == 0 ? -1 : size);
}

static t_file	*get_file_list(char **files, t_max *max,
			const char *parent_path, const t_option options)
{
	int		i;
	t_file	*first;
	t_file	*curr;

	first = NULL;
	curr = NULL;
	i = 0;
	while (files[i])
	{
		if (!((!first && !(first = new_file(files[i],
			max, parent_path, options))) || (curr
				&& !(curr->next = new_file(files[i],
					max, parent_path, options)))))
			curr = first->next ? curr->next : first;
		i++;
	}
	if (max->minmaj && max->bytes < 9)
		max->bytes = 9;
	else
		max->bytes++;
	max->nb_files = i;
	return (first);
}

static t_file	*init_detailed_arg(t_max *max, char **files,
					const char *parent_path, const t_option options)
{
	max->path = 1;
	max->rights = 10;
	max->links_nb = 1;
	max->owner = 1;
	max->group = 1;
	max->bytes = 1;
	max->minmaj = 0;
	return (get_file_list(files, max,
		parent_path ? parent_path : NULL, options));
}

void			print_detailed_list(const t_option options,
		char **files, const char *parent_path)
{
	t_file	*l_files;
	t_max	max;
	char	*res;
	int		blck_size;

	l_files = init_detailed_arg(&max, files, parent_path, options);
	if (parent_path && (blck_size = get_block_size(opendir(parent_path),
		parent_path, options.a, 0)) == -1)
	{
		while (l_files)
			free_file(&l_files);
		return ;
	}
	if (parent_path && parent_path[0])
		ft_printf("total %d\n", blck_size);
	while (l_files)
	{
		if (!(res = (char *)malloc(31 + max.rights + max.links_nb + max.owner
			+ max.group + max.bytes + ft_strlen(l_files->path) + 1)))
			return ;
		add_file_to_buffer(res, max, l_files, options);
		ft_putstr(res);
		free_file(&l_files);
		ft_strdel(&res);
	}
}
