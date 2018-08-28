#pragma once
#include <jni.h>
#include <stdint.h>
#include <assert.h>

inline jlong jlongFromPointer(void* ptr) {
  // Going through intptr_t to be obvious about the definedness of the
  // conversion from pointer to integral type.  intptr_t to jlong is a standard
  // widening by the static_assert above.
  jlong ret = reinterpret_cast<intptr_t>(ptr);
  assert(reinterpret_cast<void*>(ret) == ptr);
  return ret;
}