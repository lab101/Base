if( NOT TARGET Base )
	get_filename_component( BASE_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )
	get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE )

	
	list( APPEND BASE_SOURCES
		${BASE_SOURCE_PATH}/Settings/SettingController.cpp
		${BASE_SOURCE_PATH}/Settings/SettingManager.cpp
    		${BASE_SOURCE_PATH}/AssetLoader/LUrlParser.cpp
    		${BASE_SOURCE_PATH}/TouchVisualiser.cpp

	)
	add_library( Base ${BASE_SOURCES})

target_include_directories( Base PUBLIC "${BASE_SOURCE_PATH}" )
	target_include_directories( Base SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

	if( NOT TARGET cinder )
		    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
		    find_package( cinder REQUIRED PATHS
		        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
		        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
	endif()
	target_link_libraries( Base PRIVATE cinder )
	
endif()



