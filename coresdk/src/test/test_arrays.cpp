// This is 90% AI generated, but has been checked
// by a human who thinks it looks 'probably okay?'

#include <iostream>
#include <string>
#include <stdexcept>

#include "terminal.h"
#include "basics.h"
using namespace splashkit_lib;

#include "splashkit-arrays.h"

namespace fixed_tests
{
    using namespace std;

    int tests_run = 0;
    int tests_passed = 0;

    void assert_true(bool condition, const string &message)
    {
        tests_run++;
        if (!condition)
        {
            cout << "❌ FAILED: " << message << endl;
        }
        else
        {
            tests_passed++;
        }
    }

    template<typename ExceptionType, typename Func>
    void assert_throws(Func func, const string &message)
    {
        tests_run++;
        try
        {
            func();
            cout << "❌ FAILED (no exception): " << message << endl;
        }
        catch (const ExceptionType &)
        {
            tests_passed++;
        }
        catch (...)
        {
            cout << "❌ FAILED (wrong exception): " << message << endl;
        }
    }

    void test_basic_int_operations()
    {
        cout << "\nRunning test_basic_int_operations...\n";

        fixed_array<int, 5> arr(3);
        assert_true(arr.length() == 3, "Length should be set during construction");

        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;

        assert_true(arr[0] == 10, "Index 0 should be 10");
        assert_true(arr[1] == 20, "Index 1 should be 20");
        assert_true(arr[2] == 30, "Index 2 should be 30");
    }

    void test_string()
    {
        cout << "\nRunning test_string...\n";

        fixed_array<std::string, 10> arr(2);
        arr[0] = "Hello";
        arr[1] = "world";
        arr[1] += "!";
        get(arr, 1) += "!";

        assert_true(arr[1] == "world!!", "Index 1 should equal 'world!!'");
    }

    void test_size_and_exceptions()
    {
        cout << "\nRunning test_size_and_exceptions...\n";

        fixed_array<int, 2> arr(2);
        assert_true(arr.length() == 2, "Length should be 2");

        assert_throws<array_invalid_size>(
            [&]() { fixed_array<int, 2> invalid(3); },
            "Creating with size > max should throw array_invalid_size"
        );

        assert_throws<array_invalid_size>(
            [&]() { fixed_array<int, 2> invalid(-1); },
            "Creating with negative size should throw array_invalid_size"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.get(-1); },
            "Accessing negative index should throw"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.get(2); },
            "Accessing index >= size should throw"
        );
    }

    void test_accessor_variants()
    {
        cout << "\nRunning test_accessor_variants...\n";

        fixed_array<int, 3> arr(2);
        arr[0] = 5;
        arr[1] = 10;
        set(arr, 1, 11);

        assert_true(length(arr) == 2, "Free length() should work");
        assert_true(get(arr, 1) == 11, "Free get()/set() should work");

        const fixed_array<int, 3>& const_arr = arr;

        assert_true(const_arr[0] == 5, "Const operator[] should work");
        assert_true(get(const_arr, 0) == 5, "Const free get() should work");
    }


    struct Person
    {
        string name;
        int age;

        bool operator==(const Person &other) const
        {
            return name == other.name && age == other.age;
        }
    };

    void test_complex_types()
    {
        cout << "\nRunning test_complex_types...\n";

        fixed_array<Person, 3> people(2);
        people[0] = {"Alice", 25};
        people[1] = {"Bob", 30};

        assert_true(people.length() == 2, "People length should be 2");
        assert_true(people[0] == Person{"Alice", 25}, "First person correct");

        people[1].age = 31;
        assert_true(people[1].age == 31, "Modifying via operator[] should work");
    }

    void test_nested_arrays()
    {
        cout << "\nRunning test_nested_arrays...\n";

        fixed_array< fixed_array<int, 3>, 2 > outer(2);

        fixed_array<int, 3> inner1(2);
        inner1[0] = 1;
        inner1[1] = 2;

        fixed_array<int, 3> inner2(1);
        inner2[0] = 10;

        outer[0] = inner1;
        outer[1] = inner2;

        assert_true(outer.length() == 2, "Outer length should be 2");
        assert_true(outer[0][0] == 1, "Nested access should work");
        assert_true(outer[0][1] == 2, "Nested access should work");
        assert_true(outer[1][0] == 10, "Nested access should work");
    }

    fixed_array<int, 5> build_sequence()
    {
        fixed_array<int, 5> arr(3);
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        return arr;
    }

    int first_plus_last(fixed_array<int, 5> arr)
    {
        return arr[0] + arr[arr.length() - 1];
    }

    void write_first(fixed_array<int, 5>& arr, int value)
    {
        arr[0] = value;
    }

    void test_copy_and_parameter_passing()
    {
        cout << "\nRunning test_copy_and_parameter_passing...\n";

        fixed_array<int, 5> original = build_sequence();
        fixed_array<int, 5> copied = original;

        copied[0] = 99;
        assert_true(original[0] == 10, "Copy should be independent from original");
        assert_true(copied[0] == 99, "Copied array should hold modified value");

        write_first(original, 7);
        assert_true(original[0] == 7, "Pass-by-reference should modify original");

        assert_true(first_plus_last(original) == 37, "Pass-by-value should work");
    }

    void run_all_tests()
    {
        test_basic_int_operations();
        test_string();
        test_size_and_exceptions();
        test_accessor_variants();
        test_complex_types();
        test_nested_arrays();
        test_copy_and_parameter_passing();

        cout << "\n=========================\n";
        cout << "Tests passed: " << tests_passed << " / " << tests_run << endl;
        cout << "=========================\n";
    }
}

namespace dynamic_tests
{
    using namespace std;

    int tests_run = 0;
    int tests_passed = 0;

    void assert_true(bool condition, const string &message)
    {
        tests_run++;
        if (!condition)
            cout << "❌ FAILED: " << message << endl;
        else
            tests_passed++;
    }

    template<typename ExceptionType, typename Func>
    void assert_throws(Func func, const string &message)
    {
        tests_run++;
        try
        {
            func();
            cout << "❌ FAILED (no exception): " << message << endl;
        }
        catch (const ExceptionType&)
        {
            tests_passed++;
        }
        catch (...)
        {
            cout << "❌ FAILED (wrong exception): " << message << endl;
        }
    }

    struct LifetimeTracker
    {
        static int live_count;
        static int constructions;
        static int destructions;

        int value;

        LifetimeTracker(int v = 0) : value(v)
        {
            constructions++;
            live_count++;
        }

        LifetimeTracker(const LifetimeTracker& other)
            : value(other.value)
        {
            constructions++;
            live_count++;
        }

        ~LifetimeTracker()
        {
            destructions++;
            live_count--;
        }
    };

    int LifetimeTracker::live_count = 0;
    int LifetimeTracker::constructions = 0;
    int LifetimeTracker::destructions = 0;

    void reset_lifetime_counters()
    {
        LifetimeTracker::live_count = 0;
        LifetimeTracker::constructions = 0;
        LifetimeTracker::destructions = 0;
    }


    void test_basic_add_and_growth()
    {
        cout << "\nRunning test_basic_add_and_growth...\n";

        dynamic_array<int> arr;

        assert_true(arr.length() == 0, "Initial length should be 0");
        assert_true(arr.capacity() == 0, "Initial capacity should be 0");

        arr.add(10);
        assert_true(arr.capacity() >= 1, "Capacity should grow after first add");

        arr.add(20);
        assert_true(arr.capacity() >= arr.length(), "Capacity should be at least length");

        arr.add(30);
        assert_true(arr.capacity() >= arr.length(), "Capacity should be at least length");

        assert_true(arr.length() == 3, "Length should be 3");
        assert_true(arr[0] == 10, "Index 0 correct");
        assert_true(arr[2] == 30, "Index 2 correct");
    }

    void test_string()
    {
        cout << "\nRunning test_string...\n";

        dynamic_array<std::string> arr;

        arr.add("Hello");
        add(arr, "world");
        arr[1] += "!";
        get(arr, 1) += "!";

        assert_true(arr[1] == "world!!", "Index 1 should equal 'world!!'");
    }

    void test_remove_and_shrink()
    {
        cout << "\nRunning test_remove_and_shrink...\n";

        dynamic_array<int> arr;

        for (int i = 0; i < 8; ++i)
            arr.add(i);

        int initial_capacity = arr.capacity();

        for (int i = 0; i < 6; ++i)
            arr.remove(0);

        assert_true(arr.length() == 2, "Length should be 2 after removals");
        assert_true(arr.capacity() >= arr.length(),
            "Capacity should remain valid after removals");

        arr.remove(0);
        arr.remove(0);

        assert_true(arr.length() == 0, "Array should be empty");
        assert_true(arr.capacity() >= 0, "Capacity should be non-negative");
        assert_true(arr.capacity() <= initial_capacity, "Capacity should not increase after removals");
    }


    void test_exceptions()
    {
        cout << "\nRunning test_exceptions...\n";

        dynamic_array<int> arr;

        assert_throws<array_invalid_index>(
            [&]() { arr.get(0); },
            "Accessing empty array should throw"
        );

        arr.add(5);

        assert_throws<array_invalid_index>(
            [&]() { arr.get(-1); },
            "Negative index should throw"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.get(5); },
            "Out of range index should throw"
        );
    }


    void test_accessors()
    {
        cout << "\nRunning test_accessors...\n";

        dynamic_array<int> arr;

        add(arr, 10);
        add(arr, 20);
        set(arr, 1, 21);

        assert_true(length(arr) == 2, "Free length works");
        assert_true(capacity(arr) >= 2, "Free capacity works");

        const dynamic_array<int>& const_arr = arr;

        assert_true(get(const_arr, 1) == 21, "Const get works");
        assert_true(const_arr[0] == 10, "Const operator[] works");
    }


    void test_lifetime_management()
    {
        cout << "\nRunning test_lifetime_management...\n";

        reset_lifetime_counters();

        {
            dynamic_array<LifetimeTracker> arr;

            for (int i = 0; i < 5; ++i)
                arr.add(LifetimeTracker(i));

            assert_true(LifetimeTracker::live_count == 5,
                "Live objects should equal array size");

            arr.remove(2);
            assert_true(LifetimeTracker::live_count == 4,
                "Removing should destroy one object");

            arr.remove(0);
            arr.remove(0);
            arr.remove(0);
            arr.remove(0);

            assert_true(LifetimeTracker::live_count == 0,
                "All elements removed should destroy all objects");
        }

        assert_true(LifetimeTracker::live_count == 0,
            "All objects destroyed after array destruction");

        assert_true(
            LifetimeTracker::constructions == LifetimeTracker::destructions,
            "Construction and destruction counts should match"
        );
    }

    dynamic_array<int> build_numbers()
    {
        dynamic_array<int> arr;
        arr.add(1);
        arr.add(2);
        arr.add(3);
        return arr;
    }

    int sum_numbers(dynamic_array<int> arr)
    {
        int result = 0;
        for (int i = 0; i < arr.length(); ++i)
        {
            result += arr[i];
        }
        return result;
    }

    void append_number(dynamic_array<int>& arr, int value)
    {
        arr.add(value);
    }

    void test_copy_and_parameter_passing()
    {
        cout << "\nRunning test_copy_and_parameter_passing...\n";

        dynamic_array<int> original = build_numbers();
        dynamic_array<int> copied = original;

        copied[0] = 99;
        assert_true(original[0] == 1, "Copy should be independent from original");
        assert_true(copied[0] == 99, "Copied array should hold modified value");

        append_number(original, 4);
        assert_true(original.length() == 4, "Pass-by-reference should modify original");

        int sum = sum_numbers(original);
        assert_true(sum == 10, "Pass-by-value should work with copied array parameter");
    }

    void run_all_dynamic_tests()
    {
        test_basic_add_and_growth();
        test_string();
        test_remove_and_shrink();
        test_exceptions();
        test_accessors();
        test_lifetime_management();
        test_copy_and_parameter_passing();

        cout << "\n=========================\n";
        cout << "Tests passed: " << tests_passed
            << " / " << tests_run << endl;
        cout << "=========================\n";
    }

}

void run_arrays_test() {

    fixed_tests::run_all_tests();
    dynamic_tests::run_all_dynamic_tests();
}
