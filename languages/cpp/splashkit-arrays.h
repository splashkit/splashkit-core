#ifndef splashkit_arrays_h
#define splashkit_arrays_h

// Ensure that splashkit headers in included, if not included
// use terminal as an indicator that the other library is already
// included.
#if !(defined(__terminal_h) || defined(terminal_h))
#include "splashkit.h"
#endif

#include <cstdlib>
#include <new>
#include <string>
#include <utility>
#include <vector>

/**
 * Exception thrown when attempting to add an element to a
 * bounded_array that has already reached its maximum capacity.
 */
struct array_full {};

/**
 * Exception thrown when attempting to access or remove
 * an element using an invalid index.
 */
struct array_invalid_index {};

/**
 * Exception thrown when a memory allocation fails.
 */
struct array_allocation_failed {};


/**
 * A fixed-capacity array container.
 *
 * bounded_array stores up to MAX_CAPACITY elements of type T.
 * Elements are stored contiguously and accessed by index.
 *
 * This container does not dynamically resize. Attempting to add
 * more than MAX_CAPACITY elements will result in an array_full
 * exception being thrown.
 *
 * Bounds checking is performed for element access and removal.
 * Invalid index access results in an array_invalid_index exception.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum number of elements the array can hold
 */
template<typename T, int MAX_CAPACITY>
class bounded_array
{
    int size;
    T data[MAX_CAPACITY];

    template<typename U>
    void add_impl(U&& value)
    {
        if (size >= MAX_CAPACITY)
        {
            write_line("Tried to add a new element when size has already reached maximum capacity (" + to_string(MAX_CAPACITY) + ")");
            throw array_full();
        }
        data[size++] = std::forward<U>(value);
    }

    void check_index(int index, const std::string& access_type) const
    {
        if (index < 0 || index >= size)
        {
            if (size == 0)
            {
                write_line("Cannot access index " + to_string(index) +
    " because array is empty.");
            }
            else
            {
                write_line("Index to " + access_type + " (" + to_string(index) + ") is outside of range 0 - " + to_string(size - 1) + ".");
            }
            throw array_invalid_index();
        }
    }

    public:
    /**
     * Constructs an empty bounded_array.
     *
     * The initial length of the array is 0.
     */
    bounded_array()
    {
         size = 0;
    }

    /**
     * Returns the maximum number of elements this array can store.
     *
     * @return The maximum capacity of the array
     */
    int capacity() const
    {
        return MAX_CAPACITY;
    }

    /**
     * Returns the current number of elements stored in the array.
     *
     * @return The number of valid elements in the array
     */
    int length() const
    {
        return size;
    }

    /**
     * Returns a reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A reference to the element at the given index
     *
     * @throws array_invalid_index if index is outside the range
     *         0 to length() - 1
     */
    T& get(int index)
    {
        check_index(index, "access");
        return data[index];
    }

    /**
     * Returns a const reference to the element at the specified index.
     *
     * This overload allows access on const bounded_array objects.
     *
     * @param index  The index of the element to access
     *
     * @return A const reference to the element at the given index
     *
     * @throws array_invalid_index if index is outside the range
     *         0 to length() - 1
     */
    const T& get(int index) const
    {
        check_index(index, "access");
        return data[index];
    }

    /**
     * Returns a reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A reference to the element at the given index
     *
     * @throws array_invalid_index if index is invalid
     */
    T& operator[](int index)
    {
        return get(index);
    }

    /**
     * Returns a const reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A const reference to the element at the given index
     *
     * @throws array_invalid_index if index is invalid
     */
    const T& operator[](int index) const
    {
        return get(index);
    }

    /**
     * Adds a new element to the end of the array.
     *
     * The element is copied into the next available position.
     *
     * @param value  The value to add to the array
     *
     * @throws array_full if the array has already reached MAX_CAPACITY
     */
    void add(const T& value)
    {
        add_impl(value);
    }

    void add(T&& value)
    {
        add_impl(std::move(value));
    }

    /**
     * Removes the element at the specified index.
     *
     * All elements after the removed element are shifted
     * one position to the left.
     *
     * @param index  The index of the element to remove
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void remove(int index)
    {
        check_index(index, "remove");

        for(int i = index; i < size - 1; i ++)
        {
            data[i] = data[i + 1];
        }

        size--;
    }
};

/**
 * Returns the maximum number of elements that the given
 * bounded_array can store.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 *
 * @param array  The bounded_array to query
 *
 * @return The maximum capacity of the array
 */
template<typename T, int MAX_CAPACITY>
int capacity(const bounded_array<T, MAX_CAPACITY>& array)
{
    return array.capacity();
}

/**
 * Returns the current number of elements stored in the given
 * bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 *
 * @param array  The bounded_array to query
 *
 * @return The number of elements currently stored in the array
 */
template<typename T, int MAX_CAPACITY>
int length(const bounded_array<T, MAX_CAPACITY>& array)
{
    return array.length();
}

/**
 * Returns a reference to the element at the specified index
 * within the given bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 *
 * @param array  The bounded_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T, int MAX_CAPACITY>
T& get(bounded_array<T, MAX_CAPACITY>& array, int index)
{
    return array.get(index);
}

/**
 * Returns a const reference to the element at the specified index
 * within the given bounded_array.
 *
 * This overload allows access to elements of a const bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 *
 * @param array  The bounded_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A const reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */

template<typename T, int MAX_CAPACITY>
const T& get(const bounded_array<T, MAX_CAPACITY>& array, int index)
{
    return array.get(index);
}

/**
 * Adds a new element to the end of the given bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 * @tparam U             The type of element being added
 *
 * @param array  The bounded_array to modify
 * @param value  The value to add to the array
 *
 * @throws array_full if the array has reached its maximum capacity
 */
template<typename T, int MAX_CAPACITY, typename U>
void add(bounded_array<T, MAX_CAPACITY>& array, U&& value)
{
    array.add(std::forward<U>(value));
}

/**
 * Removes the element at the specified index from the given
 * bounded_array.
 *
 * All elements following the removed element are shifted one
 * position to the left.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_CAPACITY  The maximum capacity of the array
 *
 * @param array  The bounded_array to modify
 * @param index  The index of the element to remove
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T, int MAX_CAPACITY>
void remove(bounded_array<T, MAX_CAPACITY>& array, int index)
{
    array.remove(index);
}




/**
 * A dynamically resizing array container.
 *
 * dynamic_array stores elements in contiguous memory and automatically
 * resizes as needed.
 *
 * It supports copying, assignment, passing by value, returning from functions,
 * and passing by reference.
 *
 * Bounds checking is performed for element access and removal.
 * Invalid index access results in an array_invalid_index exception.
 * Memory allocation failures throw array_allocation_failed.
 *
 * @tparam T  The type of elements stored in the array
 */
template<typename T>
class dynamic_array
{
    std::vector<T> data;

    void check_index(int index, const std::string& access_type) const
    {
        if (index < 0 || index >= static_cast<int>(data.size()))
        {
            if (data.empty())
            {
                write_line("Cannot access index " + to_string(index) +
    " because array is empty.");
            }
            else
            {
                write_line("Index to " + access_type + " (" + to_string(index) + ") is outside of range 0 - " + to_string(static_cast<int>(data.size()) - 1) + ".");
            }
            throw array_invalid_index();
        }
    }

    public:

    /**
     * Constructs an empty dynamic_array.
     */
    dynamic_array() = default;

    /**
     * Destructor.
     *
     * Destroys all valid elements and frees allocated memory.
     */
    ~dynamic_array() = default;

    /**
     * Returns the current capacity of the array.
     *
     * @return The number of elements that can be stored
     *         without resizing.
     */
    int capacity() const
    {
        return static_cast<int>(data.capacity());
    }

    /**
     * Returns the current number of elements stored in the array.
     *
     * @return The number of valid elements in the array
     */
    int length() const
    {
        return static_cast<int>(data.size());
    }

    /**
     * Returns a reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A reference to the element at the given index
     *
     * @throws array_invalid_index if index is outside the range
     *         0 to length() - 1
     */
    T& get(int index)
    {
        check_index(index, "access");
        return data[static_cast<size_t>(index)];
    }

    /**
     * Returns a const reference to the element at the specified index.
     *
     * This overload allows access on const bounded_array objects.
     *
     * @param index  The index of the element to access
     *
     * @return A const reference to the element at the given index
     *
     * @throws array_invalid_index if index is outside the range
     *         0 to length() - 1
     */
    const T& get(int index) const
    {
        check_index(index, "access");
        return data[static_cast<size_t>(index)];
    }

    /**
     * Returns a reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A reference to the element at the given index
     *
     * @throws array_invalid_index if index is invalid
     */
    T& operator[](int index)
    {
        return get(index);
    }

    /**
     * Returns a const reference to the element at the specified index.
     *
     * @param index  The index of the element to access
     *
     * @return A const reference to the element at the given index
     *
     * @throws array_invalid_index if index is invalid
     */
    const T& operator[](int index) const
    {
        return get(index);
    }

    /**
     * Adds a new element to the end of the array.
     *
     * The element is copied into the next available position.
     *
     * @param value  The value to add to the array
     *
     * @throws array_allocation_failed if memory allocation fails.
     */
    void add(const T& value)
    {
        try
        {
            data.push_back(value);
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }

    void add(T&& value)
    {
        try
        {
            data.push_back(std::move(value));
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }

    /**
     * Removes the element at the specified index.
     *
     * All elements after the removed element are shifted one position
     * to the left, which changes their indices.
     *
     * @param index  The index of the element to remove
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void remove(int index)
    {
        check_index(index, "remove");
        data.erase(data.begin() + index);
    }
};

/**
 * Returns the current capacity that the given
 * dynamic_array can store without resizing.
 *
 * @tparam T             The type of elements stored in the array
 *
 * @param array  The dynamic_array to query
 *
 * @return The number of elements that can be stored
 *         without resizing.
 */
template<typename T>
int capacity(const dynamic_array<T>& array)
{
    return array.capacity();
}

/**
 * Returns the current number of elements stored in the given
 * dynamic_array.
 *
 * @tparam T             The type of elements stored in the array
 *
 * @param array  The dynamic_array to query
 *
 * @return The number of elements currently stored in the array
 */
template<typename T>
int length(const dynamic_array<T>& array)
{
    return array.length();
}

/**
 * Returns a reference to the element at the specified index
 * within the given dynamic_array.
 *
 * @tparam T             The type of elements stored in the array
 *
 * @param array  The dynamic_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T>
T& get(dynamic_array<T>& array, int index)
{
    return array.get(index);
}

/**
 * Returns a const reference to the element at the specified index
 * within the given dynamic_array.
 *
 * This overload allows access to elements of a const dynamic_array.
 *
 * @tparam T             The type of elements stored in the array
 *
 * @param array  The dynamic_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A const reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */

template<typename T>
const T& get(const dynamic_array<T>& array, int index)
{
    return array.get(index);
}

/**
 * Adds a new element to the end of the given dynamic_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam U             The type of element being added
 *
 * @param array  The dynamic_array to modify
 * @param value  The value to add to the array
 *
 * @throws array_allocation_failed if memory allocation fails.
 */
template<typename T, typename U>
void add(dynamic_array<T>& array, U&& value)
{
    array.add(std::forward<U>(value));
}

/**
 * Removes the element at the specified index from the given
 * dynamic_array.
 *
 * All elements following the removed element are shifted one
 * position to the left.
 *
 * @tparam T             The type of elements stored in the array
 *
 * @param array  The dynamic_array to modify
 * @param index  The index of the element to remove
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T>
void remove(dynamic_array<T>& array, int index)
{
    array.remove(index);
}

#endif
