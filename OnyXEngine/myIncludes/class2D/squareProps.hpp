#ifndef SQUAREPROPS_HPP
# define SQUAREPROPS_HPP

#include "../../vendor/raylib/src/raylib.h"
#include <stdlib.h>
#include <iostream>

	typedef struct VarCharPr
	{
		char *propPosX;
		char *propPosY;
		char *propWidth;
		char *propHeight;
		int	nbr = 0;
	}	VarCharPr;

	typedef struct VarsSideDownPanelPr
	{
		Rectangle   		rect;
		VarCharPr		varCharPr;
		Color			pixColor;
	}	VarsSideDownPanelPr;

	class SquareProps
	{
		public:
			SquareProps(void);
			SquareProps(SquareProps const &src);
			~SquareProps(void);

			SquareProps *ftInitSquareprops(Vector2 pos, Vector2 size, Color color, bool blocking, int nbr, std::string name);
			void		ftInitPosition(Vector2 pos);
			Rectangle	ftReturnRectangle(void) const;
			Color		ftReturnRecColor(void) const;

			VarCharPr	*ftReturnVarsProp(void);
			void		ftInitVars(void);
			void		ftDeleteVars(void);

			void 		ftChangeWorH(float size, char c);

			Vector2		*ftReturnPositionPtr(void) ;
			float		ftReturnSpeed(void) const;
			void		ftChangeSpeed(float speed);
			void		ftSetSpeed(float speed);
			void		ftMovePosition(float x, float y);
			void		ftMovePositionVec(Vector2 pos);

			float		ftReturnWideorHigh(char c) const;
			// int			ftReturnNbr(void) const;

			float		ftReturnSpeedX(char c) const;
			void		ftSetSpeedX(float speed, char c);
			void		ftChangeSpeedX(float speed, char c);

			float		ftReturnSpeedModifier(char c) const;
			void		ftSetSpeedModifier(float speed, char c);
			void		ftChangeSpeedModifier(float speed, char c);

			float		ftReturnSqurtPos(char c) const;
			SquareProps *ftReturnCopySquareProp(void);
			SquareProps ftReturnSquareProp(void);

			Color	 	ftReturnColorPix(void);
			void	 	ftInitColorPix(Color color);
			void	 	ftInitColor(Color color);

			//-- Add by drag and drop --//

		private:
			// EnvItem		_envItem;
			// Rectangle   		rect;
			std::string			_name;
			Color				color;
			Vector2				pos;
			Vector2				speedModifier = {0, 0};
			float				speed;
			float				speedX;
			int					blocking;
			int					_nbr;
			VarsSideDownPanelPr	_varCharPr;
	};

#endif