#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Grantlee5::Templates" for configuration "Release"
set_property(TARGET Grantlee5::Templates APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::Templates PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt5::Script"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libGrantlee_Templates.so.5.1.0"
  IMPORTED_SONAME_RELEASE "libGrantlee_Templates.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::Templates )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::Templates "${_IMPORT_PREFIX}/lib/libGrantlee_Templates.so.5.1.0" )

# Import target "Grantlee5::loadertags" for configuration "Release"
set_property(TARGET Grantlee5::loadertags APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::loadertags PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_loadertags.so"
  IMPORTED_NO_SONAME_RELEASE "TRUE"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::loadertags )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::loadertags "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_loadertags.so" )

# Import target "Grantlee5::defaulttags" for configuration "Release"
set_property(TARGET Grantlee5::defaulttags APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::defaulttags PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_defaulttags.so"
  IMPORTED_NO_SONAME_RELEASE "TRUE"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::defaulttags )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::defaulttags "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_defaulttags.so" )

# Import target "Grantlee5::defaultfilters" for configuration "Release"
set_property(TARGET Grantlee5::defaultfilters APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::defaultfilters PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_defaultfilters.so"
  IMPORTED_NO_SONAME_RELEASE "TRUE"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::defaultfilters )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::defaultfilters "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_defaultfilters.so" )

# Import target "Grantlee5::i18ntags" for configuration "Release"
set_property(TARGET Grantlee5::i18ntags APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::i18ntags PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_i18ntags.so"
  IMPORTED_NO_SONAME_RELEASE "TRUE"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::i18ntags )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::i18ntags "${_IMPORT_PREFIX}/lib/grantlee/5.1/grantlee_i18ntags.so" )

# Import target "Grantlee5::TextDocument" for configuration "Release"
set_property(TARGET Grantlee5::TextDocument APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Grantlee5::TextDocument PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libGrantlee_TextDocument.so.5.1.0"
  IMPORTED_SONAME_RELEASE "libGrantlee_TextDocument.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS Grantlee5::TextDocument )
list(APPEND _IMPORT_CHECK_FILES_FOR_Grantlee5::TextDocument "${_IMPORT_PREFIX}/lib/libGrantlee_TextDocument.so.5.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
