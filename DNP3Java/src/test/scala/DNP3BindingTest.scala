/**
 * Copyright 2011 Green Energy Corp.
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Green Energy
 * Corp licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package org.totalgrid.reef.protocol.dnp3

import org.totalgrid.reef.protocol.dnp3.mock._

import org.scalatest.matchers.ShouldMatchers
import org.scalatest.junit.JUnitRunner
import org.junit.runner.RunWith
import org.scalatest.FunSuite


@RunWith(classOf[JUnitRunner])
class DNP3BindingTest extends FunSuite with ShouldMatchers {

  val startPort = 32323
  val lev = FilterLevel.LEV_INFO

  class MockStateObserver {
    import scala.collection.mutable.{ Queue, Map }
    val states = Map.empty[String, Queue[StackStates]]

    var observers = List.empty[IStackObserver]
    def getObserver(name: String): IStackObserver = {
      val obs = new IStackObserver {
        override def OnStateChange(state: StackStates) {
          states.get(name) match {
            case Some(l: Queue[StackStates]) => l.enqueue(state)
            case None => states += name -> Queue(state)
          }
        }
      }
      // need to keep a reference to the observer so it doesn't get GCed
      observers ::= obs
      obs
    }

    def checkStates(names: List[String], expected: List[StackStates]) {
      names.foreach { name =>
        states.get(name).map { _.toList }.getOrElse(List.empty[StackStates]) should equal(expected)
      }
    }
  }

  def fixture(testFun: StackManager => Unit) = {
    val sm = new StackManager
    try {
      testFun(sm)
    } finally {
      sm.Shutdown()
    }

  }

  /// This test shows that the startup/teardown behavior is working without crashing
  test("StartupTeardownOnJVM") {
    val num_port = 100
    val num_stack = 10

    fixture { sm =>

      val stateObserver = new MockStateObserver

      var names = List.empty[String]

      // startup <num_stack> masters on <num_port> ports
      (1 to num_port).foreach { port =>

        val s = new PhysLayerSettings(FilterLevel.LEV_WARNING, 1000)
        sm.AddTCPv4Client(port.toString, s, "127.0.0.1", startPort)

        (1 to num_stack).foreach { stack =>
          val name = "port-" + port + "-stack" + stack

          names ::= name

          val cfg = new MasterStackConfig

          cfg.getLink.setLocalAddr(stack)

          cfg.getMaster.setMpObserver(stateObserver.getObserver(name))

          // the masters won't get any data, so setting the IPublisher to null is OK
          sm.AddMaster(port.toString, name, FilterLevel.LEV_WARNING, null, cfg)
        }
      }

      stateObserver.checkStates(names, List(StackStates.SS_COMMS_DOWN))

    }
  }

  test("MasterToSlaveOnJVM") {
    val num_pairs = 100
    val port_start = startPort
    val port_end = port_start + num_pairs - 1
    val counter = new CountingPublisher
    val stateObserver = new MockStateObserver
    var names = List.empty[String]

    fixture { sm =>

     // sm.AddLogHook(adapter)

      val master = new MasterStackConfig
      master.getMaster.setIntegrityRate(60000)
      val slave = new SlaveStackConfig

      slave.setDevice(new DeviceTemplate(100, 100, 100))

      val s = new PhysLayerSettings(lev, 1000)
      (port_start to port_end).foreach { port =>
        val client = "client-" + port
        val server = "server-" + port
        sm.AddTCPv4Client(client, s, "127.0.0.1", port)
        sm.AddTCPv4Server(server, s, "0.0.0.0", port)

        master.getMaster.setMpObserver(stateObserver.getObserver(server))
        names ::= server

        sm.AddMaster(client, client, lev, counter.newPublisher, master)
        sm.AddSlave(server, server, lev, null, slave)
      }

      counter.waitForMinMessages(300, 10000) should equal(true)

    }

    // make sure we got the down-up-down callbacks we expected
    stateObserver.checkStates(names, List(StackStates.SS_COMMS_DOWN, StackStates.SS_COMMS_UP, StackStates.SS_COMMS_DOWN))
  }

}
