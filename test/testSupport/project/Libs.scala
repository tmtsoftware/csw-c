import sbt._

object Libs {
  val ScalaVersion = "2.13.8"

  val `scala-async`     = "org.scala-lang.modules" %% "scala-async"     % "1.0.1"  //BSD 3-clause "New" or "Revised" License
}

object AkkaHttp {
  val Version                = "10.2.7"
  val `akka-http-spray-json` = "com.typesafe.akka" %% "akka-http-spray-json" % Version
}

object CSW {
//    val Version = "4.0.1"
  //  val Version = "0.1.0-SNAPSHOT"
    val Version = "43c9a3492ccdc8d1a5d8a1311d3127f795b2d2b9"

  val `csw-framework` = "com.github.tmtsoftware.csw" %% "csw-framework" % Version
  val `csw-testkit`   = "com.github.tmtsoftware.csw" %% "csw-testkit" % Version
}
