# CMake entry point
cmake_minimum_required (VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)
project (opengl)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	external/Simple-OpenGL-Image-Library/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)



# tutorials
add_executable(tutorials 
	tutorials/main.cpp
	tutorials/MyGLWindow.cpp
	tutorials/MyGLWindow.h
	tutorials/KingTutorial.cpp
	tutorials/KingTutorial.h
	tutorials/ShapeGenerator.cpp
	tutorials/ShapeGenerator.h
	tutorials/ShapeData.cpp
	tutorials/ShapeData.h

	common/shader.cpp
	common/shader.hpp
	
	tutorials/SimpleFragmentShader.fragmentshader
	tutorials/SimpleVertexShader.vertexshader
)
target_link_libraries(tutorials
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorials PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorials/")
create_target_launcher(tutorials WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorials/")
create_default_target_launcher(tutorials WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorials/") # tut 1 is not the default or people would complain that tut 2 doesn't work


# breakout
add_executable(breakout 
	breakout/main.cpp
	breakout/Game.cpp
	breakout/Game.h
	breakout/ResourceManager.cpp
	breakout/ResourceManager.h
	breakout/Shader.cpp
	breakout/Shader.h
	breakout/Texture2D.cpp
	breakout/Texture2D.h
	breakout/SpriteRenderer.cpp
	breakout/SpriteRenderer.h
	breakout/GameObject.h
	breakout/GameObject.cpp
	breakout/BallObject.h
	breakout/BallObject.cpp
	breakout/GameLevel.h
	breakout/GameLevel.cpp

)
target_link_libraries(breakout
	${ALL_LIBS}
	${CMAKE_SOURCE_DIR}/external/Simple-OpenGL-Image-Library/libSOIL.a

)
# Xcode and Visual working directories
set_target_properties(breakout PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/breakout/")
create_target_launcher(breakout WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/breakout/")
create_default_target_launcher(breakout WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/breakout/") # tut 1 is not the default or people would complain that tut 2 doesn't work



SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET tutorials POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorials${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorials/"
)
add_custom_command(
   TARGET breakout POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/breakout${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/breakout/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

