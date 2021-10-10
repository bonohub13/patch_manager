add_library(utils
  SHARED
  src/add_patch.cpp
)

target_include_directories(utils
  PRIVATE ${PROJECT_SOURCE_DIR}/include
)
