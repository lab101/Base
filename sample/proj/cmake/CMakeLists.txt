cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

# use -DSET17=1 as command arguments
message("CMAKE_CXX_STANDARD=${SET17}")
if( SET17 ) 
set(CMAKE_CXX_STANDARD 17)
endif()

project( BaseSample )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


set( SRC_FILES
	${APP_PATH}/src/BaseSampleApp.cpp
	${APP_PATH}/../src/Singleton.h
    ${APP_PATH}/../src/AssetLoader/AssetsCache.h
    ${APP_PATH}/../src/AssetLoader/httplib.h
    ${APP_PATH}/../src/AssetLoader/LURLParser.cpp
    ${APP_PATH}/../src/AssetLoader/LURLParser.h
)



ci_make_app(
	SOURCES     ${SRC_FILES}
	CINDER_PATH ${CINDER_PATH}
)
