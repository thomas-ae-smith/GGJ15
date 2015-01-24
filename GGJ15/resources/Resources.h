#pragma once

#ifdef __APPLE__
#	define BIRD_VERT			CINDER_RESOURCE( ../../resources/, bird_vert.glsl, 128, GLSL )
#	define BIRD_FRAG			CINDER_RESOURCE( ../../resources/, bird_frag.glsl, 129, GLSL )
#	define MAP_FRAG				CINDER_RESOURCE( ../../resources/, map_frag.glsl, 130, GLSL )
#elif defined _WIN32 || defined _WIN64
#	define BIRD_VERT 128
#	define BIRD_FRAG 129
#	define MAP_FRAG 130
#endif




