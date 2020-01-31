cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt5
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
if(Qt5_DIR)
	message(Qt5_DIR " ${Qt5_DIR}")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
# misc opengl libraries
include_directories("${CMAKE_SOURCE_DIR}/third-party/glew-2.1.0/include")
include_directories("${CMAKE_SOURCE_DIR}/third-party/glm")
link_directories("${CMAKE_SOURCE_DIR}/third-party/glew-2.1.0/lib/Release/x64/")


add_executable(mazer
	"main.cpp"
)

target_include_directories(
	mazer PUBLIC ${OPENGL_INCLUDE_DIR} "src/"
)

target_link_libraries( 
	mazer 
		PUBLIC
		glew32
		glfw 
		${OPENGL_gl_LIBRARY} 
		Qt5::Core
		Qt5::Gui 
		Qt5::Widgets
)




set_target_properties(mazer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES OUTPUT_NAME "${PLUGIN_OUTPUT_FILENAME}")