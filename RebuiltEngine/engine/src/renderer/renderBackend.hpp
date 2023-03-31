/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderBackhand.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef RENDERBACKHAND_HPP
# define RENDERBACKHAND_HPP

# include "renderType.inl"

struct PlatformState;

bl8		RendererBackendCreate(rendererBackendType type, struct PlatformState *platState,
			rendererBackend *outRendererBackend);
void	RendererBackendDestroy(rendererBackend *rendererBackend);

#endif
