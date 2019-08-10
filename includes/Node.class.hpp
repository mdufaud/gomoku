/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include "Board.class.hpp"
# include "Player.class.hpp"
# include "gomoku.hpp"
# include <list>
# include <utility>

class Node;

typedef std::list<Node>					NodeList;
typedef std::list<Node>::iterator		NodeListIter;
typedef std::pair<int, int>				PlayPair;

class	Node
{
	public:
		Node(void);
		Node(int x, int y, Board & board, Player *p1, Player *p2, int playerTurn, int depth);
		Node(Node & node);
		~Node();

		bool				isRoot(void);
		void				printDepthTab(int actualDepth, int depth);

		int					_x;
		int					_y;
		int					_value;
		int					_depth;
		int					_totalDepth;
		int					_alpha;
		int					_beta;
		bool				_max;

		int					_xPlay;
		int					_yPlay;
		Board				_board;

		Player				*_p1;
		Player				*_p2;
		Player				*_pTurn;
		int					_playerTurn;
		int					_playerNode;

	private:
};

std::ostream &			operator<<(std::ostream & o, Node *rhs);

#endif
