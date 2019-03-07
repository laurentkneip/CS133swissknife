add_executable( make_sqrt_lut make_sqrt_lut.cpp )
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/sqrt_lut.inc
  DEPENDS ${PROJECT_BINARY_DIR}/sqrt_lut.inc
  COMMAND make_sqrt_lut ${PROJECT_BINARY_DIR}/sqrt_lut.inc )
add_custom_target(run ALL DEPENDS ${PROJECT_BINARY_DIR}/sqrt_lut.inc )