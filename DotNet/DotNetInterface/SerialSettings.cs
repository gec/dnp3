﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DNP3.Interface
{
    public enum Parity {
	    NONE,
	    EVEN,
	    ODD
    }

    public enum FlowControl {
	    NONE,
	    HARDWARE,
	    XONXOFF
    }    

    public class SerialSettings {
        SerialSettings(String port, int baud, int dataBits, int stopBits, Parity parity, FlowControl flowControl)
        {
            this.port = port;
            this.baud = baud;
            this.dataBits = dataBits;
            this.stopBits = stopBits;
            this.parity = parity;
            this.flowControl = flowControl;
        }

        public readonly String port;
        public readonly int baud;
        public readonly int dataBits;
        public readonly int stopBits;
        public readonly Parity parity;
        public readonly FlowControl flowControl;
    }
}
