/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 10:39:30 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @file An alternate executable/main with tests for the entire parsing stage
 * (comparing the user input to the expected parsed result).
 * 
 */

static bool	compare(char *input, char *expected)
{
	if (!input || !expected)
	{
		printf("Found falsey pointers in test!\n");
		return (0);
	}
	size_t s1_len = ft_strlen(input);
	size_t s2_len = ft_strlen(expected);
	size_t largest_len = s1_len > s2_len ? s1_len : s2_len;
	return (ft_strncmp(input, expected, largest_len));
}

/**
 * 
 * Runs `parsing` with the `input` and compares the parsed result to `expected`.
 * 
 */
static void	test(t_shell *shell, char *input, t_node expected)
{
	int		i = 0;
	bool	same;

	printf("\ninput: %s\n", input);
	parsing(shell, input);
	
	if (expected.argc != shell->nodes->argc)
	{
		printf("\e[1;31mWrong argc! got %d when expecting %d\e[0m\n",
			shell->nodes->argc,
			expected.argc);
		return ;
	}
	else
		printf("argc: %d\n", shell->nodes->argc);
	
	while (i < expected.argc)
	{
		same = !compare(shell->nodes->argv[i], expected.argv[i]);
		if (!same)
		{
			printf("\e[1;31mFound mismatch!\e[0m\n");
			printf("expected at i-%d: %s\n", i, expected.argv[i]);
			printf("received at i-%d: %s\n", i, shell->nodes->argv[i]);
			return ;
		}
		printf("i-%d: %s\n", i, shell->nodes->argv[i]);
		i++;
	}
	printf("\e[1;32mSuccess!\e[0m\n");
}

int main()
{
	t_shell shell;
	
	test(&shell, "abcd", (t_node){
		.argc = 1, .argv = (char*[]){"abcd"}});
	
	test(&shell, "\"ab cd\"", (t_node){
		.argc = 1, .argv = (char*[]){"ab cd"}});
	
	test(&shell, "\"ab\" \"cd\"", (t_node){
		.argc = 2, .argv = (char*[]){"ab", "cd"}});
	
	test(&shell, "ab cd", (t_node){
		.argc = 2, .argv = (char*[]){"ab", "cd"}});
	
	test(&shell, "''a'b' 'cd'", (t_node){
		.argc = 2, .argv = (char*[]){"ab", "cd"}});
	
	test(&shell, "''ab \"\"'cd''''", (t_node){
		.argc = 2, .argv = (char*[]){"ab", "cd"}});
	
	test(&shell, "    \"a b  \" c     ' d'    ", (t_node){
		.argc = 3, .argv = (char*[]){"a b  ", "c", " d"}});
	
	test(&shell, "\"''a''b \" '\"c\"d'", (t_node){
		.argc = 2, .argv = (char*[]){"''a''b ", "\"c\"d"}});	
	
	test(&shell, "\"ab c'd", (t_node){
		.argc = 1, .argv = (char*[]){"ab c'd"}});	
	
	return (0);
}
