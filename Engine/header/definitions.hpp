//
// Created by luca on 19/08/22.
//

#include <memory>

#ifndef ENGINE_DEFINITIONS_HPP
#define ENGINE_DEFINITIONS_HPP

#if _MSC_VER
#define DEBUGBREAK __debugbreak()
#else
#define DEBUGBREAK __builtin_trap()
#endif
#define ASSERT(x) if (!(x)) DEBUGBREAK
#define GLCall(x) GLClearError(); \
   x;                             \
   ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

namespace GE {
   template<class T> using Ref = std::shared_ptr<T>;

   template<typename T, typename ... Args>
   constexpr Ref<T> makeRef(Args&& ... args)
   {
      return std::make_shared<T>(std::forward<Args>(args)...);
   }
}

#endif //SANDBOX_DEFINITIONS_HPP



