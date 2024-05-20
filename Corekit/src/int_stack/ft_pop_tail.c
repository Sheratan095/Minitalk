/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_tail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/20 17:35:41 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	ft_pop_tail(t_stack *stack)
{
	t_stack_node	*temp;
	int				result;

	if (ft_is_stack_empty(stack))
		return (0);
	if (stack->length == 1)
		return (ft_pop(stack));
	temp = stack->tail;
	result = temp->value;
	stack->tail = stack->tail->prev;
	stack->tail->next = NULL;
	free(temp);
	stack->length--;
	return (result);
}
