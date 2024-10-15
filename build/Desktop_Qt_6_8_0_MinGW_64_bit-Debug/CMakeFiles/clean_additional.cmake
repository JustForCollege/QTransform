# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TheImageInverter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TheImageInverter_autogen.dir\\ParseCache.txt"
  "TheImageInverter_autogen"
  )
endif()
