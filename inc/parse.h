/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:27:54 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/07 01:47:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <scene.h>
# include <fcntl.h>

typedef struct		s_elem
{
	char			*name;
	int				n_values;
	char			**values;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_part
{
	int				type;
	int				n_elems;
	t_elem			*elems;
//	struct s_part	*sub_parts;
	struct s_part	*next;
}					t_part;

t_scene		*parse(char *file_name);

#endif
