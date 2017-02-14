cmake_minimum_required(VERSION 3.0.0)


set (ProjectName "IMU")

set (CMAKE_PREFIX_PATH $ENV{QTDIR} $ENV{QT_DIR} $ENV{OPENCV_DIR}/build/x86/vc12/)
message(CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH})


project (${ProjectName})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

if(MSVC)
  set(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
endif()







# --------------------------------------
# ELENCO DELLE CARTELLE DI LIBRERIE 

set (SourceFolders . qCustomPlot)

# ---------------------------------


#aggiungo cartelle include
include_directories( ${SourceFolders} )


# cerco inizialmente le QT5

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5SQL)
find_package(Qt5Multimedia)
find_package(Qt5SerialPort)
find_package(Qt5OpenGL)
find_package(Qt5XML)
find_package(Qt5WebKit)
find_package(Qt5PrintSupport)
find_package(Qt5WebKitWidgets)
find_package(Qt5MultimediaWidgets)
find_package(Qt5axcontainer)


#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)



if (${Qt5Widgets_FOUND})

	# Use the Widgets module from Qt 5.
	#target_link_libraries(helloworld Qt5::Widgets)
	
	message("Qt5 found.")
	
	
		set(CMAKE_INCLUDE_CURRENT_DIR ON)
		# Instruct CMake to run moc automatically when needed.
		set(CMAKE_AUTOMOC ON)

	

	
else()
	message("Qt5 not found. Looking for Qt4")
	
	#cerco Qt4
	set(QT_USE_QTNETWORK TRUE) 
	set(QT_USE_QTSQL TRUE) 
	SET(QT_USE_QTGUI TRUE)
	SET(QT_USE_QTOPENGL TRUE)
	SET(QT_USE_QTXML TRUE)
	
	add_definitions(-DQT_DLL)
	# add_definitions(-DQT_NODLL)
	
	# note that it's Qt4, not QT4 or qt4
	find_package(Qt4) 
	
	if (${Qt4_FOUND})
		message("Qt4 found.")
	endif()
	
	# add some useful macros and variables
	# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
	INCLUDE( ${QT_USE_FILE} )

	  

endif()



# ----------------------------------------------------------------------------
#  Build & install layouts
# ----------------------------------------------------------------------------

# Save libs and executables in the same place
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Output directory for applications" )


# ----------------------------------------------------------------------------
# Solution folders:
# ----------------------------------------------------------------------------
if(ENABLE_SOLUTION_FOLDERS)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()




# --------------------
# Parte del progetto
# --------------------

foreach (fold ${SourceFolders})
	file(GLOB SRCFILES ${SRCFILES} "${fold}/*.cxx" "${fold}/*.cpp" "${fold}/*.c")
	file(GLOB HFILES ${HFILES} "${fold}/*.h" "${fold}/*.hpp")
	file(GLOB SAMPLE_UIS ${SAMPLE_UIS} "${fold}/*.ui")
	file(GLOB SAMPLE_RCS ${SAMPLE_RCS} "${fold}/*.qrc")
	 MESSAGE("folder: ${fold}")

	file(GLOB SRCFILES_t "${fold}/*.cxx" "${fold}/*.cpp" "${fold}/*.c")
	file(GLOB HFILES_t  "${fold}/*.h" "${fold}/*.hpp")
	file(GLOB SAMPLE_UIS_T  "${fold}/*.ui")
	file(GLOB SAMPLE_RCS_t  "${fold}/*.qrc")

	source_group (${fold} FILES ${SRCFILES_t})
	source_group (${fold} FILES ${HFILES_t})
	source_group (${fold} FILES ${SAMPLE_UIS_T})
	source_group (${fold} FILES ${SAMPLE_RCS_t})

endforeach (fold)

	
	set (addExe ${SRCFILES} ${HFILES})
	
	#qt4
	if (${Qt4_FOUND})
	 # this command will generate rules that will run rcc on all files from SAMPLE_RCS
	  # in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
	  QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )
	  
	  # this will run uic on .ui files:
	  QT4_WRAP_UI( SAMPLE_UI_HDRS ${SAMPLE_UIS} )

	  # and finally this will run moc:
	  QT4_WRAP_CPP( SAMPLE_MOC_SRCS ${HFILES} )
	  
	  
	  set (addExe ${SAMPLE_RC_SRCS} ${SAMPLE_MOC_SRCS} ${SRCFILES} ${HFILES} ${SAMPLE_UI_HDRS})
	  
	 endif()

	 
	 #qt5
	 
	 if (${Qt5Widgets_FOUND})
	 
		QT5_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )
	 
		QT5_WRAP_UI(SAMPLE_UI_HDRS ${SAMPLE_UIS})

		# qt_wrap_ui(${ProjectName} ${SAMPLE_UI_HDRS} ${SAMPLE_UISCXX} ${SAMPLE_UIS} )
		   
		   
		set (addExe  ${SAMPLE_RC_SRCS} ${SRCFILES} ${HFILES} ${SAMPLE_UI_HDRS})
		
	 endif()
	 
	 

include_directories (${CMAKE_CURRENT_BINARY_DIR})
	
add_executable(${ProjectName} ${addExe})




	#qt4
	if (${Qt4_FOUND})
		source_group ("MOCFILES" FILES ${SAMPLE_MOC_SRCS})
		source_group ("UIFILES" FILES ${SAMPLE_UI_HDRS})
		source_group ("RCFILES" FILES ${SAMPLE_RC_SRCS})
	endif()



	#qt4
	if (${Qt4_FOUND})
		target_link_libraries (${ProjectName}  ${OpenCV_LIBS} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${OtherLibs} )
	endif()
	
	#qt5
	if (${Qt5Widgets_FOUND})
		
		target_link_libraries (${ProjectName}  ${OpenCV_LIBS} Qt5::AxContainer  Qt5::PrintSupport Qt5::Widgets Qt5::Network Qt5::WebKit Qt5::WebKitWidgets Qt5::Sql Qt5::SerialPort Qt5::MultimediaWidgets Qt5::Multimedia Qt5::OpenGL Qt5::Xml ${OPENGL_LIBRARIES} ${OtherLibs} )
		
		#target_link_libraries (${ProjectName}  ${OpenCV_LIBS} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${OtherLibs} )
		
	endif()


# ------------------------------------



# ----------------------------------------------------------------------------
# Summary:
# ----------------------------------------------------------------------------
message("")
message("General configuration for Imagelab Libs  =====================================")