/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderFronthand.hpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef RENDERFRONTEND_HPP
# define RENDERFRONTEND_HPP

# include "renderer/rendererTypes.inl"

struct static_mesh_data;
struct platformState;

bl8		RendererInit(const char *applicationName, struct platformState *platState);
void	RendererShutdown(void);

void	rendererOnResized(uint16 width, uint16 height);

bl8		RendererDrawFrame(renderPacket *packet);

#endif
