/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   date.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 12:50:20 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 12:54:24 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*get_years_date(char *full_date)
{
	char	*years;
	char	*date_tmp;
	int		tmp;
	int		start;

	start = ft_strrchr(full_date, ' ') - full_date;
	years = ft_strsub(full_date, start, ft_strlen(full_date) - start);
	ft_strfsub(&years, 0, ft_strichr(years, '\n'));
	date_tmp = ft_strsub(full_date, 0, ft_strrchr(full_date, ':') - full_date);
	full_date = date_tmp;
	date_tmp = ft_strsub(full_date, 0, ft_strrchr(full_date, ' ') - full_date);
	ft_strdel(&full_date);
	full_date = date_tmp;
	tmp = ft_strichr(full_date, ' ') + 1;
	ft_strfsub(&full_date, tmp, ft_strlen(full_date) - tmp);
	full_date = ft_strfjoin(full_date, ft_strdup(" "));
	full_date = ft_strfjoin(full_date, years);
	return (full_date);
}

char		*get_date(const time_t m_time, const t_option options,
				const time_t a_time, const time_t b_time)
{
	char	*full_date;
	int		tmp;
	time_t	t;

	t = m_time;
	if (options.u || options.maj_u)
		t = options.u ? a_time : b_time;
	full_date = ctime(&t);
	if (ft_abs(time(NULL) - t) > 15770000)
		return (get_years_date(ctime(&t)));
	else
	{
		full_date = ft_strsub(full_date,
			0, ft_strrchr(full_date, ':') - full_date);
		tmp = ft_strichr(full_date, ' ') + 1;
		ft_strfsub(&full_date, tmp, ft_strlen(full_date) - tmp);
	}
	return (full_date);
}
