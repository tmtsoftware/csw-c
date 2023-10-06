import sbt._

object Libs {
  val ScalaVersion = "3.3.1"
}

object CSW {
//    val Version = "5.0.0"
  //  val Version = "0.1.0-SNAPSHOT"
    val Version = "6f29ed1"

  val `csw-framework` = "com.github.tmtsoftware.csw" %% "csw-framework" % Version
  val `csw-testkit`   = "com.github.tmtsoftware.csw" %% "csw-testkit" % Version
}
