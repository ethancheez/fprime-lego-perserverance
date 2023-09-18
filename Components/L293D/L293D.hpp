// ======================================================================
// \title  L293D.hpp
// \author ethan
// \brief  hpp file for L293D component implementation class
// ======================================================================

#ifndef L293D_HPP
#define L293D_HPP

#include "Components/L293D/L293DComponentAc.hpp"

namespace Components {

  class L293D :
    public L293DComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object L293D
      //!
      L293D(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object L293D
      //!
      ~L293D();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for Drive command handler
      //! 
      void Drive_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          MotorControl::MOVE_DIRECTION direction, 
          U8 dutyCycle
      );


    };

} // end namespace Components

#endif
