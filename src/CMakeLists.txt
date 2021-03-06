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


set(SRCS
	"main.cpp"
	"mainwindow.cpp"
	"mazeglwidget.cpp"
	"shaderprogram.cpp"
	"algorithms.cpp"
	"gameobject.cpp"
	"wallobject.cpp"
	"playerobject.cpp"
	"camera.cpp"
)

set(UI
	"mainwindow.ui"
)

set(HEADERS
	${PROJECT_SOURCE_DIR}/include/mainwindow.hpp
	${PROJECT_SOURCE_DIR}/include/mazeglwidget.hpp
	${PROJECT_SOURCE_DIR}/include/vertex.hpp
	${PROJECT_SOURCE_DIR}/include/shaderprogram.hpp
	${PROJECT_SOURCE_DIR}/include/algorithms.hpp
	${PROJECT_SOURCE_DIR}/include/gameobject/gameobject.hpp
	${PROJECT_SOURCE_DIR}/include/gameobject/wallobject.hpp
	${PROJECT_SOURCE_DIR}/include/gameobject/playerobject.hpp
	${PROJECT_SOURCE_DIR}/include/camera.hpp
	${PROJECT_SOURCE_DIR}/include/libs.hpp
)

qt5_wrap_ui(ui_wrap ${UI})
qt5_wrap_cpp(moc_sources ${HEADERS})

if(WIN32)
	add_executable(mazer WIN32
		${SRCS}
		${HEADERS}
		${moc_sources}
		${ui_wrap}
		"resources.qrc"
	)
else()
	add_executable(mazer
		${SRCS}
		${HEADERS}
		${moc_sources}
		${ui_wrap}
		"resources.qrc"
	)
endif()

target_include_directories(
	mazer 
		PUBLIC 
			${OPENGL_INCLUDE_DIR} 
			$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>

)

target_link_libraries( 
	mazer 
		PUBLIC
		${OPENGL_gl_LIBRARY} 
		Qt5::Core Qt5::Gui  Qt5::Widgets
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