add_library(worker2 SHARED worker2.cpp)
target_link_libraries(worker2 coreapi)

set_target_properties(worker2 PROPERTIES FOLDER "worker2")

install(TARGETS
    worker2
    ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
    RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
    LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
    PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}
    COMPONENT dev)