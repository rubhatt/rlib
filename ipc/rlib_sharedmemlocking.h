#include <rlib_ipclockinginterface.h>
#include <rlib_ipclockdata.h>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>

#include <utility>

namespace rlib {
class SharedMemLocking : public IPCLockingInterface {
public:
  SharedMemLocking(const std::string &shared_mem_name, const int size);

  virtual ~SharedMemLocking();

  virtual bool lock(const std::string &lock_name);
  virtual bool unlock(const std::string &lock_name);
  virtual int numLocks() const = 0;
private:

  typedef boost::interprocess::managed_shared_memory shared_mem_t;
  typedef shared_mem_t::segment_manager segment_manager_t;

  typedef boost::interprocess::allocator<void, segment_manager_t> void_allocator;
  
  // segment allocator for string
  typedef boost::interprocess::allocator<char, segment_manager_t> char_alloc;
  typedef boost::interprocess::basic_string<char, std::char_traits<char>,
                                            char_alloc> String;

  typedef boost::interprocess::interprocess_mutex lock_type;

  typedef String key_type;
  typedef IPCLockData value_type;
  typedef std::pair<const key_type, value_type> map_value;

  // allocator for values of the map
  typedef boost::interprocess::allocator<map_value, segment_manager_t>
      map_value_alloc;

  typedef boost::interprocess::map<key_type, value_type, std::less<key_type>,
                                   map_value_alloc> lock_store_t;

  // private member variables
  shared_mem_t d_shared_mem; // the managed shared mem object
  lock_store_t *d_locks;
  mutable lock_type *d_locks_mutex; // mutex to protect access to d_locks
};
} // close namespace rlib
