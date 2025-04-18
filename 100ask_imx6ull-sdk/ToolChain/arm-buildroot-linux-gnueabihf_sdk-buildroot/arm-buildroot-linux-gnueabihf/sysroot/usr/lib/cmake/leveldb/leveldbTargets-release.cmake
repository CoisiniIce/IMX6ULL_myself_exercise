#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "leveldb::leveldb" for configuration "Release"
set_property(TARGET leveldb::leveldb APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(leveldb::leveldb PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libleveldb.so.1.22.0"
  IMPORTED_SONAME_RELEASE "libleveldb.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS leveldb::leveldb )
list(APPEND _IMPORT_CHECK_FILES_FOR_leveldb::leveldb "${_IMPORT_PREFIX}/lib/libleveldb.so.1.22.0" )

# Import target "leveldb::memenv" for configuration "Release"
set_property(TARGET leveldb::memenv APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(leveldb::memenv PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libmemenv.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS leveldb::memenv )
list(APPEND _IMPORT_CHECK_FILES_FOR_leveldb::memenv "${_IMPORT_PREFIX}/lib/libmemenv.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
