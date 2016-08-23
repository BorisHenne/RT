/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyco_internal_struct.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 13:38:44 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/23 13:48:19 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CYCO_INTERNAL_STRUCT_
# define _CYCO_INTERNAL_STRUCT_

typedef struct		s_intern
{
	t_vec			aa;
	t_vec			ab;
	double			ab2;
	t_vec			oxb;
	t_vec			v;
	t_vec			delta;
	double			x;
	double			y;
}					t_intern;

#endif
