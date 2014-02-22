# - Try to find CEGUI 0
# Once done this will define
#  CEGUI_FOUND - System has CEGUI 0
#  CEGUI_INCLUDE_DIRS - The CEGUI 0 include directories
#  CEGUI_LIBRARIES - The libraries needed to use CEGUI 0
#  CEGUI_DEFINITIONS - Compiler switches required for using CEGUI 0
find_package(PkgConfig)
pkg_check_modules(PC_CEGUI QUIET CEGUI-0)
set(CEGUI_DEFINITIONS ${PC_CEGUI_CFLAGS_OTHER})

find_path(CEGUI_INCLUDE_DIR CEGUI/Version.h
          HINTS ${PC_CEGUI_INCLUDEDIR} ${PC_CEGUI_INCLUDE_DIRS}
          PATH_SUFFIXES CEGUI-0 )

find_library(CEGUI_LIBRARY NAMES CEGUIBase-0 CEGUIBase
             HINTS ${PC_CEGUI_LIBDIR} ${PC_CEGUI_LIBRARY_DIRS} )

 find_library(CEGUI_OGL_LIBRARY NAMES CEGUIOpenGLRenderer-0
             HINTS ${PC_CEGUI_LIBDIR} ${PC_CEGUI_LIBRARY_DIRS} )

set(CEGUI_LIBRARIES ${CEGUI_LIBRARY} ${CEGUI_OGL_LIBRARY})
set(CEGUI_INCLUDE_DIRS ${CEGUI_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CEGUI_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CEGUI DEFAULT_MSG CEGUI_LIBRARY CEGUI_INCLUDE_DIR)

mark_as_advanced(CEGUI_INCLUDE_DIR CEGUI_LIBRARY )
