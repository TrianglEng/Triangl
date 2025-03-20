#ifndef TRIANGL_MISC_MISCDEF_HH
#define TRIANGL_MISC_MISCDEF_HH 1

#define TL_CONCAT_DETAIL(l, r) l##r
#define TL_CONCAT(l, r)        TL_CONCAT_DETAIL(l, r)

#define TL_STRINGIFY_DETAIL(x) #x
#define TL_STRINGIFY(x)        TL_STRINGIFY_DETAIL(x)

#define TL_BIT(x) (1 << x)

#define TL_BIND_METHOD(p, fn) [p](auto&&... args) -> decltype(auto) { return p->fn(std::forward<decltype(args)>(args)...); }

#endif
