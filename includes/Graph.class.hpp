/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.class.hpp                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:24:06 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/23 16:48:14 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

# include "gomoku.hpp"
# include "AInterface.class.hpp"
# include <map>

typedef std::map<std::string, SDL_Surface *>	MapSurfaces;
typedef std::map<int, TTF_Font *>				MapFonts;
typedef std::map<int, AInterface *>				MapMenus;

class	Graph
{
	public:
		Graph(void);
		~Graph(void);

		void			draw(void);
		int				parseEvent(bool & loop_bool);
		void			mouseMotion(void);
		void			input(bool & loop_bool);
		void			windowEvent(void);

		SDL_Window		*getWindow(void) const;
		SDL_Surface		*getScreen(void) const;
		SDL_Surface		*getSurface(std::string name);
		TTF_Font		*getFont(int font);
		SDL_Texture		*getTexture(void);
		SDL_Renderer	*getRenderer(void);
		AInterface		*getInterface(void) const;
		AInterface		*getMenu(int type);
		void			setMenus(void);
		bool			getError(void) const;
		int				getW(void) const;
		int				getH(void) const;
		bool			hasMouseFocus(void) const;
		bool			hasKeyboardFocus(void) const;
		bool			isMinimized(void) const;
		bool			doContinue(void) const;

		void			setMinWinSize(void);
		void			setInterface(AInterface *interface);
		void			setSurfaces(void);
		void			setFonts(void);

		void			reloadInterfaces(void);

		int				error(std::string message);
		int				sdl_error(std::string message);
		int				ttf_error(std::string message);
		//int			img_error(std::string message);


	private:
		bool			_mouseFocus;
		bool			_keyboardFocus;
		bool			_fullScreen;
		bool			_minimized;
		bool			_error;
		bool			_exit;

		int				_w;
		int				_h;

		MapSurfaces		_surfaces;
		MapFonts		_fonts;
		MapMenus		_menus;

		SDL_Window		*_window;
		SDL_Surface		*_screen;
		SDL_Event		_event;
		SDL_Renderer	*_renderer;
		SDL_Texture		*_texture;
		AInterface		*_interface;
		std::string		_path;

};

#endif
