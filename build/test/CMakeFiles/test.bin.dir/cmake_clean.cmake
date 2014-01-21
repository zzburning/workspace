FILE(REMOVE_RECURSE
  "CMakeFiles/test.bin.dir/test.c.o"
  "../test.bin.pdb"
  "../test.bin"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/test.bin.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
