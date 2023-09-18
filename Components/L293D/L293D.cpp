// ======================================================================
// \title  L293D.cpp
// \author ethan
// \brief  cpp file for L293D component implementation class
// ======================================================================


#include <Components/L293D/L293D.hpp>
#include <FpConfig.hpp>

namespace Components {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  L293D ::
    L293D(
        const char *const compName
    ) : L293DComponentBase(compName)
  {

  }

  L293D ::
    ~L293D()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void L293D ::
    Drive_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        MotorControl::MOVE_DIRECTION direction,
        U8 dutyCycle
    )
  {
    switch (direction) {
      case MotorControl::MOVE_DIRECTION::FORWARD:
        this->gpioM1In1_out(0, Fw::Logic::HIGH);
        this->gpioM1In2_out(0, Fw::Logic::LOW);
        this->gpioM2In1_out(0, Fw::Logic::HIGH);
        this->gpioM2In2_out(0, Fw::Logic::LOW);
        break;
      case MotorControl::MOVE_DIRECTION::BACKWARD:
        this->gpioM1In1_out(0, Fw::Logic::LOW);
        this->gpioM1In2_out(0, Fw::Logic::HIGH);
        this->gpioM2In1_out(0, Fw::Logic::LOW);
        this->gpioM2In2_out(0, Fw::Logic::HIGH);
        break;
      case MotorControl::MOVE_DIRECTION::STOP:
        this->gpioM1In1_out(0, Fw::Logic::LOW);
        this->gpioM1In2_out(0, Fw::Logic::LOW);
        this->gpioM2In1_out(0, Fw::Logic::LOW);
        this->gpioM2In2_out(0, Fw::Logic::LOW);
        break;
    }

    this->pwmM1_out(0, (direction == MotorControl::MOVE_DIRECTION::STOP) ? 0 : dutyCycle);
    this->pwmM2_out(0, (direction == MotorControl::MOVE_DIRECTION::STOP) ? 0 : dutyCycle);

    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Components
