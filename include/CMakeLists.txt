set(hdrs rtmpointer/pointerportmgmt.h
    rtmpointer/pointerportbase.h
    rtmpointer/pointerport.h)
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}
    COMPONENT headers)

