
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/../include
)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(stack-src SHARED ${SRC_LIST})

INSTALL(
    TARGETS stack-src
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
