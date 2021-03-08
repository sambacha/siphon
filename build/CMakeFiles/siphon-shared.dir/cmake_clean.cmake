file(REMOVE_RECURSE
  "libsiphon.0.2.6.dylib"
  "libsiphon.dylib"
  "libsiphon.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/siphon-shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
