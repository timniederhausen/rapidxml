# Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 3.8)

project(rapidxml VERSION 1.13)

include(GNUInstallDirs)

# Determine if RapidXML is built as a subproject (using add_subdirectory) or if it is the root project.
if (NOT DEFINED RAPIDXML_ROOT_PROJECT)
  set(RAPIDXML_ROOT_PROJECT OFF)
  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(RAPIDXML_ROOT_PROJECT ON)
  endif ()
endif ()

option(RAPIDXML_BUILD_TESTS "Build tests as well" ${RAPIDXML_ROOT_PROJECT})
option(RAPIDXML_INSTALL "Provide installable targets" ${RAPIDXML_ROOT_PROJECT})

add_library(${PROJECT_NAME} INTERFACE)
add_library(rapidxml::rapidxml ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if (cxx_std_11 IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)
else ()
  message(WARNING "Feature cxx_std_11 is unknown for the CXX compiler")
endif ()

if (RAPIDXML_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()

if (RAPIDXML_INSTALL)
  include(CMakePackageConfigHelpers)
  set(RAPIDXML_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
  set(version_config ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
  set(targets_export_name rapidxml-targets)

  # Generate the version, config and target files into the build directory.
  write_basic_package_version_file(${version_config} COMPATIBILITY SameMajorVersion)
  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/rapidxml-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${RAPIDXML_CMAKE_DIR})

  set(INSTALL_TARGETS ${PROJECT_NAME})

  # Install the library and headers.
  install(TARGETS ${INSTALL_TARGETS} EXPORT ${targets_export_name}
          LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/rapidxml"
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  # Use a namespace because CMake provides better diagnostics for namespaced
  # imported targets.
  export(TARGETS ${INSTALL_TARGETS} NAMESPACE rapidxml::
         FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

  # Install version, config and target files.
  install(FILES ${project_config} ${version_config} DESTINATION ${RAPIDXML_CMAKE_DIR})
  install(EXPORT ${targets_export_name} DESTINATION ${RAPIDXML_CMAKE_DIR}
          NAMESPACE rapidxml::)
endif ()
