set( SWISSKNIFE_SRC tools/base_logger.cpp
                    tools/console_logger.cpp
                    tools/file_logger.cpp
                    lut/sqrt_calc.cpp
                    profiling/lap_timer.cpp )

add_library(swissknife ${SWISSKNIFE_SRC} )