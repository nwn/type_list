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
}
