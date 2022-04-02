#pragma once

#include <windows.h>


// Std includes
#include <iostream>
#include <format>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>


// GL includes
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


// Debug Flag
#ifdef _DEBUG
#define DEBUG
#endif


//+++++++++++++++++++++++++++++++++++++
// DEFINES

#ifdef DEBUG
#define INLINE_		inline
#endif

#define EXTERN_			extern
#define OSAPIC			__stdcall


//+++++++++++++++++++++++++++++++++++++
// MATH CONSTANTS


#define ALPHA				1.0f
#define DEGREES_TO_RADIANT	0.0174532924f//3.14159265359f/180.0f
#define RADIANT_TO_DEGREE	57.295779513078550f//180.0f/3.14159265359.0f
#define f_EPSILON			1e-6f//0.0001
#define EPSILON				0.001f
#define HALF_PI				1.57079632679f
#define FROM255TO1			0.003921569f

//+++++++++++++++++++++++++++++++++++++
// SOLUTION SETTINGS

#define MAX_SHADER_UNIFOR_INPUTS 14
#define CAMERA_FOVX				 90.0f
#define CAMERA_ZFAR				 10000.0f
#define CAMERA_ZNEAR			 1.0f

//+++++++++++++++++++++++++++++++++++++
// BUILD SETTINGS

#define _COMPILE_LPCWSTR_		//#define _COMPILE_LPCWSTR_ L
#define TEXT_FORMAT_MAX_SIZE	1024

//=====================================
// APPLICATION SETTINGS
#define _SO_WINDOWS_ 
#define _OPENGL_MAX_VERSION_	3
#define _OPENGL_MIN_VERSION_	3


#define PC_DESKTOP


#pragma warning( disable: 4127 )
#pragma warning( disable: 4100 )
