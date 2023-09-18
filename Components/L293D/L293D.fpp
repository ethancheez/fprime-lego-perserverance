module MotorControl {

    enum MOVE_DIRECTION {
        FORWARD,
        BACKWARD,
        STOP
    }

}

module Components {
    @ L293D Motor Driver IC
    passive component L293D {

        output port pwmM1: Drv.DutyCycle

        output port pwmM2: Drv.DutyCycle

        output port gpioM1In1: Drv.GpioWrite

        output port gpioM1In2: Drv.GpioWrite

        output port gpioM2In1: Drv.GpioWrite

        output port gpioM2In2: Drv.GpioWrite

        sync command Drive(direction: MotorControl.MOVE_DIRECTION, dutyCycle: U8)

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

    }
}