#!/bin/bash

# Script that starts the CSW services, compiles and runs the test assembly and then runs the C based tests.
# Assumes that csw-services and sbt are all in your shell path.

CSW_VERSION=4.0.0-M1
logfile=test.log
if ! hash csw-services 2>/dev/null ; then
    echo >&2 "Please install csw-services (run: cs install csw-services $CSW_VERSION).  Aborting."
    exit 1
fi
csw_services_version=`csw-services --help | grep Main | sed -e 's/Main //'`
if test "$csw_services_version" != "$CSW_VERSION"; then
    echo >&2 "CSW services version $csw_services_version != $CSW_VERSION: Please install csw-services (run: cs install csw-services $CSW_VERSION).  Aborting."
    exit 1
fi
set -v
csw-services start -e > $logfile 2>&1 &
cswServicesPid=$!
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
#csw-services stop  >> $logfile 2>&1
kill $cswServicesPid
