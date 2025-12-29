add_library(peanut_gb INTERFACE)

target_sources(peanut_gb
INTERFACE
   minigb_apu.c
   gb.c
)