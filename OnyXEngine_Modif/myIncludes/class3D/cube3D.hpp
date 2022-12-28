#ifndef CUBE3D_HPP
# define CUBE3D_HPP

# include "../../vendor/raylib/src/raylib.h"
# include <iostream>

using std::string;

typedef struct Cube3D
{
	Vector3	pos;
	Vector3	size;
	Texture	texture;
	string	name;
} Cube3D;

class CUBE3D
{
	public:
		CUBE3D(void);
		CUBE3D(CUBE3D const &src);
		~CUBE3D(void);

		void        ftInitCube(Vector3 pos, Vector3 size, Texture texture, string name);

		// Change
		void        ftChangePosition(Vector3 pos);
		void        ftChangeSize(Vector3 size);
		void        ftChangeName(string name);
		void        ftChangeTexture(Texture texture);

		void		ftMovePosition(Vector3 pos);
		void		ftExpendCube(Vector3 size);

		// Return
		Vector3     ftReturnPosition(void) const;
		Vector3     ftReturnSize(void) const;
		string      ftReturnName(void) const;
		Texture     ftReturnTexture(void) const;
		Cube3D		ftReturnCube3D(void) const;

	private:
		Cube3D  _cube;
};

#endif