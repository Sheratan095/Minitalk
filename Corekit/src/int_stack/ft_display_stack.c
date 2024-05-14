/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/14 16:10:16 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	ft_display_stack(t_stack *stack)
{
	t_stack_node	*temp;

	if (ft_is_stack_empty(stack))
	{
		ft_printf("Stack is empty\n");
		return ;
	}
	temp = stack->head;
	while (temp != NULL)
	{
		ft_printf("%i\n", temp->value);
		temp = temp->next;
	}
}
