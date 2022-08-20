//
// Created by luca on 19/08/22.
//

#include <memory>

#ifndef SANDBOX_DEFINITIONS_HPP
#define SANDBOX_DEFINITIONS_HPP

#endif //SANDBOX_DEFINITIONS_HPP

namespace GM {
   template<class T> using Ref = std::shared_ptr<T>;

//   template<typename T, typename ... Args>
//   constexpr Ref<T> MakeRef(Args&& ... args)
//   {
//      return std::make_shared<T>(std::forward<Args>(args)...);
//   }
}

