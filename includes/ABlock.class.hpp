/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABlock.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:31:02 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 18:31:43 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABLOCK_CLASS_HPP
# define ABLOCK_CLASS_HPP

# include "gomoku.hpp"
# include "SDL2/SDL_ttf.h"

class AInterface;

class Graph;

class	ABlock
{
	public:
		ABlock(Graph *graph, SDL_Rect & blockDef);
		ABlock(Graph *graph, SDL_Rect & blockDef, std::string text);
		ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, SDL_Rect & messageDef);
		ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, std::string background);
		ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, SDL_Rect & messageDef, std::string background);
		ABlock(ABlock *block);
		virtual ~ABlock(void);

		void			init(Graph *graph, SDL_Rect & blockDef);
		bool			isInBlock(int x, int y);

		ABlock			*operator=(ABlock *rhs);

		virtual int		selected(void);
		virtual void	unselect(void);
		int				hoovered(void);
		void			unhoover(void);
		void			selectable(bool b);
		bool			isSelected(void) const;
		bool			isHoovered(void) const;
		bool			isSelectable(void) const;
		bool			isHidden(void);

		int				getType(void) const;
		std::string		getText(void) const;
		int				getID(void) const;
		int				getFontID(void) const;
		std::string		getBackgroundPath(void) const;
		SDL_Rect		getMessageRect(void) const;
		SDL_Color		getColor(void) const;
		SDL_Rect		getBackgroundRect(void) const;
		Graph			*getGraph(void) const;

		void			setBackground(std::string filename);
		virtual void	setBackgroundRect(SDL_Rect rect);
		void			setMessage();
		void			setMessage(SDL_Texture **texture, std::string & text);
		void			setMessage(SDL_Texture **texture, std::string & text, TTF_Font *font, SDL_Color color);
		void			setMessage(SDL_Texture **texture, std::string & text, SDL_Rect *rect);
		void			setMessage(SDL_Texture **texture, std::string & text, TTF_Font *font, SDL_Rect *rect);
		void			setFontID(int font);
		void			setFontSize(int size);
		void			setFontStyle(int style);
		void			setMessageColor(int r, int g, int b);
		void			setMessageRect(SDL_Rect & rect);
		void			setMessageFontRect(std::string & text, TTF_Font *font, SDL_Rect *rect);
		void			setText(std::string text);
		void			hide(bool b);

		void			setClockBlock(ABlock *u, ABlock *r, ABlock *d, ABlock *l);

		void			setRightBlock(ABlock *right);
		void			setLeftBlock(ABlock *left);
		ABlock			*getRightBlock(void) const;
		ABlock			*getLeftBlock(void) const;
		void			setDownBlock(ABlock *down);
		void			setUpBlock(ABlock *up);
		ABlock			*getDownBlock(void) const;
		ABlock			*getUpBlock(void) const;

		virtual bool	action(int x, int y) = 0;
		virtual void	draw(void) = 0;


	protected:
		int				_type;
		int				_id;

		SDL_Rect		_backgroundRect;
		SDL_Rect		_messageRect;

		bool			_selectable;
		bool			_selected;
		bool			_hoovered;
		bool			_hidden;

		std::string		_backgroundPath;
		SDL_Surface		*_background;
		SDL_Texture		*_backgroundTexture;
		Graph			*_graph;

		std::string		_text;
		int				_fontID;
		int				_fontSize;
		int				_fontStyle;
		SDL_Color		_color;
		TTF_Font		*_font;
		SDL_Texture		*_messageTexture;

		ABlock			*_left;
		ABlock			*_right;
		ABlock			*_down;
		ABlock			*_up;

	private:
		static int		_idKey;
};

std::ostream &			operator<<(std::ostream & o, ABlock *rhs);

#endif
