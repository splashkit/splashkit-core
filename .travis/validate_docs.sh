#!/bin/bash
if [[ $TRAVIS_OS_NAME == 'osx' ]]; then
  echo "Running HeaderDoc validator..."
  tools/translator/translate -v -i .
fi
