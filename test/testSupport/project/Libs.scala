import sbt._

object Libs {
  val ScalaVersion = "3.6.2"
}

object CSW {
    val Version = "2f05249"

  val `csw-framework` = "com.github.tmtsoftware.csw" %% "csw-framework" % Version
  val `csw-testkit`   = "com.github.tmtsoftware.csw" %% "csw-testkit" % Version
}
