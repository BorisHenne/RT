/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:53:34 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 01:38:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _NODE_H
# define _NODE_H

#define LIGHT		0
#define CAMERA		1
#define SPHERE		2
#define CYLINDER	3
#define PLANE		4

typedef struct		s_node
{
	int				type;
	char			*name;
	void			*data;
	struct s_node	*next;
}					t_node;

t_node	*init_node(int type, void *data, char *name);
void	node_add(t_node **node, t_node *new);

#endif
