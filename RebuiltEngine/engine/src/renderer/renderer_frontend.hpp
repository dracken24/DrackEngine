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
#define RENDERFRONTEND_HPP

#include "renderer/renderer_types.inl"

struct static_mesh_data;
struct platformState;

bl8 renderer_initialize(const char *application_name, struct platformState *plat_state);
void renderer_shutdown();

void renderer_on_resized(uint16 width, uint16 height);

bl8 renderer_draw_frame(render_packet *packet);

#endif
