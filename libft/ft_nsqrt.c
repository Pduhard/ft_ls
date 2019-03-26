/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nsqrt.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/28 06:30:02 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:20:25 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

double	ft_nsqrt(double n, double prec, int pow)
{
	double	min;
	double	max;
	double	test;
	double	pow_val;

	min = -46340.0;
	max = 46341.0;
	test = (max - min) / 2.0 + min;
	pow_val = ft_fpow(test, pow);
	while (pow_val != n)
	{
		if (pow_val > n)
			max = test;
		if (pow_val < n)
			min = test;
		if (max - min < prec)
			return (max);
		test = (max - min) / 2.0 + min;
		pow_val = ft_fpow(test, pow);
	}
	return (test);
}
