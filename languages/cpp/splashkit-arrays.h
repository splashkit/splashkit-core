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
 * Exception thrown when attempting to access or remove
 * an element using an invalid index.
 */
struct array_invalid_index {};

/**
 * Exception thrown when a memory allocation fails.
 */
struct array_allocation_failed {};

/**
 * Exception thrown when creating a fixed-size array with
 * a size outside the valid range.
 */
struct array_invalid_size {};


/**
 * A fixed-size array container.
 *
 * bounded_array stores exactly `size` elements of type T, where `size`
 * is set when the array is created.
 * Elements are stored contiguously and accessed by index.
 *
 * This container does not support add/remove operations.
 * Its length is fixed after construction.
 *
 * Bounds checking is performed for element access.
 * Invalid index access results in an array_invalid_index exception.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_SIZE      The maximum number of elements the array can hold
 */
template<typename T, int MAX_SIZE>
class bounded_array
{
    int _size;
    T data[MAX_SIZE];

    void check_index(int index, const std::string& access_type) const
    {
        if (index < 0 || index >= _size)
        {
            if (_size == 0)
            {
                write_line("Cannot access index " + to_string(index) +
    " because array is empty.");
            }
            else
            {
                write_line("Index to " + access_type + " (" + to_string(index) + ") is outside of range 0 - " + to_string(_size - 1) + ".");
            }
            throw array_invalid_index();
        }
    }

    public:
    /**
     * Constructs a fixed-size bounded_array.
     *
     * @param size  Number of elements in this array (0 to MAX_SIZE)
     *
     * @throws array_invalid_size when size is outside 0 to MAX_SIZE.
     */
    explicit bounded_array(int size = MAX_SIZE)
    {
         if (size < 0 || size > MAX_SIZE)
         {
             write_line("Invalid bounded_array size (" + to_string(size) + "). Valid range is 0 - " + to_string(MAX_SIZE) + ".");
             throw array_invalid_size();
         }
         _size = size;
    }

    /**
     * Returns the current number of elements stored in the array.
     *
     * @return The number of valid elements in the array
     */
    int length() const
    {
        return _size;
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
     * Sets the value at the specified index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void set(int index, const T& value)
    {
        check_index(index, "set");
        data[index] = value;
    }

    /**
     * Sets the value at the specified index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void set(int index, T&& value)
    {
        check_index(index, "set");
        data[index] = std::move(value);
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

};

/**
 * Returns the current number of elements stored in the given
 * bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The bounded_array to query
 *
 * @return The number of elements currently stored in the array
 */
template<typename T, int MAX_SIZE>
int length(const bounded_array<T, MAX_SIZE>& array)
{
    return array.length();
}

/**
 * Returns a reference to the element at the specified index
 * within the given bounded_array.
 *
 * @tparam T             The type of elements stored in the array
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The bounded_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T, int MAX_SIZE>
T& get(bounded_array<T, MAX_SIZE>& array, int index)
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
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The bounded_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A const reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the valid range
 */

template<typename T, int MAX_SIZE>
const T& get(const bounded_array<T, MAX_SIZE>& array, int index)
{
    return array.get(index);
}

/**
 * Sets the element at the specified index within the given
 * bounded_array.
 *
 * @tparam T         The type of elements stored in the array
 * @tparam MAX_SIZE  The maximum capacity of the array
 * @tparam U         The type of value being assigned
 *
 * @param array  The bounded_array to modify
 * @param index  The index of the element to update
 * @param value  The new value for that index
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T, int MAX_SIZE, typename U>
void set(bounded_array<T, MAX_SIZE>& array, int index, U&& value)
{
    array.set(index, std::forward<U>(value));
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
     * Sets the value at the specified index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void set(int index, const T& value)
    {
        check_index(index, "set");
        data[static_cast<size_t>(index)] = value;
    }

    /**
     * Sets the value at the specified index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the valid range
     */
    void set(int index, T&& value)
    {
        check_index(index, "set");
        data[static_cast<size_t>(index)] = std::move(value);
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
 * Sets the element at the specified index within the given
 * dynamic_array.
 *
 * @tparam T     The type of elements stored in the array
 * @tparam U     The type of value being assigned
 *
 * @param array  The dynamic_array to modify
 * @param index  The index of the element to update
 * @param value  The new value for that index
 *
 * @throws array_invalid_index if index is outside the valid range
 */
template<typename T, typename U>
void set(dynamic_array<T>& array, int index, U&& value)
{
    array.set(index, std::forward<U>(value));
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
