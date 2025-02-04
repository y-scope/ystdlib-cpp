#include <iostream>
#include <ystdlib/testlib/hello.hpp>
#ifndef YSTDLIB_CONTAINER_ARRAY_HPP
    #define YSTDLIB_CONTAINER_ARRAY_HPP

    #include <concepts>
    #include <cstddef>
    #include <cstring>
    #include <memory>
    #include <stdexcept>
    #include <type_traits>

namespace ystdlib::container {
/**
 * Class for a runtime fix-sized array.
 * @tparam T The type of elements in the array. The type must be default initializable so that this
 * class doesn't need to implement a constructor which takes an initializer list.
 */
template <typename T>
requires(std::is_fundamental_v<T> || std::default_initializable<T>)
class Array {
public:
    // Types
    using Iterator = T*;
    using ConstIterator = T const*;

    // Constructors
    // NOLINTNEXTLINE(*-avoid-c-arrays)
    explicit Array(size_t size) : m_data{std::make_unique<T[]>(size)}, m_size{size} {
        if constexpr (std::is_fundamental_v<T>) {
            memset(m_data.get(), 0, m_size * sizeof(T));
        }
    }

    // Disable copy constructor and assignment operator
    Array(Array const&) = delete;
    auto operator=(Array const&) -> Array& = delete;

    // Default move constructor and assignment operator
    Array(Array&&) = default;
    auto operator=(Array&&) -> Array& = default;

    // Destructor
    ~Array() = default;

    // Methods
    /**
     * @return Whether the array is empty.
     */
    [[nodiscard]] auto empty() const -> bool { return 0 == size(); }

    /**
     * @return The size of the array.
     */
    [[nodiscard]] auto size() const -> size_t { return m_size; }

    /**
     * @return A pointer to the underlying data buffer.
     */
    [[nodiscard]] auto data() -> T* { return m_data.get(); }

    /**
     * @return A pointer to the underlying data buffer.
     */
    [[nodiscard]] auto data() const -> T const* { return m_data.get(); }

    /**
     * @param idx
     * @return The element at the given index.
     * @throw `OperationFailed` if the given index is out of bound.
     */
    [[nodiscard]] auto at(size_t idx) -> T& {
        assert_is_in_range(idx);
        return m_data[idx];
    }

    /**
     * @param idx
     * @return The element at the given index.
     * @throw `OperationFailed` if the given index is out of bound.
     */
    [[nodiscard]] auto at(size_t idx) const -> T const& {
        assert_is_in_range(idx);
        return m_data[idx];
    }

    [[nodiscard]] auto begin() -> Iterator { return m_data.get(); }

    [[nodiscard]] auto end() -> Iterator { return m_data.get() + m_size; }

    [[nodiscard]] auto begin() const -> ConstIterator { return m_data.get(); }

    [[nodiscard]] auto end() const -> ConstIterator { return m_data.get() + m_size; }

private:
    /**
     * @param idx
     * @throw `std::out_of_range` if the given index is out of bound.
     */
    auto assert_is_in_range(size_t idx) -> void {
        if (idx >= m_size) {
            throw std::out_of_range("ystdlib::Array out-of-range access.");
        }
    }

    // Variables
    // NOLINTNEXTLINE(*-avoid-c-arrays)
    std::unique_ptr<T[]> m_data;
    size_t m_size;
};
}  // namespace ystdlib::container

#endif  // YSTDLIB_CONTAINER_ARRAY_HPP

[[nodiscard]] auto main() -> int {
    ystdlib::container::Array<int> const c_v{3};
    for (auto const i : c_v) {
        std::cout << i << '\n';
    }
    std::cout << ystdlib::testlib::hello() << '\n';
    constexpr auto c23{202'101L};
    constexpr auto c20{202'002L};
    constexpr auto c17{201'703L};
    constexpr auto c14{201'402L};
    constexpr auto c11{201'103L};
    constexpr auto c98{199'711L};
    if (__cplusplus == c23) {
        std::cout << "C++23";
    } else if (__cplusplus == c20) {
        std::cout << "C++20";
    } else if (__cplusplus == c17) {
        std::cout << "C++17";
    } else if (__cplusplus == c14) {
        std::cout << "C++14";
    } else if (__cplusplus == c11) {
        std::cout << "C++11";
    } else if (__cplusplus == c98) {
        std::cout << "C++98";
    } else {
        std::cout << "pre-standard C++." << __cplusplus;
    }
    std::cout << "\n";
    return 0;
}
