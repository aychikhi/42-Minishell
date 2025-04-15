/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:03:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/15 17:32:07 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokeniser(char	*input)
{
	t_token	*tokens; //the head
	t_token	*last;// pointer to the last token in the list
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '&' && input[i + 1] == '&')
		{
			add_token(&tokens, &last, TOKEN_AND, "&&");
			i += 2; 
		}
		else if (input[i] == '|' && input[i+1] == '|') {
            add_token(&tokens, &last, TOKEN_OR, "||");
            i += 2;
        }
        else if (input[i] == '|') {
            add_token(&tokens, &last, TOKEN_PIPE, "|");
            i++;
        }
        else if (input[i] == '(') {
            add_token(&tokens, &last, TOKEN_LPAREN, "(");
            i++;
        }
        else if (input[i] == ')') {
            add_token(&tokens, &last, TOKEN_RPAREN, ")");
            i++;
        }
	}
}
