/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:47:15 by rcherik           #+#    #+#             */
/*   Updated: 2016/03/17 15:00:12 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include <string>

class Player
{
	public:
		Player(int num, std::string name);
		Player(Player *player);
		~Player(void);
		Player(void);

		int			getNum(void);
		int			getCap(void);
		int			getNbCoups(void);
		void		incCap(void);
		std::string	& getName(void);
		void		incNbCoups(void);
		void		setName(std::string name);
		void		setCap(int cap);

	private:
		int			_num;
		std::string	_name;
		int			_cap;
		int			_nbCoups;
};

#endif
