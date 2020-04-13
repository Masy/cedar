cmake_minimum_required(VERSION 3.10)
project(cedar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(OpenGL_GL_PREFERENCE LEGACY)

add_subdirectory(glfw)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

add_library(cedar
		glad/src/glad.c
		glad/include/glad/glad.h
		include/cedar/XException.hpp
		src/core/XException.cpp
		include/cedar/Thread.hpp
		src/thread/Thread.cpp
		include/cedar/Logger.hpp
		src/logging/Logger.cpp
		include/cedar/LoggerFactory.hpp
		src/logging/LoggerFactory.cpp
		include/cedar/QueueLogAppender.hpp
		src/logging/QueueLogAppender.cpp
		include/cedar/Math.hpp
		include/cedar/Window.hpp
		src/graphics/window/Window.cpp
		include/cedar/ShaderProgram.hpp
		src/graphics/shader/ShaderProgram.cpp
		include/cedar/Vector2i.hpp
		src/math/Vector2i.cpp
		include/cedar/Vector2ui.hpp
		src/math/Vector2ui.cpp
		include/cedar/Vector2d.hpp
		include/cedar/Vector2f.hpp
		src/math/Vector2f.cpp
		include/cedar/Vector3i.hpp
		include/cedar/Vector3ui.hpp
		include/cedar/Vector3d.hpp
		include/cedar/Vector3f.hpp
		src/math/Vector3f.cpp
		include/cedar/Vector4i.hpp
		include/cedar/Vector4d.hpp
		include/cedar/Vector4f.hpp
		src/math/Vector4f.cpp
		include/cedar/Vector4ui.hpp
		src/math/Vector4ui.cpp
		include/cedar/Matrix4f.hpp
		src/math/Matrix4f.cpp
		include/cedar/Quaternionf.hpp
		src/math/Quaternionf.cpp
		include/cedar/Input.hpp
		include/cedar/InputHandler.hpp
		src/input/InputHandler.cpp
		src/math/Vector2d.cpp
		include/cedar/Renderer2D.hpp
		src/graphics/renderer/Renderer2D.cpp
		include/cedar/Texture.hpp
		src/graphics/texture/Texture.cpp
		include/cedar/Texture2D.hpp
		src/graphics/texture/Texture2D.cpp
		include/cedar/GLConstants.hpp
		include/cedar/OpenSimplexNoise.hpp
		src/math/OpenSimplexNoise.cpp
		include/cedar/Model.hpp
		src/graphics/model/Model.cpp
		include/cedar/Cedar.hpp
		src/core/Cedar.cpp
		include/cedar/ModelRegistry.hpp
		src/graphics/model/ModelRegistry.cpp
		include/cedar/Font.hpp
		src/graphics/font/Font.cpp
		include/cedar/Glyph.hpp
		src/graphics/font/Glyph.cpp
		include/cedar/GlyphData.hpp
		src/graphics/font/GlyphData.cpp
		include/cedar/FontRegistry.hpp
		src/graphics/font/FontRegistry.cpp
		stb/include/stb_image_write.h
		include/cedar/Quad.hpp
		src/graphics/model/Quad.cpp
		include/cedar/TextBuffer.hpp
		src/graphics/model/TextBuffer.cpp
		include/cedar/OpenGLThread.hpp
		src/thread/OpenGLThread.cpp
		include/cedar/EngineThread.hpp
		src/thread/EngineThread.cpp
		include/cedar/MasterRenderer.hpp
		src/graphics/renderer/MasterRenderer.cpp
		include/cedar/Renderer.hpp
		src/graphics/renderer/Renderer.cpp
		include/cedar/Camera.hpp
		src/entity/camera/Camera.cpp
		include/cedar/Config.hpp
		src/core/Config.cpp
		include/cedar/Element.hpp
		src/graphics/gui/elements/Element.cpp
		include/cedar/Screen.hpp
		src/graphics/gui/Screen.cpp
		include/cedar/ScreenRegistry.hpp
		src/graphics/gui/ScreenRegistry.cpp
		include/cedar/Intersection.hpp
		include/cedar/GUIConstants.hpp
		include/cedar/Button.hpp
		src/graphics/gui/elements/Button.cpp
		include/cedar/Label.hpp
		src/graphics/gui/elements/Label.cpp
		include/cedar/FrustumRayBuilder.hpp
		src/math/FrustumRayBuilder.cpp
		include/cedar/Scene.hpp
		src/scene/Scene.cpp
		include/cedar/MeshCollider2D.hpp
		src/math/collision/MeshCollider2D.cpp
		include/cedar/Entity.hpp
		src/entity/Entity.cpp
		include/cedar/EntityManager.hpp
		src/entity/EntityManager.cpp
		include/cedar/Distance2D.hpp include/cedar/FreeTypeFont.hpp src/graphics/font/FreeTypeFont.cpp include/cedar/PTFFont.hpp src/graphics/font/PTFFont.cpp include/cedar/TextureRegistry.hpp src/graphics/texture/TextureRegistry.cpp include/cedar/ImageLoader.hpp src/graphics/texture/ImageLoader.cpp)

target_include_directories(cedar PUBLIC
		glad/include
		include
		freetype2/include
		stb/include
		${OPENGL_INCLUDE_DIR})

target_link_libraries(cedar glfw ${FREETYPE_LIBRARIES} ${OPENGL_gl_LIBRARY})


