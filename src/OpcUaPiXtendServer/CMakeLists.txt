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

file(
    GLOB 
    OpcUaPiXtendServer_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Library/*.cpp
)

add_library(
    OpcUaPiXtendServer SHARED
    ${OpcUaPiXtendServer_SRC}
)

target_link_libraries(
    OpcUaPiXtendServer
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${OPCUASTACK_LIBRARY_SERVER}
    ${OPCUASTACK_LIBRARY_PUBSUB}
    ${Boost_LIBRARIES}
)

file(
    GLOB 
    OpcUaPiXtendServer_PiXtendLib_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/PiXtend/*.cpp
)

add_library(
    PiXtendLib STATIC
    ${OpcUaPiXtendServer_PiXtendLib_SRC}
)

add_executable( 
    pixtend
    ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/PiXtend/pixtend.cpp
) 

target_link_libraries(
    pixtend
    PiXtendLib
    ${Boost_LIBRARIES}
)


# FIXME: build pixtendLib library
# FIXME: build pixtend tool
# FIXME: Example: https://gitlab.asneg.de/konvekta/opcuadiaggateway/-/blob/work/src/OpcUaDiagGateway/CMakeLists.txt

if (WIN32)
    target_link_libraries(OpcUaPiXtendServer wsock32 ws2_32)

    if (MINGW)
        set(CMAKE_SHARED_LIBRARY_PREFIX "")
    endif()
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# config moduls by env variables
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
if (DEFINED ENV{OPCUAPIXTENDSERVER_MODUL_V2S_DUMMY})
    add_definitions(-DOPCUAPIXTENDSERVER_MODUL_V2S_DUMMY)
    message(STATUS "Modul V2S activate dummy")
endif ()

if (DEFINED ENV{OPCUAPIXTENDSERVER_MODUL_V2L_DUMMY})
    add_definitions(-DOPCUAPIXTENDSERVER_MODUL_V2L_DUMMY)
    message(STATUS "Modul V2L activate dummy")
endif ()

if (DEFINED ENV{OPCUAPIXTENDSERVER_MODUL_EIOAO_DUMMY})
    add_definitions(-DOPCUAPIXTENDSERVER_MODUL_EIOAO_DUMMY)
    message(STATUS "Modul EIOAO activate dummy")
endif ()

if (DEFINED ENV{OPCUAPIXTENDSERVER_MODUL_EIODO_DUMMY})
    add_definitions(-DOPCUAPIXTENDSERVER_MODUL_EIODO_DUMMY)
    message(STATUS "Modul EIODO activate dummy")
endif ()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

file (GLOB CONFIG_FILES ${PROJECT_SOURCE_DIR}/OpcUaPiXtendServer/Config/*.xml)
install(TARGETS OpcUaPiXtendServer DESTINATION ${INSTALL_PREFIX}/lib)

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
