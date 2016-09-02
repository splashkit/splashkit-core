#!/bin/bash
if [[ -z "$DOC_TEST_ONLY" ]]; then
  cmake projects/cmake
  make -j 2 -C projects/cmake sktest
else
  echo "Running HeaderDoc validator..."
  tools/translator/translate -v -i .
fi
