import org.scalafmt.sbt.ScalafmtPlugin.autoImport.scalafmtOnCompile
import sbt.Keys._
import sbt._
import sbt.plugins.JvmPlugin

object Common extends AutoPlugin {

  override def trigger: PluginTrigger = allRequirements

  override def requires: Plugins = JvmPlugin

  override lazy val projectSettings: Seq[Setting[_]] = Seq(
    organization := "com.github.tmtsoftware.csw",
    organizationName := "Thirty Meter Telescope International Observatory",
    scalaVersion := Libs.ScalaVersion,
    homepage := Some(url("https://github.com/tmtsoftware/csw")),

    scalacOptions ++= Seq(
      "-encoding",
      "UTF-8",
      "-feature",
      "-unchecked",
      "-deprecation"
    ),
    Compile / doc / javacOptions ++= Seq("-Xdoclint:none"),
    Test / testOptions ++= Seq(
      // show full stack traces and test case durations
      Tests.Argument("-oDF"),
      // -v Log "test run started" / "test started" / "test run finished" events on log level "info" instead of "debug".
      // -a Show stack traces and exception class name for AssertionErrors.
      Tests.Argument(TestFrameworks.JUnit, "-v", "-a")
    ),
    resolvers += "jitpack" at "https://jitpack.io",
    version := "0.0.1",
    fork := true,
    Test / parallelExecution := false,
    autoCompilerPlugins := true,
    if (formatOnCompile) scalafmtOnCompile := true else scalafmtOnCompile := false
  )

  private def formatOnCompile = sys.props.get("format.on.compile") match {
    case Some("false") ⇒ false
    case _             ⇒ true
  }
}
