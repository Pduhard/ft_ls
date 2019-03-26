/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 04:35:44 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 11:19:32 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	free_all(t_data *data, char **str)
{
	int		i;

	i = 0;
	if (str)
		ft_strdel(str);
	while (data->files[i])
		ft_strdel(&data->files[i++]);
	free(data->files);
	free(data->fds);
	free(data->types);
	free(data);
}

void	free_file(t_file **file)
{
	t_file	*next;

	next = (*file)->next;
	ft_strdel(&(*file)->rights);
	ft_strdel(&(*file)->owner);
	ft_strdel(&(*file)->group);
	ft_strdel(&(*file)->date);
	ft_strdel(&(*file)->path);
	free((*file));
	(*file) = next;
}

void	free_dir(char **file_list, char **new_path, char **list_to_recurse)
{
	int		i;

	i = 0;
	while (file_list[i])
		ft_strdel(&file_list[i++]);
	if (list_to_recurse != file_list)
		free(list_to_recurse);
	free(file_list);
	if (new_path)
		ft_strdel(new_path);
}
