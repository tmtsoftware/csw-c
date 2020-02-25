#!/bin/bash

# Script that starts the CSW services, compiles and runs the test assembly and then runs the C based tests.
# Assumes that csw-services.sh and sbt are all in your shell path.

logfile=test.log
set -v
csw-services.sh start -e > $logfile 2>&1 &
cd testSupport
sbt stage  >> $logfile 2>&1
test-deploy/target/universal/stage/bin/test-container-cmd-app --local test-deploy/src/main/resources/TestContainer.conf >> $logfile 2>&1 &
assemblyPid=$!
cd ..
# give the background assembly time to initialize
sleep 5
# Run the C based tests
../build/test/testPublisher
kill $assemblyPid
csw-services.sh stop >> $logfile 2>&1
