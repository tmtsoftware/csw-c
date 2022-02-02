#!/bin/bash

# Script that starts the CSW services, compiles and runs the test assembly and then runs the python tests.
# Assumes that cs, sbt, pytest are all in your shell path.

CSW_VERSION=4.0.1-RC1
#CSW_VERSION=a9073713d8b5de90a817e08b31629a7176e1b4fe

logfile=test.log
if ! hash cs 2>/dev/null ; then
    echo >&2 "Please install coursier (https://get-coursier.io/).  Aborting."
    exit 1
fi
set -x
cs launch csw-services:$CSW_VERSION -- start -e > $logfile 2>&1 &
cd testSupport || exit 1
sbt stage  >> $logfile 2>&1
test-deploy/target/universal/stage/bin/test-container-cmd-app --local test-deploy/src/main/resources/TestContainer.conf >> $logfile 2>&1 &
assemblyPid=$!
cd ..
# give the background assembly time to initialize
sleep 30
export LD_LIBRARY_PATH=`pwd`/build/csw
# Run the C based tests
../build/test/testPublisher
kill $assemblyPid
# Kill csw-services
kill `ps aux | grep 'csw-services' | grep -v grep | awk '{print $2}'`
