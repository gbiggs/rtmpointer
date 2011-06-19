set(PKG_DESC "Pointer-sharing transport for OpenRTM-aist")
set(PKG_EXTERNAL_DEPS "openrtm-aist")
set(PKG_LIBS -lrtmpointer)
set(pkg_conf_file ${CMAKE_CURRENT_BINARY_DIR}/rtmpointer.pc)
configure_file(rtmpointer.pc.in ${pkg_conf_file} @ONLY)
install(FILES ${pkg_conf_file}
    DESTINATION ${LIB_INSTALL_DIR}/pkgconfig/ COMPONENT build)

# Install CMake modules
set(cmake_config ${CMAKE_CURRENT_BINARY_DIR}/rtmpointer-config.cmake)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rtmpointer-config.cmake.in
    ${cmake_config} @ONLY)
set(cmake_version_config ${CMAKE_CURRENT_BINARY_DIR}/rtmpointer-config-version.cmake)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rtmpointer-config-version.cmake.in
    ${cmake_version_config} @ONLY)
set(cmake_mods ${CMAKE_CURRENT_SOURCE_DIR}/Modules/FindOpenRTM.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/Findrtmpointer.cmake
    ${cmake_config} ${cmake_version_config})
install(FILES ${cmake_mods} DESTINATION ${SHARE_INSTALL_DIR} COMPONENT build)

