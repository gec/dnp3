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
package org.totalgrid.dnp3.mock

import org.totalgrid.dnp3._
import scala.collection.mutable

class MockCommandAcceptor extends ICommandAcceptor {
  val commands = new mutable.Queue[Tuple3[BinaryOutput, Long, Int]]
  val setpoints = new mutable.Queue[Tuple3[Setpoint, Long, Int]]

  override def AcceptCommand(obj: BinaryOutput, index: Long, seq: Int, accept: IResponseAcceptor, isDirectOperate: Boolean) {
    commands += Tuple3(obj, index, seq)
  }
  override def AcceptCommand(obj: Setpoint, index: Long, seq: Int, accept: IResponseAcceptor, isDirectOperate: Boolean) {
    setpoints += Tuple3(obj, index, seq)
  }
}
