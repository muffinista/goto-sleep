#include <mach/mach_port.h>
#include <IOKit/pwr_mgt/IOPM.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
extern "C" {
  int SACLockScreenImmediate ( void );
}

bool doSleep() {
  IOReturn                        err;
  io_connect_t                    fb;

  // https://opensource.apple.com/source/PowerManagement/PowerManagement-211.14/pmset/pmset.c.auto.html
  fb = IOPMFindPowerManagement(MACH_PORT_NULL);
  if ( MACH_PORT_NULL != fb ) {
    err = IOPMSleepSystem( fb );

    if (kIOReturnNotPrivileged == err) {
      // printf("Sleep error 0x%08x; You must run this as root.\n", err);
      return false;
    }
    else if ( (MACH_PORT_NULL == fb) || (kIOReturnSuccess != err) ) {
      // printf("Unable to sleep system: error 0x%08x\n", err);
      return false;
    } 
    return true;
  }  

  return false;
}

bool doLockScreen() {
  return SACLockScreenImmediate();
}