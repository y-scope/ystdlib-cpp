#ifndef YSTDLIB_CONTAINERS_ARRAY_HPP
#define YSTDLIB_CONTAINERS_ARRAY_HPP

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace ystdlib::containers {
/**
 * Class for a runtime fix-sized array.
 * @tparam T The type of elements in the array. The type must be default initializable so that this
 * class doesn't need to implement special memory allocation procedure for std::unique_ptr<T[]>.
 * Note that when using constructor that takes an initializer list, T must be copy constructable.
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
            std::fill_n(m_data.get(), m_size, T{});
        }
    }

    Array(std::initializer_list<T> list)
            // NOLINTNEXTLINE(*-avoid-c-arrays)
            : m_data{std::make_unique<T[]>(list.size())},
              m_size{list.size()} {
        std::ranges::copy(list, m_data.get());
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
     * @throw `std::out_of_range` if the given index is out of bound.
     */
    [[nodiscard]] auto at(size_t idx) -> T& {
        assert_is_in_range(idx);
        return m_data[idx];
    }

    /**
     * @param idx
     * @return The element at the given index.
     * @throw `std::out_of_range` if the given index is out of bound.
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
    auto assert_is_in_range(size_t idx) const -> void {
        if (idx >= m_size) {
            // TODO: Add ErrorCode class for `stdexcept` errors and switch to use TraceableException
            throw std::out_of_range("ystdlib::containers::Array out-of-range access.");
        }
    }

    // Variables
    // NOLINTNEXTLINE(*-avoid-c-arrays)
    std::unique_ptr<T[]> m_data;
    size_t m_size;
};
}  // namespace ystdlib::containers

#endif  // YSTDLIB_CONTAINERS_ARRAY_HPP
