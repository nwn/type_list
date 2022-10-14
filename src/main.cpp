#include <iostream>

#include "type_list.hpp"

int main() {
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
}
