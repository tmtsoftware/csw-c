Testing C Event Publishing
==========================

In order to test publishing CSW events from C, we need a test assembly that subscribes to the events.
One is provided under the `testSupport` directory.

## Running the Test

* First start the CSW services

    csw-services.sh start

* Then start the test assembly:

    cd testSupport
    sbt stage
    cd test-deploy
    ./target/universal/stage/bin/test-container-cmd-app --local ./src/main/resources/TestContainer.conf
 
 * Then run the test publisher defined in this directory:
 
    testPublisher
 
 The test assembly writes a file `/tmp/TestAssemblyHandlers.out` containing the JSON for the received events.
 The testPublisher compares that file to a file that was previously saved and is known to be correct.
 It then prints out "All Tests Passed" if the files are the same.
 
 (Note that the EventTime fields and Ids are changed in the JSON file for comparison).
 