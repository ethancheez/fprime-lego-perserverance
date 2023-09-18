// ======================================================================
// \title  LegoPerserveranceRoverTopologyDefs.hpp
// \brief required header file containing the required definitions for the topology autocoder
//
// ======================================================================
#ifndef LEGOPERSERVERANCEROVER_LEGOPERSERVERANCEROVERTOPOLOGYDEFS_HPP
#define LEGOPERSERVERANCEROVER_LEGOPERSERVERANCEROVERTOPOLOGYDEFS_HPP

#include "Fw/Types/MallocAllocator.hpp"
#include "LegoPerserveranceRover/Top/FppConstantsAc.hpp"
#include "Svc/FramingProtocol/FprimeProtocol.hpp"

// Definitions are placed within a namespace named after the deployment
namespace LegoPerserveranceRover {

/**
 * \brief required type definition to carry state
 *
 * The topology autocoder requires an object that carries state with the name `LegoPerserveranceRover::TopologyState`. Only the type
 * definition is required by the autocoder and the contents of this object are otherwise opaque to the autocoder. The
 * contents are entirely up to the definition of the project. This reference application specifies hostname and port
 * fields, which are derived by command line inputs.
 */
struct TopologyState {
    FwIndexType uartNumber;
    PlatformIntType uartBaud;
};

/**
 * \brief required ping constants
 *
 * The topology autocoder requires a WARN and FATAL constant definition for each component that supports the health-ping
 * interface. These are expressed as enum constants placed in a namespace named for the component instance. These
 * are all placed in the PingEntries namespace.
 *
 * Each constant specifies how many missed pings are allowed before a WARNING_HI/FATAL event is triggered. In the
 * following example, the health component will emit a WARNING_HI event if the component instance cmdDisp does not
 * respond for 3 pings and will FATAL if responses are not received after a total of 5 pings.
 *
 * ```c++
 * namespace PingEntries {
 * namespace cmdDisp {
 *     enum { WARN = 3, FATAL = 5 };
 * }
 * }
 * ```
 */
namespace PingEntries {
namespace tlmSend {
enum { WARN = 3, FATAL = 5 };
}
namespace cmdDisp {
enum { WARN = 3, FATAL = 5 };
}
namespace eventLogger {
enum { WARN = 3, FATAL = 5 };
}
namespace rateGroup1 {
enum { WARN = 3, FATAL = 5 };
}
}  // namespace PingEntries
}  // namespace LegoPerserveranceRover
#endif
