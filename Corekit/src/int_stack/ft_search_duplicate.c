/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_duplicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/14 16:10:16 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_bool	ft_search_duplicate(t_stack *stack)
{
	t_stack_node	*tmp;

	if (ft_is_stack_empty(stack))
		return (false);
	tmp = stack->head;
	while (tmp)
	{
		if (ft_stack_contains(stack, tmp->value))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
