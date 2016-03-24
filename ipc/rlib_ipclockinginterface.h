#ifndef INCLUDED_RLIB_IPCLOCKINGINTERFACE
#define INCLUDED_RLIB_IPCLOCKINGINTERFACE

#include <string>

namespace rlib {

class IPCLockingInterface {
public:
  IPCLockingInterface() {}

  virtual ~IPCLockingInterface() {}

  virtual bool lock(const std::string &lock_name) = 0;
  virtual bool unlock(const std::string &lock_name) = 0;
  virtual int numLocks() const = 0;
};

} // close namespace rlib

#endif
