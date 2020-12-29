include(WhiteList.cmake)
include(CompilerFlags.cmake)

project(chaplin)

add_library(chaplin STATIC ${SOURCES} ${HEADERS})

#no dependencies
set(LOCAL_MODULE_DEPENDENCIES)

set(MODULE_DEPENDENCIES ${LOCAL_MODULE_DEPENDENCIES} PARENT_SCOPE)
set(PUBLIC_MODULE_HEADERS ${HEADERS} PARENT_SCOPE)

target_link_libraries(chaplin
	${LOCAL_MODULE_DEPENDENCIES}
	ddk
	pthread
	log4cxx)

set_target_properties(chaplin PROPERTIES FOLDER "Chaplin")