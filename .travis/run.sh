#!/bin/bash
if [[ -z "$DOC_TEST_ONLY" ]]; then
  cd projects/cmake
  cmake CMakeLists.txt
  make -j 2
  cd ../../bin
  ./skunit_tests
else
  echo "Running HeaderDoc validator..."
  TRANS_SRC=tools/translator
  BUNDLE_GEMFILE=$TRANS_SRC/Gemfile bundle exec $TRANS_SRC/translate -v -i .
fi
