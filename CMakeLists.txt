cmake_minimum_required(VERSION 3.10)
project(cedar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(OpenGL_GL_PREFERENCE LEGACY)

add_subdirectory(glfw)
find_package(OpenGL REQUIRED)

add_library(cedar
		glad/src/glad.c
		glad/include/glad/glad.h
		include/cedar/XException.h
		src/core/XException.cpp
		include/cedar/Thread.h
		src/multithreading/Thread.cpp
		include/cedar/Logger.h
		src/logging/Logger.cpp
		include/cedar/LoggerFactory.h
		src/logging/LoggerFactory.cpp
		include/cedar/QueueLogAppender.h
		src/logging/QueueLogAppender.cpp
		include/cedar/Vector2f.h
		src/math/Vector2f.cpp
		include/cedar/Vector3f.h
		src/math/Vector3f.cpp
		include/cedar/Vector4f.h
		src/math/Vector4f.cpp
		include/cedar/Matrix4f.h
		src/math/Matrix4f.cpp
		include/cedar/Quaternionf.h
		src/math/Quaternionf.cpp
		include/cedar/Math.h
		include/cedar/Window.h
		src/graphics/window/Window.cpp
		include/cedar/ShaderProgram.h
		src/graphics/shader/ShaderProgram.cpp include/cedar/Vector2i.h include/cedar/Vector2ui.h include/cedar/Vector2d.h include/cedar/Vector3i.h include/cedar/Vector3ui.h include/cedar/Vector3d.h include/cedar/Vector4i.h include/cedar/Vector4d.h include/cedar/Vector4ui.h include/cedar/Input.h include/cedar/InputHandler.h src/input/InputHandler.cpp src/math/Vector2d.cpp include/cedar/GuiRenderer.h src/graphics/renderer/GuiRenderer.cpp include/cedar/Texture.h src/graphics/texture/Texture.cpp include/cedar/Texture2D.h src/graphics/texture/Texture2D.cpp include/cedar/GLConstants.h include/cedar/OpenSimplexNoise.h src/math/OpenSimplexNoise.cpp include/cedar/Model.h src/graphics/model/Model.cpp include/cedar/Cedar.h src/core/Cedar.cpp include/cedar/ModelRegistry.h src/graphics/model/ModelRegistry.cpp)

target_include_directories(cedar PUBLIC
		glad/include
		include
		${OPENGL_INCLUDE_DIR})

target_link_libraries(cedar glfw ${OPENGL_gl_LIBRARY})


