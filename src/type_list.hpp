#ifndef TYPE_LIST_HPP_
#define TYPE_LIST_HPP_

#include <cstddef>

namespace tl {

    template <typename... Ts>
    struct type_list {};

    namespace _details::linear {

        template <size_t I, typename... Ts>
        struct check_bounds {
            static_assert(I < sizeof...(Ts), "type_list index out of bounds");
        };

        template <size_t I, typename... Ts>
        struct at_impl: check_bounds<I, Ts...> { };

        template <typename T, typename... Ts>
        struct at_impl<0, T, Ts...>: check_bounds<0, T, Ts...> {
            using type = T;
        };

        template <size_t I, typename T, typename... Ts>
        struct at_impl<I, T, Ts...>: check_bounds<I, T, Ts...> {
            using type = typename at_impl<I - 1, Ts...>::type;
        };

    }  // _details::linear

    template <size_t I, typename TypeList>
    struct at;

    template <size_t I, template <typename...> typename TypeList, typename... Ts>
    struct at<I, TypeList<Ts...>> {
        using type = typename _details::linear::at_impl<I, Ts...>::type;
    };

    template <size_t I, typename TypeList>
    using at_t = typename at<I, TypeList>::type;


    template <typename... TypeLists>
    struct concat;

    template <>
    struct concat<> {
        using type = type_list<>;
    };

    template <typename... Ts>
    struct concat<type_list<Ts...>> {
        using type = type_list<Ts...>;
    };

    template <typename... Ts, typename... Us, typename... TypeLists>
    struct concat<type_list<Ts...>, type_list<Us...>, TypeLists...> {
        using type = typename concat<type_list<Ts..., Us...>, TypeLists...>::type;
    };

    template <typename... TypeLists>
    using concat_t = typename concat<TypeLists...>::type;

}  // tl

#endif  // TYPE_LIST_HPP_
