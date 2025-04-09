/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:37:29 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/24 15:23:24 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libft_plus.h"

/*						*
	TRUTHINESS CHECKS
*						*/

// Whether digit (remake)
int		ft_isdigit(int c);

// Whether alphabetical (remake)
int		ft_isalpha(int c);

// Whether alphanumeric (remake)
int		ft_isalnum(int c);

// Whether printable (remake)
int		ft_isprint(int c);

// Whether ascii (remake)
int		ft_isascii(int c);

/*						*
	VALUE CONVERSIONS
*						*/

// Whether uppercase (remake)
int		ft_toupper(int c);

// Whether lowercase (remake)
int		ft_tolower(int c);

/*					*
	ARRAY CHECKS
*					*/

// Get string length (remake)
size_t	ft_strlen(const char *s);

// Find first instance of byte (remake)
void	*ft_memchr(const void *s, int c, size_t n);

// Find first byte diff between arrays (remake)
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Find first instance in character (remake)
char	*ft_strchr(const char *s, int c);

// Find last instance of character (remake)
char	*ft_strrchr(const char *s, int c);

// Find difference between strings, up to limit (remake)
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Find first instance of substring, up to limit (remake)
char	*ft_strnstr(const char *big, const char *little, size_t len);

/*						*
	ARRAY ITERATIONS
*						*/

// Iterate on string characters using provided function
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*						*
	ARRAY CONVERSIONS
*						*/

// Duplicate and convert array through function applied to each character
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// Convert string to integer (remake)
int		ft_atoi(const char *nptr);

// Convert integer to string
char	*ft_itoa(int n);

// Copy a non-overlapping string to another, up to limit (remake)
void	*ft_memcpy(void *dest, const void *src, size_t n);

// Copy a possibly-overlapping string to another, up to limit (remake)
void	*ft_memmove(void *dest, const void *src, size_t n);

// Copy one string into another (remake)
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

// Append one string after another, up to combined limit (remake)
size_t	ft_strlcat(char *dest, const char *src, size_t size);

// Duplicate string using malloc
char	*ft_strdup(const char *src);

// Create string trimmed of set's characters at both ends using malloc (remake)
char	*ft_strtrim(char const *s1, char const *set);

// Create string from another from index by length using malloc
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Set all array bytes to given byte (remake)
void	*ft_memset(void *s, int c, size_t n);

// Set all array bytes to NULL (remake)
void	ft_bzero(void *s, size_t n);

// Create combined string using malloc
char	*ft_strjoin(char const *s1, char const *s2);

// Divide string into malloc'd substrings based on separator
char	**ft_split(char const *s, char c);

/*					*
	MALLOC HELPERS
*					*/

// Malloc for a 'nmemb' members of 'size' bytes (remake)
void	*ft_calloc(size_t nmemb, size_t size);

/*					*
	FILE WRITERS
*					*/

// Write character to file
void	ft_putchar_fd(char c, int fd);

// Write string to file
void	ft_putstr_fd(char *s, int fd);

// Write string plus newline to file
void	ft_putendl_fd(char *s, int fd);

// Write number to file
void	ft_putnbr_fd(int n, int fd);

/*						*
	STRUCTS & LISTS
*						*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Create new t_list item using malloc
t_list	*ft_lstnew(void *content);

// Prepend t_list to beginning of list
void	ft_lstadd_front(t_list **lst, t_list *new);

// Count items in list
int		ft_lstsize(t_list *lst);

// Return last item in list
t_list	*ft_lstlast(t_list *lst);

// Append t_list to end of list
void	ft_lstadd_back(t_list **lst, t_list *new);

// Delete the given list item, deleting the content with the provided function
void	ft_lstdelone(t_list *lst, void (*del)(void*));

// Delete the given list, deleting the contents with the provided function
void	ft_lstclear(t_list **lst, void (*del)(void*));

// Execute the provided function on each of the list's contents
void	ft_lstiter(t_list *lst, void (*f)(void *));

// Duplicate a list with contents modified according to the given function
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
