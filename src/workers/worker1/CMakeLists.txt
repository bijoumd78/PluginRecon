add_library(worker1 SHARED worker1.cpp)
target_link_libraries(worker1 coreapi)

set_target_properties(worker1 PROPERTIES FOLDER "worker1")

install(TARGETS
    worker1
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