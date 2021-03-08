file(REMOVE_RECURSE
  "libsiphon.a"
  "libsiphon.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/siphon-static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
