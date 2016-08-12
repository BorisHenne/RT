/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:58:44 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/12 02:05:48 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_elem		*parse_elem(char *s, t_elem *next)
{
	char	**name;
	char	**values;
	t_elem	*elem;

	if (!(elem = create_elem()))
		return (NULL);
	if (!(name = ft_strsplit(s, ':')))
		return (NULL);
	if (arr_len(name) != 2)
		return (NULL);
	elem->name = ft_strtrim(name[0]);
	if (!(values = ft_strsplit(name[1], ',')))
		return (NULL);
	if ((elem->n_values = arr_len(values)) <= 0)
		return (NULL);
	if (!(elem->values = cpy_carray(values)))
		return (NULL);
	elem->next = next;
	free_tab(name);
	free_tab(values);
	return (elem);
}

int			init_elem(t_part *part, char *tmp)
{
	if (part->sub_parts == NULL)
	{
		if (!(part->elems = parse_elem(tmp, part->elems)))
			return (0);
	}
	else
	{
		part->sub_parts->elems = parse_elem(tmp, part->sub_parts->elems);
		if (!part->sub_parts->elems)
			return (0);
	}
	return (1);
}

int			init_part(t_part *new_part, char *tmp)
{
	t_part *tmp2;

	if (new_part->type == NONE)
		new_part->type = find_type(tmp);
	else if (!ft_strstr(tmp, "option"))
	{
		if (!(tmp2 = create_part()))
			return (0);
		tmp2->type = find_type(tmp);
		tmp2->next = new_part->sub_parts;
		new_part->sub_parts = tmp2;
	}
	return (1);
}

int			set_part(char **array, t_part *new_part)
{
	char	*tmp;
	int		i;

	i = -1;
	while (array[++i])
	{
		if (!(tmp = ft_strtrim(array[i])))
			return (0);
		if (ft_strchr(tmp, '}'))
		{
			if (!init_elem(new_part, tmp))
			{
				return (0);
			}
		}
		else if (ft_strchr(tmp, ':'))
		{
			if (!init_part(new_part, tmp))
			{
				ft_putendl("okok");
				return (0);
			}
		}
		free(tmp);
		tmp = NULL;
	}
	return (1);
}

t_part		*parse_scop(char *scop)
{
	t_part	*new_part;
	char	**array;

	if (!ft_strchr(scop, ':'))
	{
		ft_putendl("Empty Object");
		return (NULL);
	}
	if (!(new_part = create_part()))
	{
		return (NULL);
	}
	if (!(array = ft_strsplit(scop, '{')))
	{
		return (NULL);
	}
	if (!set_part(array, new_part))
	{
		ft_putendl("Empty Object");
		return (NULL);
	}
	free_tab(array);
	return (new_part);
}
