module LegoPerserveranceRover {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

    enum Ports_RateGroups {
      rateGroup1
    }

    enum Ports_StaticMemory {
      framer
      deframer
      deframing
    }

  topology LegoPerserveranceRover {

    # ----------------------------------------------------------------------
    # Instances used in the topology
    # ----------------------------------------------------------------------

    instance cmdDisp
    instance commDriver
    instance deframer
    instance eventLogger
    instance fatalAdapter
    instance fatalHandler
    instance framer
    instance rateDriver
    instance rateGroup1
    instance rateGroupDriver
    instance staticMemory
    instance systemResources
    instance textLogger
    instance timeHandler
    instance tlmSend

    instance led
    instance ledPin

    instance motorDriver
    instance pwmM1
    instance pwmM2
    instance gpioM1In1
    instance gpioM1In2
    instance gpioM2In1
    instance gpioM2In2

    # ----------------------------------------------------------------------
    # Pattern graph specifiers
    # ----------------------------------------------------------------------

    command connections instance cmdDisp

    event connections instance eventLogger

    telemetry connections instance tlmSend

    text event connections instance textLogger

    time connections instance timeHandler

    # ----------------------------------------------------------------------
    # Direct graph specifiers
    # ----------------------------------------------------------------------

    connections RateGroups {
      # Block driver
      rateDriver.CycleOut -> rateGroupDriver.CycleIn

      # Rate group 1
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      rateGroup1.RateGroupMemberOut[0] -> commDriver.schedIn
      rateGroup1.RateGroupMemberOut[1] -> tlmSend.Run
      rateGroup1.RateGroupMemberOut[2] -> systemResources.run
      rateGroup1.RateGroupMemberOut[3] -> led.run
    }

    connections FaultProtection {
      eventLogger.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections Downlink {

      tlmSend.PktSend -> framer.comIn
      eventLogger.PktSend -> framer.comIn

      framer.framedAllocate -> staticMemory.bufferAllocate[Ports_StaticMemory.framer]
      framer.framedOut -> commDriver.send

      commDriver.deallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.framer]

    }
    
    connections Uplink {

      commDriver.allocate -> staticMemory.bufferAllocate[Ports_StaticMemory.deframer]
      commDriver.$recv -> deframer.framedIn
      deframer.framedDeallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.deframer]

      deframer.comOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus -> deframer.cmdResponseIn

      deframer.bufferAllocate -> staticMemory.bufferAllocate[Ports_StaticMemory.deframing]
      deframer.bufferDeallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.deframing]
      
    }

    connections LegoPerserveranceRover {
      # Add here connections to user-defined components
      motorDriver.pwmM1 -> pwmM1.setDutyCycle
      motorDriver.pwmM2 -> pwmM2.setDutyCycle
      motorDriver.gpioM1In1 -> gpioM1In1.gpioWrite
      motorDriver.gpioM1In2 -> gpioM1In2.gpioWrite
      motorDriver.gpioM2In1 -> gpioM2In1.gpioWrite
      motorDriver.gpioM2In2 -> gpioM2In2.gpioWrite

      led.gpioSet -> ledPin.gpioWrite
    }

  }

}
