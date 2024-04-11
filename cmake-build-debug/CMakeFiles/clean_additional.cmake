# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/polynomial_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/polynomial_autogen.dir/ParseCache.txt"
  "polynomial_autogen"
  )
endif()
