module LegoPerserveranceRover {

  # ----------------------------------------------------------------------
  # Defaults
  # ----------------------------------------------------------------------

  module Default {
    constant QUEUE_SIZE = 3
    constant STACK_SIZE = 64 * 1024
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance cmdDisp: Svc.CommandDispatcher base id 0x0100 \
    queue size Default.QUEUE_SIZE\
    stack size Default.STACK_SIZE \
    priority 101

  instance eventLogger: Svc.ActiveLogger base id 0x0200 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 98

  instance tlmSend: Svc.TlmChan base id 0x0300 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 97

  # ----------------------------------------------------------------------
  # Queued component instances
  # ----------------------------------------------------------------------

  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  instance rateGroup1: Svc.PassiveRateGroup base id 0x1000

  instance commDriver: Arduino.StreamDriver base id 0x4000

  # instance commDriver: Arduino.TcpClient base id 0x4000

  instance framer: Svc.Framer base id 0x4100

  instance fatalAdapter: Svc.AssertFatalAdapter base id 0x4200

  instance fatalHandler: Svc.FatalHandler base id 0x4300

  instance timeHandler: Svc.Time base id 0x4400 \
    type "Svc::ArduinoTimeImpl" \
    at "../../fprime-arduino/Arduino/ArduinoTime/ArduinoTimeImpl.hpp"

  instance rateGroupDriver: Svc.RateGroupDriver base id 0x4500

  instance staticMemory: Svc.StaticMemory base id 0x4600

  instance textLogger: Svc.PassiveTextLogger base id 0x4700

  instance deframer: Svc.Deframer base id 0x4800

  instance systemResources: Svc.SystemResources base id 0x4900

  instance rateDriver: Arduino.HardwareRateDriver base id 0x4A00

  instance led: Components.Led base id 0x9000

  instance ledPin: Arduino.GpioDriver base id 0x9100

  instance motorDriver: Components.L293D base id 0x10000

  instance pwmM1: Arduino.PwmDriver base id 0x10100

  instance pwmM2: Arduino.PwmDriver base id 0x10200

  instance gpioM1In1: Arduino.GpioDriver base id 0x10300

  instance gpioM1In2: Arduino.GpioDriver base id 0x10400

  instance gpioM2In1: Arduino.GpioDriver base id 0x10500

  instance gpioM2In2: Arduino.GpioDriver base id 0x10600

}
