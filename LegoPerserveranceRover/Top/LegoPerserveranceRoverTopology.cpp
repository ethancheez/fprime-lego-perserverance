// ======================================================================
// \title  LegoPerserveranceRoverTopology.cpp
// \brief cpp file containing the topology instantiation code
//
// ======================================================================
// Provides access to autocoded functions
#include <LegoPerserveranceRover/Top/LegoPerserveranceRoverTopologyAc.hpp>
#include <LegoPerserveranceRover/Top/LegoPerserveranceRoverPacketsAc.hpp>
#include <config/FppConstantsAc.hpp>

// Necessary project-specified types
#include <Fw/Types/MallocAllocator.hpp>
#include <Svc/FramingProtocol/FprimeProtocol.hpp>
#include <Os/Log.hpp>
#include <FprimeArduino.hpp>

// Allows easy reference to objects in FPP/autocoder required namespaces
using namespace LegoPerserveranceRover;

// The reference topology uses a malloc-based allocator for components that need to allocate memory during the
// initialization phase.
Fw::MallocAllocator mallocator;

// The reference topology uses the F´ packet protocol when communicating with the ground and therefore uses the F´
// framing and deframing implementations.
Svc::FprimeFraming framing;
Svc::FprimeDeframing deframing;

// The reference topology divides the incoming clock signal (1Hz) into sub-signals: 1/100Hz, 1/200Hz, and 1/1000Hz
NATIVE_INT_TYPE rateGroupDivisors[Svc::RateGroupDriver::DIVIDER_SIZE] = {100, 200, 1000};

// Rate groups may supply a context token to each of the attached children whose purpose is set by the project. The
// reference topology sets each token to zero as these contexts are unused in this project.
NATIVE_INT_TYPE rateGroup1Context[FppConstant_PassiveRateGroupOutputPorts::PassiveRateGroupOutputPorts] = {};

/**
 * \brief configure/setup components in project-specific way
 *
 * This is a *helper* function which configures/sets up each component requiring project specific input. This includes
 * allocating resources, passing-in arguments, etc. This function may be inlined into the topology setup function if
 * desired, but is extracted here for clarity.
 */
void configureTopology() {
    // Rate group driver needs a divisor list
    rateGroupDriver.configure(rateGroupDivisors, FW_NUM_ARRAY_ELEMENTS(rateGroupDivisors));

    // Rate groups require context arrays.
    rateGroup1.configure(rateGroup1Context, FW_NUM_ARRAY_ELEMENTS(rateGroup1Context));

    // Framer and Deframer components need to be passed a protocol handler
    framer.setup(framing);
    deframer.setup(deframing);

    ledPin.open(Arduino::DEF_LED_BUILTIN, Arduino::GpioDriver::GpioDirection::OUT);
    pwmM1.open(15);
    gpioM1In1.open(12, Arduino::GpioDriver::GpioDirection::OUT);
    gpioM1In2.open(13, Arduino::GpioDriver::GpioDirection::OUT);
    pwmM2.open(16);
    gpioM2In1.open(19, Arduino::GpioDriver::GpioDirection::OUT);
    gpioM2In2.open(18, Arduino::GpioDriver::GpioDirection::OUT);
}

// Public functions for use in main program are namespaced with deployment name LegoPerserveranceRover
namespace LegoPerserveranceRover {
void setupTopology(const TopologyState& state) {
    // Autocoded initialization. Function provided by autocoder.
    initComponents(state);
    // Autocoded id setup. Function provided by autocoder.
    setBaseIds();
    // Autocoded connection wiring. Function provided by autocoder.
    connectComponents();
    // Autocoded command registration. Function provided by autocoder.
    regCommands();
    // Project-specific component configuration. Function provided above. May be inlined, if desired.
    configureTopology();
    // Autocoded parameter loading. Function provided by autocoder.
    // loadParameters();
    // Autocoded task kick-off (active components). Function provided by autocoder.
    startTasks(state);

    // if (commDriver.setupWiFi("ssid", "password") != Drv::SocketIpStatus::SOCK_SUCCESS) {
    //     Fw::Logger::logMsg("Failed to connect to WiFi\n");
    // }
    // if (commDriver.configure("192.168.1.1", 50000) != Drv::SocketIpStatus::SOCK_SUCCESS) {
    //     Fw::Logger::logMsg("Failed to connect to Client\n");
    // }

    commDriver.configure(&Serial);
    
    rateDriver.configure(1);
    rateDriver.start();
}

void teardownTopology(const TopologyState& state) {
    // Autocoded (active component) task clean-up. Functions provided by topology autocoder.
    stopTasks(state);
    freeThreads(state);
}
};  // namespace LegoPerserveranceRover
