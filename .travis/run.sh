#!/bin/bash
if [[ -z "$DOC_TEST_ONLY" ]]; then
  cd projects/cmake
  cmake CMakeLists.txt
  make -j 2
else
  echo "Running HeaderDoc validator..."
  bundle exec tools/translator/translate -v -i .
fi
