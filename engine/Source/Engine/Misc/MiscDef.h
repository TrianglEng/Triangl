#pragma once

#define TL_CONCAT_DETAIL(l, r) l##r
#define TL_CONCAT(l, r)        TL_CONCAT_DETAIL(l, r)

#define TL_STRINGIFY_DETAIL(x) #x
#define TL_STRINGIFY(x)        TL_STRINGIFY_DETAIL(x)

#define TL_BIT(x) (1 << x)

#define TL_BIND_METHOD(pObject, method) [pObject](auto&&... args) -> decltype(auto) { return pObject->method(std::forward<decltype(args)>(args)...); }
