#!/bin/bash

# Script that starts the CSW services, compiles and runs the test assembly and then runs the C based tests.
# Assumes that csw-services.sh and sbt are all in your shell path.

logfile=test.log
if ! hash csw-services.sh 2>/dev/null ; then
    echo >&2 "Please install csw-services.sh (from csw sources or download csw-apps zip from csw GitHub release).  Aborting."
    exit 1
fi
set -v
csw-services.sh --version v3.0.0-M1 start -e > $logfile 2>&1 &
#csw-services.sh start -e > $logfile 2>&1 &
cd testSupport || exit 1
sbt stage  >> $logfile 2>&1
test-deploy/target/universal/stage/bin/test-container-cmd-app --local test-deploy/src/main/resources/TestContainer.conf >> $logfile 2>&1 &
assemblyPid=$!
cd ..
# give the background assembly time to initialize
sleep 30
# Run the C based tests
../build/test/testPublisher
kill $assemblyPid
csw-services.sh stop >> $logfile 2>&1
