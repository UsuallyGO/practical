
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/../include
)

AUX_SOURCE_DIRECTORY(. SRC_STACK)
ADD_EXECUTABLE(ustack ${SRC_STACK})

IF(WIN32)
    IF(MSVC)
    ELSE(MSVC)
    ENDIF(MSVC)
ELSE(WIN32)
    FIND_LIBRARY(liblist_core "list-core")
    FIND_LIBRARY(libstack_src "stack-src")
ENDIF(WIN32)
IF(NOT liblist_core MATCHES liblist_core-NOTFOUND)
    TARGET_LINK_LIBRARIES(ustack ${liblist_core})
ENDIF()
IF(NOT libstack_src MATCHES libstack_src-NOTFOUND)
    TARGET_LINK_LIBRARIES(ustack ${libstack_src})
ENDIF()

INSTALL(
    TARGETS ustack
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
