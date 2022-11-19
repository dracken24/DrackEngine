
#ifndef ENVITEM_HPP
#define ENVITEM_HPP

#include "../../vendor/raylib/src/raylib.h"
#include "../../myIncludes/class2D/envitems.hpp"
#include <stdlib.h>
#include <iostream>

namespace obj
{
	typedef struct VarCharEnvi
	{
		char *enviPosX;
		char *enviPosY;
		char *enviWidth;
		char *enviHeight;
		int nbr = 4;
	} VarCharEnvi;

	typedef struct EnvItem
	{
		Texture2D texture;
		Color color;
		Rectangle rect;
		VarCharEnvi _varCharEnvi;
		Color pixColor;

		int blocking;
		int nbr;

		std::string name;
	} EnvItem;

	class EnvItems
	{
	public:
		EnvItems(void);
		EnvItems(EnvItems const &src);
		~EnvItems(void);

		EnvItems	*ftInitOneEnvitem(Vector2 pos, Vector2 size, int blocking,
						Color color, Texture2D texture, int nbr, std::string name);

		void		ftInitPosition(float x, float y);
		void		ftChangePosition(float x, float y);
		void		ftChangeColor(Color color);

		VarCharEnvi *ftReturnVarsCharEnvi(void);
		int 		ftReturnEnviAllNbr(void) const;
		Rectangle 	ftReturnOneRectangle(void) const;
		Vector2 	ftReturnOneEnviPos(void) const;
		Vector2 	ftReturnOneEnviSize(void) const;
		Color 		ftReturnOneEnviColor(void) const;
		Texture2D 	ftReturnOneEnviTexture(void) const;
		EnvItem 	*ftReturnOneEnvitemPtr(void);
		EnvItems 	*ftReturnOneEnvitems(void);

		void 		ftInitVarChar(void);
		void 		ftDeleteVarChar(void);
		void 		ftDestroyImgs(void);

		// EnvItems	ftReturnEnvitems(void);

	private:
		EnvItem		_item;
		VarCharEnvi	_varCharEnvi;
	};
};

#endif