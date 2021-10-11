# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# prebuild
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Build/BuildConfig.h.in"
    "${PROJECT_BINARY_DIR}/BuildConfig.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/linux/etc/init/OpcUaPiXtendServer.conf.in"
    "${PROJECT_BINARY_DIR}/OpcUaPiXtendServer.conf"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/linux/etc/init.d/OpcUaPiXtendServer.in"
    "${PROJECT_BINARY_DIR}/OpcUaPiXtendServer"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/linux/usr/lib/systemd/system/OpcUaPiXtendServer.service.in"
    "${PROJECT_BINARY_DIR}/OpcUaPiXtendServer.service"
)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
include_directories(
    ${OPCUASTACK_INSTALL_PREFIX}/usr/include/OpcUaStack${OPCUASTACK_VERSION_MAJOR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

set(HardwareAccessLibs
    "" # hardware access for pc/dummy - no libs needed
)

if (${OPTION_OPCUAPIXTENDSERVER_SPI} STREQUAL SPI_ON)
    set(HardwareAccessLibs
        pixtend
        wiringPi
    )

    file(
        GLOB
        OpcUaPiXtendServer_PiXtendAccess_SRC
        ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/PiXtend/*.cpp
        ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/ModuleSpi/*.cpp
    )
elseif (${OPTION_OPCUAPIXTENDSERVER_SPI} STREQUAL SPI_DUMMY)
    file(
        GLOB
        OpcUaPiXtendServer_PiXtendAccess_SRC
        ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/PiXtend/*.cpp
        ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/ModuleDummy/*.cpp
    )
else ()
    file(
        GLOB
        OpcUaPiXtendServer_PiXtendAccess_SRC
        ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/PiXtend/*.cpp
    )
endif()

add_library(
    PiXtendAccess STATIC
    ${OpcUaPiXtendServer_PiXtendAccess_SRC}
)

file(
    GLOB 
    OpcUaPiXtendServer_PiXtendTool_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Tools/PiXtendTool*.cpp
)

add_library(
    PiXtendTool STATIC
    ${OpcUaPiXtendServer_PiXtendTool_SRC}
)

file(
    GLOB 
    OpcUaPiXtendServer_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Library/*.cpp
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/OpcUaServer/*.cpp
)

add_library(
    OpcUaPiXtendServer SHARED
    ${OpcUaPiXtendServer_SRC}
)

target_link_libraries(
    OpcUaPiXtendServer
    ${pthread}
    PiXtendAccess
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${OPCUASTACK_LIBRARY_SERVER}
    ${OPCUASTACK_LIBRARY_PUBSUB}
    ${Boost_LIBRARIES}
    ${HardwareAccessLibs}
)

add_executable( 
    pixtendOpcUa
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Tools/pixtend.cpp
)

target_link_libraries(
    pixtendOpcUa
    PiXtendTool
    PiXtendAccess
    ${OPCUASTACK_LIBRARY_CORE}
    ${Boost_LIBRARIES}
    ${HardwareAccessLibs}
) 

if (WIN32)
    target_link_libraries(OpcUaPiXtendServer wsock32 ws2_32)

    if (MINGW)
        set(CMAKE_SHARED_LIBRARY_PREFIX "")
    endif()
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# add configuration to cpp build
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
if (${OPTION_OPCUAPIXTENDSERVER_SPI} STREQUAL SPI_ON)
    add_definitions(-DOPTION_OPCUAPIXTENDSERVER_SPI_ON)
elseif (${OPTION_OPCUAPIXTENDSERVER_SPI} STREQUAL SPI_DUMMY)
    add_definitions(-DOPTION_OPCUAPIXTENDSERVER_DUMMY)
else ()
    add_definitions(-DOPTION_OPCUAPIXTENDSERVER_SPI_OFF)
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

file (GLOB CONFIG_FILES ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Config/*.xml)
install(TARGETS OpcUaPiXtendServer DESTINATION ${INSTALL_PREFIX}/lib)
install(TARGETS pixtendOpcUa DESTINATION ${INSTALL_PREFIX}/bin)

if (WIN32)
    install(FILES ${CONFIG_FILES} DESTINATION ${INSTALL_PREFIX}/../etc/OpcUaStack/OpcUaPiXtendServer) 
    install(FILES ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/linux/log/README DESTINATION ${INSTALL_PREFIX}/../var/log/OpcUaStack/OpcUaPiXtendServer)
    install(DIRECTORY DESTINATION ${INSTALL_PREFIX}/../var/log/OpcUaStack/OpcUaPiXtendServer)
else()    
    install(FILES ${CONFIG_FILES} DESTINATION ${INSTALL_PREFIX}/../etc/OpcUaStack/OpcUaPiXtendServer) 
    install(FILES ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/linux/log/README DESTINATION /var/log/OpcUaStack/OpcUaPiXtendServer)
    install(DIRECTORY DESTINATION /var/log/OpcUaStack/OpcUaPiXtendServer)

    install(PROGRAMS ${PROJECT_BINARY_DIR}/OpcUaPiXtendServer DESTINATION /etc/init.d)
    install(FILES ${PROJECT_BINARY_DIR}/OpcUaPiXtendServer.conf DESTINATION /etc/init)
    install(FILES ${PROJECT_BINARY_DIR}/OpcUaPiXtendServer.service DESTINATION /usr/lib/systemd/system)
endif()

if (CPACK_BINARY_DEB)
    set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/postinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/preinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/prerm"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/postrm")
endif()

if (CPACK_BINARY_RPM)
    set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/postinst)
    set(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaPiXtendServer/linux/script/prerm)
endif()
