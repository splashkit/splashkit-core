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
#include <array>
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
 * Exception thrown when creating or resizing a dynamic array
 * with an invalid size.
 */
struct array_invalid_size {};


/**
 * A fixed-size array container.
 *
 * fixed_array stores exactly `MAX_SIZE` elements of type T.
 * Elements are stored next to each other and accessed by index.
 *
 * This container does not support add/remove operations.
 * Its length is fixed after construction.
 *
 * Bounds checking is performed for element access.
 * Invalid index access results in an array_invalid_index error.
 *
 * @tparam T             Element type stored in the array
 * @tparam MAX_SIZE      The maximum number of elements the array can hold
 */
template<typename T, int MAX_SIZE>
class fixed_array
{
    const int _size = MAX_SIZE;
    std::array<T, MAX_SIZE> data;

    /**
     * Checks whether an index is valid for this array.
     *
     * @param index       The index to validate.
     * @param access_type Text label describing the operation for error output.
     *
     * @throws array_invalid_index when index is outside 0 to length() - 1.
     */
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
     * Constructs a fixed-size fixed_array.
     *
     * The array always has length MAX_SIZE.
     */
    fixed_array() = default;

    /**
     * Constructs a fixed-size fixed_array and initializes each element.
     *
     * @param initial_value Value assigned to each element
     */
    explicit fixed_array(const T& initial_value)
    {
        fill(initial_value);
    }

    /**
     * Assigns element values from another fixed_array with the same type and
     * max size.
     *
     * @param other The array to copy values from
     *
     * @return This array after copying
     */
    fixed_array& operator=(const fixed_array& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
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
     * Returns a reference to the element at the given index.
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
     * Returns a const reference to the element at the given index.
     *
     * This version allows access on const fixed_array objects.
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
     * Sets the value at the given index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the allowed range
     */
    void set(int index, const T& value)
    {
        check_index(index, "set");
        data[index] = value;
    }

    /**
     * Sets the value at the given index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the allowed range
     */
    void set(int index, T&& value)
    {
        check_index(index, "set");
        data[index] = std::move(value);
    }

    /**
     * Sets every element in this array to the provided value.
     *
     * @param value The value assigned to each element
     */
    void fill(const T& value)
    {
        for (int i = 0; i < _size; ++i)
        {
            data[i] = value;
        }
    }

    /**
     * Attempts to read the value at index without stopping with an error.
     *
     * @param index  The index to read
     * @param value  Variable used to return the value
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_get(int index, T& value) const
    {
        if (index < 0 || index >= _size)
        {
            return false;
        }

        value = data[index];
        return true;
    }

    /**
     * Attempts to update the value at index without stopping with an error.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_set(int index, const T& value)
    {
        if (index < 0 || index >= _size)
        {
            return false;
        }

        data[index] = value;
        return true;
    }

    /**
     * Attempts to update the value at index without stopping with an error.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_set(int index, T&& value)
    {
        if (index < 0 || index >= _size)
        {
            return false;
        }

        data[index] = std::move(value);
        return true;
    }

    /**
     * Returns a reference to the element at the given index.
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
     * Returns a const reference to the element at the given index.
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
 * fixed_array.
 *
 * @tparam T             Element type stored in the array
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The fixed_array to check
 *
 * @return The number of elements currently stored in the array
 */
template<typename T, int MAX_SIZE>
int length(const fixed_array<T, MAX_SIZE>& array)
{
    return array.length();
}

/**
 * Returns a reference to the element at the given index
 * within the given fixed_array.
 *
 * @tparam T             Element type stored in the array
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The fixed_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */
template<typename T, int MAX_SIZE>
T& get(fixed_array<T, MAX_SIZE>& array, int index)
{
    return array.get(index);
}

/**
 * Returns a const reference to the element at the given index
 * within the given fixed_array.
 *
 * This version allows access to elements of a const fixed_array.
 *
 * @tparam T             Element type stored in the array
 * @tparam MAX_SIZE      The maximum capacity of the array
 *
 * @param array  The fixed_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A const reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */

template<typename T, int MAX_SIZE>
const T& get(const fixed_array<T, MAX_SIZE>& array, int index)
{
    return array.get(index);
}

/**
 * Fills every element in the given fixed_array with value.
 */
template<typename T, int MAX_SIZE>
void fill(fixed_array<T, MAX_SIZE>& array, const T& value)
{
    array.fill(value);
}

/**
 * Sets the element at the given index within the given
 * fixed_array.
 *
 * @tparam T         The type of elements stored in the array
 * @tparam MAX_SIZE  The maximum capacity of the array
 * @tparam U         Type of value being assigned
 *
 * @param array  The fixed_array to change
 * @param index  The index of the element to update
 * @param value  The new value for that index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */
template<typename T, int MAX_SIZE, typename U>
void set(fixed_array<T, MAX_SIZE>& array, int index, U&& value)
{
    array.set(index, std::forward<U>(value));
}

/**
 * Attempts to read an element from fixed_array without stopping with an error.
 *
 * @return True when index is valid; otherwise false.
 */
template<typename T, int MAX_SIZE>
bool try_get(const fixed_array<T, MAX_SIZE>& array, int index, T& value)
{
    return array.try_get(index, value);
}

/**
 * Attempts to set an element in fixed_array without stopping with an error.
 *
 * @return True when index is valid; otherwise false.
 */
template<typename T, int MAX_SIZE, typename U>
bool try_set(fixed_array<T, MAX_SIZE>& array, int index, U&& value)
{
    return array.try_set(index, std::forward<U>(value));
}




/**
 * A dynamically resizing array container.
 *
 * dynamic_array stores elements in a row and automatically
 * resizes as needed.
 *
 * It supports copying, assignment, passing by value, returning from functions,
 * and passing by reference.
 *
 * Bounds checking is performed for element access and removal.
 * Invalid index access results in an array_invalid_index error.
 * If there is not enough memory, array_allocation_failed is thrown.
 *
 * @tparam T  The type of elements stored in the array
 */
template<typename T>
class dynamic_array
{
    std::vector<T> data;

    /**
     * Checks whether an index is valid for access/update/removal.
     *
     * @param index       The index to validate.
     * @param access_type Text label describing the operation for error output.
     *
     * @throws array_invalid_index when index is outside 0 to length() - 1.
     */
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

    /**
     * Checks whether an index is valid for insertion.
     *
     * @param index The insertion index to validate.
     *
     * @throws array_invalid_index when index is outside 0 to length().
     */
    void check_insert_index(int index) const
    {
        if (index < 0 || index > static_cast<int>(data.size()))
        {
            write_line("Index to insert (" + to_string(index) + ") is outside of range 0 - " + to_string(static_cast<int>(data.size())) + ".");
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
     * Returns true when this array has no elements.
     *
     * @return True if length() == 0.
     */
    bool is_empty() const
    {
        return data.empty();
    }

    /**
     * Returns a reference to the element at the given index.
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
     * Returns a const reference to the element at the given index.
     *
     * This version allows access on const fixed_array objects.
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
     * Sets the value at the given index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the allowed range
     */
    void set(int index, const T& value)
    {
        check_index(index, "set");
        data[static_cast<size_t>(index)] = value;
    }

    /**
     * Sets the value at the given index.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @throws array_invalid_index if index is outside the allowed range
     */
    void set(int index, T&& value)
    {
        check_index(index, "set");
        data[static_cast<size_t>(index)] = std::move(value);
    }

    /**
     * Sets every element in this array to the provided value.
     *
     * @param value The value assigned to each element
     */
    void fill(const T& value)
    {
        for (size_t i = 0; i < data.size(); ++i)
        {
            data[i] = value;
        }
    }

    /**
     * Attempts to read the value at index without stopping with an error.
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_get(int index, T& value) const
    {
        if (index < 0 || index >= static_cast<int>(data.size()))
        {
            return false;
        }

        value = data[static_cast<size_t>(index)];
        return true;
    }

    /**
     * Attempts to update the value at index without stopping with an error.
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_set(int index, const T& value)
    {
        if (index < 0 || index >= static_cast<int>(data.size()))
        {
            return false;
        }

        data[static_cast<size_t>(index)] = value;
        return true;
    }

    /**
     * Attempts to update the value at index without stopping with an error.
     *
     * @param index  The index to update
     * @param value  The new value for that index
     *
     * @return True when index is valid; otherwise false.
     */
    bool try_set(int index, T&& value)
    {
        if (index < 0 || index >= static_cast<int>(data.size()))
        {
            return false;
        }

        data[static_cast<size_t>(index)] = std::move(value);
        return true;
    }

    /**
     * Returns a reference to the element at the given index.
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
     * Returns a const reference to the element at the given index.
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

    /**
     * Adds a new element to the end of the array.
     *
     * The element is moved into the next available position when possible.
     *
     * @param value  The value to add to the array
     *
     * @throws array_allocation_failed if memory allocation fails.
     */
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
     * Inserts a new element at the given index.
     *
     * @param index The insertion index (0 to length()).
     * @param value The value to insert.
     *
     * @throws array_invalid_index if index is outside 0 to length().
     * @throws array_allocation_failed if memory allocation fails.
     */
    void insert(int index, const T& value)
    {
        check_insert_index(index);
        try
        {
            data.insert(data.begin() + index, value);
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }

    /**
     * Inserts a new element at the given index.
     *
     * @param index The insertion index (0 to length()).
     * @param value The value to insert.
     *
     * @throws array_invalid_index if index is outside 0 to length().
     * @throws array_allocation_failed if memory allocation fails.
     */
    void insert(int index, T&& value)
    {
        check_insert_index(index);
        try
        {
            data.insert(data.begin() + index, std::move(value));
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }

    /**
     * Removes the element at the given index.
     *
     * All elements after the removed element are shifted one position
     * to the left, which changes their indices.
     *
     * @param index  The index of the element to remove
     *
     * @throws array_invalid_index if index is outside the allowed range
     */
    void remove(int index)
    {
        check_index(index, "remove");
        data.erase(data.begin() + index);
    }

    /**
     * Removes the element at the given index.
     * This is a short name for remove(index).
     */
    void remove_at(int index)
    {
        remove(index);
    }

    /**
     * Removes all elements from this array.
     */
    void clear()
    {
        data.clear();
    }

    /**
     * Changes the length of this array.
     *
     * @param new_size The new array length.
     *
     * @throws array_invalid_size if new_size is negative.
     * @throws array_allocation_failed if memory allocation fails.
     */
    void resize(int new_size)
    {
        if (new_size < 0)
        {
            write_line("Invalid dynamic_array size (" + to_string(new_size) + "). Size must be 0 or greater.");
            throw array_invalid_size();
        }

        try
        {
            data.resize(static_cast<size_t>(new_size));
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }

    /**
     * Changes the length of this array and initializes new elements.
     *
     * @param new_size The new array length.
     * @param value    Value assigned to new elements when growing.
     */
    void resize(int new_size, const T& value)
    {
        if (new_size < 0)
        {
            write_line("Invalid dynamic_array size (" + to_string(new_size) + "). Size must be 0 or greater.");
            throw array_invalid_size();
        }

        try
        {
            data.resize(static_cast<size_t>(new_size), value);
        }
        catch (const std::bad_alloc&)
        {
            throw array_allocation_failed();
        }
    }
};

/**
 * Returns the current capacity that the given
 * dynamic_array can store without resizing.
 *
 * @tparam T             Element type stored in the array
 *
 * @param array  The dynamic_array to check
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
 * @tparam T             Element type stored in the array
 *
 * @param array  The dynamic_array to check
 *
 * @return The number of elements currently stored in the array
 */
template<typename T>
int length(const dynamic_array<T>& array)
{
    return array.length();
}

/**
 * Returns true when the given dynamic_array has no elements.
 */
template<typename T>
bool is_empty_array(const dynamic_array<T>& array)
{
    return array.is_empty();
}

/**
 * Returns a reference to the element at the given index
 * within the given dynamic_array.
 *
 * @tparam T             Element type stored in the array
 *
 * @param array  The dynamic_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */
template<typename T>
T& get(dynamic_array<T>& array, int index)
{
    return array.get(index);
}

/**
 * Returns a const reference to the element at the given index
 * within the given dynamic_array.
 *
 * This version allows access to elements of a const dynamic_array.
 *
 * @tparam T             Element type stored in the array
 *
 * @param array  The dynamic_array to access
 * @param index  The index of the element to retrieve
 *
 * @return A const reference to the element at the given index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */

template<typename T>
const T& get(const dynamic_array<T>& array, int index)
{
    return array.get(index);
}

/**
 * Fills every element in the given dynamic_array with value.
 */
template<typename T>
void fill(dynamic_array<T>& array, const T& value)
{
    array.fill(value);
}

/**
 * Sets the element at the given index within the given
 * dynamic_array.
 *
 * @tparam T     The type of elements stored in the array
 * @tparam U     Type of value being assigned
 *
 * @param array  The dynamic_array to change
 * @param index  The index of the element to update
 * @param value  The new value for that index
 *
 * @throws array_invalid_index if index is outside the allowed range
 */
template<typename T, typename U>
void set(dynamic_array<T>& array, int index, U&& value)
{
    array.set(index, std::forward<U>(value));
}

/**
 * Attempts to read an element from dynamic_array without stopping with an error.
 *
 * @return True when index is valid; otherwise false.
 */
template<typename T>
bool try_get(const dynamic_array<T>& array, int index, T& value)
{
    return array.try_get(index, value);
}

/**
 * Attempts to set an element in dynamic_array without stopping with an error.
 *
 * @return True when index is valid; otherwise false.
 */
template<typename T, typename U>
bool try_set(dynamic_array<T>& array, int index, U&& value)
{
    return array.try_set(index, std::forward<U>(value));
}

/**
 * Adds a new element to the end of the given dynamic_array.
 *
 * @tparam T             Element type stored in the array
 * @tparam U             Type of value being added
 *
 * @param array  The dynamic_array to change
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
 * Inserts an element at the given index in the given dynamic_array.
 *
 * @throws array_invalid_index if index is outside 0 to length().
 * @throws array_allocation_failed if memory allocation fails.
 */
template<typename T, typename U>
void insert(dynamic_array<T>& array, int index, U&& value)
{
    array.insert(index, std::forward<U>(value));
}

/**
 * Removes the element at the given index from the given
 * dynamic_array.
 *
 * All elements following the removed element are shifted one
 * position to the left.
 *
 * @tparam T             Element type stored in the array
 *
 * @param array  The dynamic_array to change
 * @param index  The index of the element to remove
 *
 * @throws array_invalid_index if index is outside the allowed range
 */
template<typename T>
void remove(dynamic_array<T>& array, int index)
{
    array.remove(index);
}

/**
 * Removes the element at the given index from the given dynamic_array.
 * This is a short name for remove(array, index).
 */
template<typename T>
void remove_at(dynamic_array<T>& array, int index)
{
    array.remove_at(index);
}

/**
 * Removes all elements from the given dynamic_array.
 */
template<typename T>
void clear(dynamic_array<T>& array)
{
    array.clear();
}

/**
 * Changes the length of the given dynamic_array.
 */
template<typename T>
void resize(dynamic_array<T>& array, int new_size)
{
    array.resize(new_size);
}

/**
 * Changes the length of the given dynamic_array and initializes new elements.
 */
template<typename T>
void resize(dynamic_array<T>& array, int new_size, const T& value)
{
    array.resize(new_size, value);
}

#endif
