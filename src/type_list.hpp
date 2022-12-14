#ifndef TYPE_LIST_HPP_
#define TYPE_LIST_HPP_

#include <cstddef>
#include <type_traits>
#include <utility>

namespace tl {

    template <typename... Ts>
    struct type_list;

    template <typename TypeList>
    struct first;

    template <typename T, typename... Ts>
    struct first<type_list<T, Ts...>> {
        using type = T;
    };

    template <typename TypeList>
    using first_t = typename first<TypeList>::type;

    template <typename TypeList>
    struct last;

    template <typename... Ts>
    struct last<type_list<Ts...>> {
        using type = typename decltype((std::type_identity<Ts>(), ...))::type;
    };

    template <typename TypeList>
    using last_t = typename last<TypeList>::type;

    namespace _details::at {

        namespace linear {

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

        }  // linear

        template <size_t I, typename... Ts>
        struct check_bounds {
            static_assert(I < sizeof...(Ts), "type_list index out of bounds");
        };

        // Leverage the multiple-inheritance technique from:
        // https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
        template <size_t I, typename T>
        struct indexed {
            using type = T;
        };

        template <typename Is, typename... Ts>
        struct indexer;

        template <size_t... Is, typename... Ts>
        struct indexer<std::index_sequence<Is...>, Ts...> : indexed<Is, Ts>...
        { };

        template <size_t I, typename T>
        static constexpr indexed<I, T> select(indexed<I, T>);

        template <size_t I, typename... Ts>
        struct at_impl: check_bounds<I, Ts...> {
            using type = typename decltype(select<I>(
                indexer<std::index_sequence_for<Ts...>, Ts...>{}
            ))::type;
        };

    }  // _details::at

    template <size_t I, typename TypeList>
    struct at;

    template <size_t I, template <typename...> typename TypeList, typename... Ts>
    struct at<I, TypeList<Ts...>> {
        using type = typename _details::at::at_impl<I, Ts...>::type;
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

    template <typename TypeList, template <typename> typename Adaptor>
    struct map;

    template <template <typename> typename Adaptor, typename... Ts>
    struct map<type_list<Ts...>, Adaptor> {
        using type = type_list<typename Adaptor<Ts>::type...>;
    };

    template <typename TypeList, template <typename> typename Adaptor>
    using map_t = typename map<TypeList, Adaptor>::type;

    template <typename>
    struct always_true: std::true_type {};

    template <typename>
    struct always_false: std::false_type {};

    namespace _details::filter {

        template <typename Done, typename Rest, template <typename> typename Predicate>
        struct filter_partial;

        template <template <typename> typename Predicate, typename Next, typename... Done, typename... Rest>
        struct filter_partial<type_list<Done...>, type_list<Next, Rest...>, Predicate> {
            static constexpr bool include = Predicate<Next>::value;
            using type = std::conditional_t<include,
                typename filter_partial<type_list<Done..., Next>, type_list<Rest...>, Predicate>::type,
                typename filter_partial<type_list<Done...>, type_list<Rest...>, Predicate>::type>;
        };

        template <template <typename> typename Predicate, typename... Done>
        struct filter_partial<type_list<Done...>, type_list<>, Predicate> {
            using type = type_list<Done...>;
        };

    }  // namespace _details::filter

    template <typename TypeList, template <typename> typename Predicate>
    struct filter;

    template <template <typename> typename Predicate, typename... Ts>
    struct filter<type_list<Ts...>, Predicate> {
        using type = typename _details::filter::filter_partial<type_list<>, type_list<Ts...>, Predicate>::type;
    };

    template <typename TypeList, template <typename> typename Predicate>
    using filter_t = typename filter<TypeList, Predicate>::type;

    namespace _details::reverse {

        template <typename New, typename TypeList>
        struct append;

        template <typename New, typename... Ts>
        struct append<New, type_list<Ts...>> {
            using type = type_list<Ts..., New>;
        };

        template <typename... Ts>
        struct reverse_partial;

        template <>
        struct reverse_partial<> {
            using type = type_list<>;
        };

        template <typename First, typename... Rest>
        struct reverse_partial<First, Rest...> {
            using type = typename append<First, typename reverse_partial<Rest...>::type>::type;
        };

    }  // namespace _details::reverse

    template <typename TypeList>
    struct reverse;

    template <typename... Ts>
    struct reverse<type_list<Ts...>> {
        using type = typename _details::reverse::reverse_partial<Ts...>::type;
    };

    template <typename TypeList>
    using reverse_t = typename reverse<TypeList>::type;

    template <typename T, typename TypeList>
    struct contains;

    template <typename T>
    struct contains<T, type_list<>> : std::false_type {};

    template <typename T, typename... Ts>
    struct contains<T, type_list<T, Ts...>> : std::true_type {};

    template <typename T, typename Next, typename... Ts>
    struct contains<T, type_list<Next, Ts...>> : contains<T, type_list<Ts...>> {};

    template <typename T, typename TypeList>
    static constexpr bool contains_v = contains<T, TypeList>::value;

    template <template <typename> typename Pred, typename TypeList>
    struct all_of;

    template <template <typename> typename Pred, typename... Ts>
    struct all_of<Pred, type_list<Ts...>> : std::conjunction<Pred<Ts>...> {};

    template <template <typename> typename Pred, typename TypeList>
    static constexpr bool all_of_v = all_of<Pred, TypeList>::value;

    template <template <typename> typename Pred, typename TypeList>
    struct any_of;

    template <template <typename> typename Pred, typename... Ts>
    struct any_of<Pred, type_list<Ts...>> : std::disjunction<Pred<Ts>...> {};

    template <template <typename> typename Pred, typename TypeList>
    static constexpr bool any_of_v = any_of<Pred, TypeList>::value;

    template <template <typename> typename Pred, typename TypeList>
    struct none_of : std::negation<any_of<Pred, TypeList>> {};

    template <template <typename> typename Pred, typename TypeList>
    static constexpr bool none_of_v = none_of<Pred, TypeList>::value;

    template <typename... Ts>
    struct type_list {
        static constexpr size_t size = sizeof...(Ts);

        template <typename T>
        static constexpr bool contains = contains_v<T, type_list>;

        template <template <typename> typename Pred>
        static constexpr bool all_of = all_of_v<Pred, type_list>;

        template <template <typename> typename Pred>
        static constexpr bool any_of = any_of_v<Pred, type_list>;

        template <template <typename> typename Pred>
        static constexpr bool none_of = none_of_v<Pred, type_list>;

        template <typename TemplFunc>
        static void for_each(TemplFunc templ_func) {
            (void)((templ_func.template operator()<Ts>(), 0) + ...);
        }
    };
}  // tl

#endif  // TYPE_LIST_HPP_
