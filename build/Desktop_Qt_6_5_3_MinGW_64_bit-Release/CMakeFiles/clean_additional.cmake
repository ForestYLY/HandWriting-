# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\HandWriting_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\HandWriting_autogen.dir\\ParseCache.txt"
  "HandWriting_autogen"
  )
endif()
