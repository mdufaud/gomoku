/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogBlock.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGBLOCK_CLASS_HPP
# define LOGBLOCK_CLASS_HPP

# include "ABlock.class.hpp"
# include <list>

typedef std::list<SDL_Rect>						rectList;
typedef std::list<SDL_Texture *>				textList;
typedef std::list<SDL_Texture *>::iterator		textListIt;
typedef std::list<SDL_Rect>::iterator			rectListIt;

# define NOL 8

class	Graph;

class	LogBlock: public ABlock
{
	public:
		LogBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name);
		LogBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name,
					std::string background);
		virtual ~LogBlock(void);

		bool	action(int x, int y);
		bool	hoovered();
		void	draw();
		void	recalc_draw();

		void	scrollUp();
		void	scrollDown();
		void	scrollLeft(void);
		void	scrollRight(void);
		void	addLog(std::string s);
		void	endIt(void);

		void	scrollLogUp(void);
		void	scrollLogDown(void);

	private:
		int			_scrollY;
		int			_scrollX;
		int			_scrollLog;
		rectList	_rList;
		textList	_tList;
		int			_textX;
		int			_textY;

};
#endif
