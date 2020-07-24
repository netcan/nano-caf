//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_EXIT_REASON_H
#define NANO_CAF_EXIT_REASON_H

#include <nano-caf/nano-caf-ns.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

enum class exit_reason : uint8_t {
   /// Indicates that an actor finished execution without error.
   normal = 0,
   /// Indicates that an actor died because of an unhandled exception.
   unhandled_exception,
   /// Indicates that the exit reason for this actor is unknown, i.e.,
   /// the actor has been terminated and no longer exists.
   unknown,
   /// Indicates that an actor pool unexpectedly ran out of workers.
   out_of_workers,
   /// Indicates that an actor was forced to shutdown by a user-generated event.
   user_shutdown,
   /// Indicates that an actor was killed unconditionally.
   kill,
   /// Indicates that an actor finished execution because a connection
   /// to a remote link was closed unexpectedly.
   remote_link_unreachable,
   /// Indicates that an actor was killed because it became unreachable.
   unreachable
};

NANO_CAF_NS_END

#endif //NANO_CAF_EXIT_REASON_H
