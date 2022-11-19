#ifndef PROPS_HPP
# define PROPS_HPP

#include "squareProps.hpp"
#include <iostream>

// using namespace obj;

namespace obj
{
	class Props
	{
		public:
			Props(void);
			Props(Props const &src);
			~Props(void);

			// Square props //
			void		ftInitSquareProps(int nbr, std::string type);
			void		ftKillSquareProps(void);
			void        ftAddProps(Vector2 pos, Vector2 size, Color color, bool blocking,
							int nbr, std::string type, std::string name);

			Props		ftReturnCopyProps(void);
			Rectangle   ftReturnRectangleSqPr(int nbr);
			Color       ftReturnRecColorSqPr(int nbr);
			SquareProps *ftReturnSquareProp(int nbr) const; 
			void        ftSetPosSquareProp(Vector2 pos, int nbr);
			void        ftMoveSquareProp(Vector2 pos, int nbr);
			int         ftReturnNbr(void) const;
			int         ftReturnOneNbr(int nbr) const;
			float       ftReturnSqurtPos(char c, int nbr) const;
			float       ftReturnSqurtWorH(char c, int nbr) const;
			float		ftReturnSpeedModifier(char c, int nbr) const;
			void		ftSetSpeedModifier(float speed, char c, int nbr);
			void		ftSetSpeed(float speed, int nbr);
			float		ftReturnSpeed(int nbr) const;
			void		ftChangeSpeedModifier(float speed, char c, int nbr);
			void		ftDeleteVarsChar(int nbr);
			void		ftChangeNbr(int nbr);

			void		ftChangeSquareName(int nbr, std::string name);
			std::string	ftReturnSquareName(int nbr) const;

		private:
			SquareProps *_squareProps;
			SquareProps *_platforms;
			int         _nbrSquare;
	};
};

#endif