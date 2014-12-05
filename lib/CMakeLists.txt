cmake_minimum_required(VERSION 3.18)

file(GLOB cpp_sources ${CMAKE_SOURCE_DIR}/lib/*.cc)
file(GLOB cpp_headers ${CMAKE_SOURCE_DIR}/lib/*.h)

add_library(cppdlopen SHARED ${cpp_sources})

set_target_properties(cppdlopen PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS cppdlopen LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)
install( FILES ${cpp_headers} DESTINATION include/${PROJECT_NAME} COMPONENT headers)
