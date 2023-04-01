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

# include "renderer/renderType.inl"

struct staticMeshData;
struct PlatformState;

bl8		RendererInitialize(std::string applicationName, struct PlatformState *platState);
void	RendererShutdown(void);

void	RendererOnResized(uint16 width, uint16 height);

bl8		RendererDrawFrame(renderPacket *packet);

#endif
