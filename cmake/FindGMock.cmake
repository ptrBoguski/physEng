# find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
#   PATHS
#     /usr/include
# )
#
# find_library(GMOCK_LIBRARY
#   NAMES gmock
#   PATHS
#     /usr/lib
# )
#
# include(FindPackageHandleStandardArgs)
# find_package_handle_standard_args(GMock DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR)
#
# if(GMOCK_FOUND)
#   set(GMOCK_LIBRARIES ${GMOCK_LIBRARY})
#   set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR})
# endif()
#
# mark_as_advanced(GMOCK_INCLUDE_DIR GMOCK_LIBRARY)
