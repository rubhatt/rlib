#ifndef INCLUDED_RLIB_IPCLOCKDATA
#define INCLUDED_RLIB_IPCLOCKDATA

namespace rlib {

struct IPCLockData {
  bool d_is_locked;        // whether there is a lock held.
  int d_pid;               // pid of process currently holding lock
  long long d_access_time; // milliseconds since epoch
};

} // close namespace rlib

#endif
