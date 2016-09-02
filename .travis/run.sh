#!/bin/bash
if [[ -z "$DOC_TEST_ONLY" ]]; then
  cmake projects/cmake
  make -j 2 -C projects/cmake all
else
  .travis/validate_docs.sh
fi
