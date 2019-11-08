#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

#include <windows.h>
#include <stdio.h>

enum LOG_TYPE
{
	LOG_INFORMATION,
	LOG_WARNING,
	LOG_ERROR
};

#define LOG(type, format, ...) log(type, __FILE__, __LINE__, format, __VA_ARGS__);

void log(LOG_TYPE type, const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n = 0.0f : (n >= 1.0f) ? n = 1.0f : n = n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI

/* CUSTOM BUFFERS SIZES */
#define CUSTOM_BUFFER_SIZE_SMALL 25
#define CUSTOM_BUFFER_SIZE_MEDIUM 50
#define CUSTOM_BUFFER_SIZE_BIG 75
#define CUSTOM_BUFFER_SIZE_EXTRA_BIG 100


/* PATHS */
#define TEXTURE_ROOT_PATH "Assets/Textures/"

#define LIBRARY_MESH_PATH "Library/Meshes/"
#define LIBRARY_TEXTURE_PATH "Library/Textures/"

/* FRACTURE ENGINE MESH FORMAT */
#define FE_MESH "femesh"


typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#endif /* __GLOBALS_H__ */