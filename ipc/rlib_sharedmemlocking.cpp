#include <rlib_sharedmemlocking.h>

#include <boost/interprocess/sync/scoped_lock.hpp>

namespace rlib {

using namespace boost::interprocess;

SharedMemLocking::SharedMemLocking(const std::string &shared_mem_name,
                                   const int size)
    : d_shared_mem(open_or_create, shared_mem_name.c_str(), size) {

	auto x = 10;
  auto valloc = void_allocator{d_shared_mem.get_segment_manager()};

  // TODO - should these be named? 
  d_locks = d_shared_mem.get_segment_manager()->find_or_construct<lock_store_t>(
      "LockStorage")(std::less<String>(), valloc);

  d_locks_mutex =
      d_shared_mem.get_segment_manager()->find_or_construct<lock_type>(
          "LocksMutex")();
}

bool SharedMemLocking::lock(const std::string &lock_name) {
    auto valloc = void_allocator{d_shared_mem.get_segment_manager()};
    scoped_lock<lock_type> guard(*d_locks_mutex); // protect lock storage.

    auto key = key_type{
        lock_name.c_str(), valloc /* can be converted to any other alloc type */
    };

    auto iter = d_locks->find(key);
    if (d_locks->end() == iter) {
	// lock was not found, must be created.
    } else {
    }
}

} // close namespace rlib
