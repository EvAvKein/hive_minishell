/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/10 18:17:22 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.c"

int main()
{
	bool	in_quotes[2] = {false, false};

	printf("%d\n", is_skippable_quote(in_quotes, '\'', false));

	return (0);
}
