# Build the sample components
set(subcomp_srcs sub_rtc.cpp)
set(subcomp_hdrs sub_rtc.h)
set(pubcomp_srcs pub_rtc.cpp)
set(pubcomp_hdrs pub_rtc.h)

include_directories(${PROJECT_SOURCE_DIR}/include ${OPENRTM_INCLUDE_DIRS})
add_definitions(${OPENRTM_DEFINITIONS})

add_library(rtmpointer_subcomp SHARED ${subcomp_srcs} ${ALL_IDL_SRCS})
target_link_libraries(rtmpointer_subcomp ${OPENRTM_LIBRARIES} rtmpointer)

add_library(rtmpointer_pubcomp SHARED ${pubcomp_srcs} ${ALL_IDL_SRCS})
target_link_libraries(rtmpointer_pubcomp ${OPENRTM_LIBRARIES} rtmpointer)

# Install the compiled sample components
install(TARGETS rtmpointer_subcomp rtmpointer_pubcomp
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

# Install the sample files
set(eg_cmakelists ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt.example.in
    ${eg_cmakelists} @ONLY)
install(FILES ${eg_cmakelists} DESTINATION ${SHARE_INSTALL_DIR}/examples
    COMPONENT examples)
install(FILES ${subcomp_srcs} ${subcomp_hdrs} ${pubcomp_srcs} ${pubcomp_hdrs}
    testtype.h README.txt rtc.conf rtmpointer_composite.conf
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    COMPONENT examples)

