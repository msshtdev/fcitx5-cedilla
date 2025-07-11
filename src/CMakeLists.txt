set(CPP_SOURCES
  cedilla_engine.cpp
  cedilla_state.cpp
)

add_library(fcitx5-cedilla
  SHARED ${CPP_SOURCES}
)
set_target_properties(fcitx5-cedilla
  PROPERTIES
  PREFIX ""
)

target_include_directories(fcitx5-cedilla
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(fcitx5-cedilla
  PRIVATE
  Fcitx5::Core
)

install(TARGETS fcitx5-cedilla 
  DESTINATION "${FCITX_INSTALL_LIBDIR}/fcitx5"
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cedilla-addon.conf.in.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cedilla-addon.conf.in"
  @ONLY
)

fcitx5_translate_desktop_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cedilla-addon.conf.in"
  "cedilla-addon.conf"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cedilla-addon.conf"
  RENAME cedilla.conf
  DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon"
)

fcitx5_translate_desktop_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cedilla-im.conf.in"
  "cedilla-im.conf"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cedilla-im.conf"
  RENAME "cedilla.conf"
  DESTINATION "${FCITX_INSTALL_PKGDATADIR}/inputmethod"
)
