/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 06:05:47 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 19:12:25 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_part		*create_part(void)
{
	t_part *part;

	if (!(part = (t_part *)malloc(sizeof(t_part))))
		return (NULL);
	part->type = NONE;
	part->n_elems = 0;
	part->elems = NULL;
	part->sub_parts = NULL;
	part->next = NULL;
	return (part);
}

t_elem		*create_elem(void)
{
	t_elem	*elem;

	if (!(elem = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	elem->name = NULL;
	elem->n_values = 0;
	elem->values = 0;
	elem->next = NULL;
	return (elem);
}

void		free_elem(t_elem **elem)
{
	t_elem	*tmp;

	while (*elem)
	{
		tmp = (*elem);
		free(tmp->name);
		free_tab(tmp->values);
		*elem = (*elem)->next;
		free(tmp);
		tmp = NULL;
	}
}

void		free_part(t_part **part)
{
	t_part	*tmp;
	t_part	*tmp2;

	while (*part)
	{
		tmp = *part;
		free_elem(&tmp->elems);
		while (tmp->sub_parts)
		{
			tmp2 = tmp->sub_parts;
			free_elem(&tmp2->elems);
			tmp->sub_parts = tmp->sub_parts->next;
			free(tmp2);
			tmp2 = NULL;
		}
		*part = (*part)->next;
		free(tmp);
		tmp = NULL;
	}
}
