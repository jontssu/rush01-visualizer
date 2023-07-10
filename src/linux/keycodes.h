/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:38:42 by hseppane          #+#    #+#             */
/*   Updated: 2023/02/23 12:10:12 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

enum e_key
{
	KEY_ESCAPE = 0xFF1B,
	KEY_LEFT = 0xFF51,
	KEY_RIGHT = 0xFF53
};

enum	e_mouse_button
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 3,
	MOUSE_MID = 2,
	SCROLL_DOWN = 5,
	SCROLL_UP = 4,
	KEY_P = 34
};

#endif
