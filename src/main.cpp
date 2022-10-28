#include <iostream>

#include "type_list.hpp"

int main() {
    static_assert(std::is_same_v<tl::first_t<tl::type_list<char>>, char>, "Oh no!");
    static_assert(std::is_same_v<tl::first_t<tl::type_list<bool, char>>, bool>, "Oh no!");
    static_assert(std::is_same_v<tl::first_t<tl::type_list<void, bool, char>>, void>, "Oh no!");

    static_assert(std::is_same_v<tl::last_t<tl::type_list<char>>, char>, "Oh no!");
    static_assert(std::is_same_v<tl::last_t<tl::type_list<char, bool>>, bool>, "Oh no!");
    static_assert(std::is_same_v<tl::last_t<tl::type_list<char, bool, void>>, void>, "Oh no!");

    // Should fail:
    // static_assert(std::is_same_v<tl::first_t<tl::type_list<>>, void>, "Oh no!");
    // static_assert(std::is_same_v<tl::last_t<tl::type_list<>>, void>, "Oh no!");


    using list_t = tl::type_list<char, bool, void>;

    static_assert(std::is_same_v<char, typename tl::at<0, list_t>::type>, "Oh no!");
    static_assert(std::is_same_v<char, tl::at_t<0, list_t>>, "Oh no!");

    static_assert(std::is_same_v<bool, typename tl::at<1, list_t>::type>, "Oh no!");
    static_assert(std::is_same_v<bool, tl::at_t<1, list_t>>, "Oh no!");

    static_assert(std::is_same_v<void, typename tl::at<2, list_t>::type>, "Oh no!");
    static_assert(std::is_same_v<void, tl::at_t<2, list_t>>, "Oh no!");

    // Should fail:
    // tl::at<3, list_t>::type X;
    // tl::at_t<3, list_t> Y;
    // tl::_details::linear::at_impl<0>::type Z;


    using empty_list_t = tl::type_list<>;
    static_assert(std::is_same_v<empty_list_t, tl::concat_t<>>, "Oh no!");
    static_assert(std::is_same_v<empty_list_t, tl::concat_t<empty_list_t>>, "Oh no!");
    static_assert(std::is_same_v<empty_list_t, tl::concat_t<empty_list_t, empty_list_t>>, "Oh no!");
    static_assert(std::is_same_v<empty_list_t, tl::concat_t<empty_list_t, empty_list_t, empty_list_t>>, "Oh no!");
    static_assert(std::is_same_v<list_t, tl::concat_t<list_t>>, "Oh no!");
    static_assert(std::is_same_v<tl::type_list<char, bool, void, char, bool, void>, tl::concat_t<list_t, list_t>>, "Oh no!");
    static_assert(std::is_same_v<tl::type_list<char, bool, void, char, bool, void>, tl::concat_t<list_t, empty_list_t, list_t>>, "Oh no!");
    static_assert(std::is_same_v<tl::type_list<char, bool, void, char, bool, void, char, bool, void>, tl::concat_t<list_t, list_t, list_t>>, "Oh no!");

    // Should fail:
    // tl::concat_t<int> X;
    // tl::concat_t<int, list_t> Y;

    using void256 = tl::type_list<
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void,
        void, void, void, void, void, void, void, void, void, void, void, void, void, void, void, void
    >;
    using void4096 = tl::concat_t<
        void256, void256, void256, void256, void256, void256, void256, void256,
        void256, void256, void256, void256, void256, void256, void256, void256
    >;
    static_assert(std::is_same_v<void, tl::at_t<void4096::size - 1, void4096>>, "Oh no!");
    static_assert(std::is_same_v<void, tl::last_t<void4096>>, "Oh no!");

    // This starts to get slow (~5s):
    // using void65536 = tl::concat_t<
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256,
    //     void256, void256, void256, void256, void256, void256, void256, void256
    // >;
    // static_assert(std::is_same_v<void, tl::at_t<void65536::size - 1, void65536>>, "Oh no!");
    // static_assert(std::is_same_v<void, tl::last_t<void65536>>, "Oh no!");


    static_assert(std::is_same_v<list_t, tl::map_t<list_t, std::type_identity>>, "Oh no!");

    using list_ints = tl::type_list<int8_t, int16_t, int32_t, int64_t>;
    using list_uints = tl::type_list<uint8_t, uint16_t, uint32_t, uint64_t>;
    using list_chars = tl::type_list<char8_t, char16_t, char32_t>;
    using list_null = tl::type_list<nullptr_t>;

    static_assert(std::is_same_v<list_ints, tl::map_t<list_uints, std::make_signed>>, "Oh no!");

    using list_meta = tl::type_list<list_uints, list_chars, list_null>;

    using firsts = tl::map_t<list_meta, tl::first>;
    static_assert(std::is_same_v<firsts, tl::type_list<uint8_t, char8_t, nullptr_t>>, "Oh no!");

    using lasts = tl::map_t<list_meta, tl::last>;
    static_assert(std::is_same_v<lasts, tl::type_list<uint64_t, char32_t, nullptr_t>>, "Oh no!");


    using list_mixed = tl::type_list<int8_t, float, void, double, char*, void, const std::string, nullptr_t>;
    using list_integral = tl::type_list<int8_t>;
    using list_float = tl::type_list<float, double>;
    using list_void = tl::type_list<void, void>;
    using list_pointer = tl::type_list<char*>;
    using list_const = tl::type_list<const std::string>;
    using list_nullptr = tl::type_list<nullptr_t>;

    static_assert(std::is_same_v<list_integral, tl::filter_t<list_mixed, std::is_integral>>, "Oh no!");
    static_assert(std::is_same_v<list_float, tl::filter_t<list_mixed, std::is_floating_point>>, "Oh no!");
    static_assert(std::is_same_v<list_void, tl::filter_t<list_mixed, std::is_void>>, "Oh no!");
    static_assert(std::is_same_v<list_pointer, tl::filter_t<list_mixed, std::is_pointer>>, "Oh no!");
    static_assert(std::is_same_v<list_const, tl::filter_t<list_mixed, std::is_const>>, "Oh no!");
    static_assert(std::is_same_v<list_nullptr, tl::filter_t<list_mixed, std::is_null_pointer>>, "Oh no!");

    static_assert(std::is_same_v<list_mixed, tl::filter_t<list_mixed, tl::always_true>>, "Oh no!");
    static_assert(std::is_same_v<empty_list_t, tl::filter_t<list_mixed, tl::always_false>>, "Oh no!");


    static_assert(tl::contains_v<char, list_t>, "Oh no!");
    static_assert(tl::contains_v<bool, list_t>, "Oh no!");
    static_assert(tl::contains_v<void, list_t>, "Oh no!");
    static_assert(!tl::contains_v<int, list_t>, "Oh no!");

    static_assert(list_t::contains<char>, "Oh no!");
    static_assert(list_t::contains<bool>, "Oh no!");
    static_assert(list_t::contains<void>, "Oh no!");
    static_assert(!list_t::contains<int>, "Oh no!");


    static_assert(list_ints::all_of<std::is_integral>, "Oh no!");
    static_assert(!list_t::all_of<std::is_integral>, "Oh no!");
    static_assert(empty_list_t::all_of<std::is_union>, "Oh no!");
    static_assert(empty_list_t::all_of<tl::always_false>, "Oh no!");

    static_assert(list_t::any_of<std::is_integral>, "Oh no!");
    static_assert(!list_t::any_of<std::is_floating_point>, "Oh no!");
    static_assert(!empty_list_t::any_of<std::is_union>, "Oh no!");
    static_assert(!empty_list_t::any_of<tl::always_true>, "Oh no!");

    static_assert(!list_t::none_of<std::is_integral>, "Oh no!");
    static_assert(list_t::none_of<std::is_floating_point>, "Oh no!");
    static_assert(empty_list_t::none_of<std::is_union>, "Oh no!");
    static_assert(empty_list_t::none_of<tl::always_true>, "Oh no!");
}
