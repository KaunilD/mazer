cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()


# Qt5

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets )
if(${Qt5_FOUND})
	message("Found QT5 at: " ${Qt5_DIR})
else()
	message("Couldn't find Qt. Aborting.")
endif()


# OpenGL
find_package(OpenGL REQUIRED)
# misc opengl libraries
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)


# BOOST
set(Boost_DEBUG				ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS	ON)
set(BOOST_ROOT "C:/boost_1_60_0")
set(BOOST_LIBRARYDIR "C:/boost_1_60_0/stage/lib")
set(BOOST_INCLUDEDIR "C:/boost_1_60_0/build/install/include/boost-1_60")
include_directories(${BOOST_INCLUDEDIR})
find_package( Boost 1.60 COMPONENTS system filesystem REQUIRED )


include_directories("${CMAKE_SOURCE_DIR}/third-party/glew-2.1.0/include")
include_directories("${CMAKE_SOURCE_DIR}/third-party/glm")
link_directories("${CMAKE_SOURCE_DIR}/third-party/glew-2.1.0/lib/Release/x64/")

set(SRCS
	"main.cpp"
	"mainwindow.cpp"
	"mazeglwidget.cpp"
	"objLoader.cpp"
	"shaderprogram.cpp"
)

set(UI
	"mainwindow.ui"
)

set(HEADERS
	"mainwindow.hpp"
	"mazeglwidget.hpp"
	"objLoader.hpp"
	"vertex.hpp"
	"shaderprogram.hpp"
)

qt5_wrap_ui(ui_wrap ${UI})
qt5_wrap_cpp(moc_sources ${HEADERS})


add_executable(mazer WIN32
	${SRCS}
	${HEADERS}
	${moc_sources}
	${ui_wrap}
	"resources.qrc"
)

target_include_directories(
	mazer PUBLIC ${OPENGL_INCLUDE_DIR} "src/"
)

target_link_libraries( 
	mazer 
		PUBLIC
		glew32 glfw ${OPENGL_gl_LIBRARY} 
		Qt5::Core Qt5::Gui  Qt5::Widgets
		${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${BOOST_LIBRARIES}
)


# auto copy dlls if on windows
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)

# set output directory
set_target_properties(mazer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(mazer PROPERTIES OUTPUT_NAME "${PLUGIN_OUTPUT_FILENAME}")