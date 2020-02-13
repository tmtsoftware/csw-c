package org.tmt.csw.testassembly

import akka.actor.typed.Behavior
import akka.actor.typed.scaladsl.{ActorContext, Behaviors}
import csw.command.client.messages.TopLevelActorMessage
import csw.framework.models.CswContext
import csw.framework.scaladsl.ComponentHandlers
import csw.location.api.models.TrackingEvent
import csw.logging.api.scaladsl.Logger
import csw.params.commands.CommandResponse._
import csw.params.commands.ControlCommand
import csw.time.core.models.UTCTime
import csw.params.core.models.Id
import csw.params.events.{Event, EventKey, EventName, SystemEvent}

import scala.concurrent.{ExecutionContextExecutor, Future}
import TestAssemblyHandlers._
import csw.params.core.generics.{Key, KeyType}
import csw.prefix.models.Prefix
import csw.prefix.models.Subsystem.CSW

object TestAssemblyHandlers {

  // Event published by C code and subscribed to here
  private val prefix = Prefix(CSW, "TestPublisher")
  private val eventNames = List(
    "SimpleDoubleEvent",
    "IntArrayMatrixEvent",
    "DoubleArrayMatrtixEvent",
    "AltAzCoordEvent",
    "CometCoordEvent",
    "MinorPlanetCoordEvent",
    "SolarSystemCoordsEvent",
    "EqCoordsEvent",
    "StructEvent"
  ).map(EventName).toSet
  private val eventKeys = eventNames.map(EventKey(prefix, _))

  private def checkSimpleDoubleEvent(event: SystemEvent): Unit = {
    val eventValueKey: Key[Double] = KeyType.DoubleKey.make("DoubleValue")
    event.get(eventValueKey)
      .foreach { p =>
        val eventValue = p.head
      }

  }

  private def checkEvent(event: SystemEvent): Unit = {
    event.eventName.name match {
      case "SimpleDoubleEvent" => checkSimpleDoubleEvent(event)
      case "IntArrayMatrixEvent" =>
      case "DoubleArrayMatrtixEvent" =>
      case "AltAzCoordEvent" =>
      case "CometCoordEvent" =>
      case "MinorPlanetCoordEvent" =>
      case "SolarSystemCoordsEvent" =>
      case "EqCoordsEvent" =>
      case "StructEvent" =>
    }
  }

  // Actor to receive events
  private def eventHandler(log: Logger): Behavior[Event] = {
    Behaviors.receive { (_, msg) =>
      msg match {
        case event: SystemEvent =>
          log.info(s"received event: $event")
          try{
            checkEvent(event)
          } catch {
            case ex: Exception =>
              log.error(s"Test failed for event $event", ex = ex)
          }
//          val eventValueKey: Key[Int] = KeyType.IntKey.make("eventValue")
//          event.get(eventValueKey)
//            .foreach { p =>
//              val eventValue = p.head
//              log.info(s"Received event with event time: ${event.eventTime} with value: $eventValue")
//            }
          Behaviors.same
        case x =>
          log.error(s"Unexpected message: $x")
          Behaviors.same
      }
    }
  }
}

/**
 * Domain specific logic should be written in below handlers.
 * This handlers gets invoked when component receives messages/commands from other component/entity.
 * For example, if one component sends Submit(Setup(args)) command to TestHcd,
 * This will be first validated in the supervisor and then forwarded to Component TLA which first invokes validateCommand hook
 * and if validation is successful, then onSubmit hook gets invoked.
 * You can find more information on this here : https://tmtsoftware.github.io/csw/commons/framework.html
 */
class TestAssemblyHandlers(ctx: ActorContext[TopLevelActorMessage], cswCtx: CswContext) extends ComponentHandlers(ctx, cswCtx) {

  import cswCtx._
  implicit val ec: ExecutionContextExecutor = ctx.executionContext
  private val log                           = loggerFactory.getLogger

  override def initialize(): Future[Unit] = {
    log.info("Initializing test assembly...")
    startSubscribingToEvents()
    Future.unit
  }

  private def startSubscribingToEvents(): Unit = {
    val eventHandlerActor = ctx.spawn(eventHandler(log), "eventHandlerActor")
    eventService.defaultSubscriber.subscribeActorRef(eventKeys, eventHandlerActor)
  }

  override def onLocationTrackingEvent(trackingEvent: TrackingEvent): Unit = {}

  override def validateCommand(runId: Id, controlCommand: ControlCommand): ValidateCommandResponse = Accepted(runId)

  override def onSubmit(runId: Id, controlCommand: ControlCommand): SubmitResponse = Completed(runId)

  override def onOneway(runId: Id, controlCommand: ControlCommand): Unit = {}

  override def onShutdown(): Future[Unit] = { Future.unit }

  override def onGoOffline(): Unit = {}

  override def onGoOnline(): Unit = {}

  override def onDiagnosticMode(startTime: UTCTime, hint: String): Unit = {}

  override def onOperationsMode(): Unit = {}

}
