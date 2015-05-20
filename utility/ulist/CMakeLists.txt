
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/../include
)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(ulist ${SRC_LIST})

IF(WIN32)
    IF(MSVC)
    ELSE(MSVC)
    ENDIF(MSVC)
ELSE(WIN32)
    FIND_LIBRARY(liblist_core "list-core")
    FIND_LIBRARY(liblist_src "list-src")
ENDIF(WIN32)
IF(NOT liblist_core MATCHES liblist_core-NOTFOUND)
    TARGET_LINK_LIBRARIES(ulist ${liblist_core})
ENDIF()
IF(NOT liblist_src MATCHES liblist_src-NOTFOUND)
    TARGET_LINK_LIBRARIES(ulist ${liblist_src})
ENDIF()

INSTALL(
    TARGETS ulist
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

INSTALL(
    FILES ${PROJECT_SOURCE_DIR}/ulist/temp.txt
    DESTINATION ${CMAKE_INSTALL_PREFIX}/utility/ulist/
)
