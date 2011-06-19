set(srcs pointerportmgmt.cpp)

include_directories(${OPENRTM_INCLUDE_DIRS})
add_definitions(${OPENRTM_DEFINITIONS})

set(lib_name rtmpointer)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
add_library(${lib_name} SHARED ${srcs})
target_link_libraries(${lib_name} ${OPENRTM_LIBRARIES})
install(TARGETS ${lib_name} LIBRARY DESTINATION
    ${LIB_INSTALL_DIR} COMPONENT library)

