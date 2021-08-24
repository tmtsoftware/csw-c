# Releasing

* Check/update the CSW version in csw/CMakeLists.txt, test/testSupport/project/Libs.scala and test/runTest.sh.

* Run "make test" in top level dir.
  (This assumes csw-services is in the path and starts a scala based backend and compares results with the C version.)
 
* Make GitHub release

