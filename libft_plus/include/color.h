/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:26:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/03/17 18:41:49 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/**
 * ### Color Beginning (Literal)
 * #### Parses colors as:
 * Font: 30-37
 * Background: 40-47
 * Neon font: 90-93
 * Neon background: 100-107
 */
# define CLR_BL "\e["
/**
 * ### Color Beginning (Hexadecimal)
 * #### Parses colors as:
 * 
 */
# define CLR_BH	"\x1b["

/**
 * ### Color End
 */
# define CLR_E "m"

/* TEXT STYLE */

# define S_STD		"0"
# define S_BOLD		"1"
# define S_DIM		"2"
# define S_ITALIC	"3"
# define S_LINED	"4"
# define S_FLASH	"5"
# define S_INVERT	"7"
# define S_INVIS	"8"

/* FONT COLORS */

# define F_BLK		"30"
# define F_RED		"31"
# define F_GRN		"32"
# define F_BRN		"33"
# define F_BLU		"34"
# define F_PRP		"35"
# define F_CYN		"36"
# define F_WHT		"37"

/* BACKGROUND COLORS */

# define B_BLK		"40"
# define B_RED		"41"
# define B_GRN		"42"
# define B_BRN		"43"
# define B_BLU		"44"
# define B_PRP		"45"
# define B_CYN		"46"
# define B_WHT		"47"

/* NEON FONT COLORS */

# define NF_BLK		"90"
# define NF_RED		"91"
# define NF_GRN		"92"
# define NF_BRN		"93"
# define NF_BLU		"94"
# define NF_PRP		"95"
# define NF_CYN		"96"
# define NF_WHT		"97"

/* NEON BACKGROUND COLORS */

# define NB_BLK		"100"
# define NB_RED		"101"
# define NB_GRN		"102"
# define NB_BRN		"103"
# define NB_BLU		"104"
# define NB_PRP		"105"
# define NB_CYN		"106"
# define NB_WHT		"107"

#endif