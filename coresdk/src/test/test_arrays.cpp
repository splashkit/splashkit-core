// This is 90% AI generated, but has been checked
// by a human who thinks it looks 'probably okay?'

#include <iostream>
#include <string>
#include <stdexcept>

#include "terminal.h"
#include "basics.h"
using namespace splashkit_lib;

#include "splashkit-arrays.h"

namespace bounded_tests
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

        bounded_array<int, 5> arr;

        assert_true(arr.length() == 0, "Initial length should be 0");
        assert_true(arr.capacity() == 5, "Capacity should be 5");

        arr.add(10);
        arr.add(20);
        arr.add(30);

        assert_true(arr.length() == 3, "Length should be 3 after 3 adds");
        assert_true(arr[0] == 10, "Index 0 should be 10");
        assert_true(arr[1] == 20, "Index 1 should be 20");
        assert_true(arr[2] == 30, "Index 2 should be 30");
    }

    void test_string()
    {
        cout << "\nRunning test_string...\n";

        bounded_array<std::string, 10> arr;

        arr.add("Hello");
        add(arr, "world");
        arr[1] += "!";
        get(arr, 1) += "!";

        assert_true(arr[1] == "world!!", "Index 1 should equal 'world!!'");
    }

    void test_capacity_and_exceptions()
    {
        cout << "\nRunning test_capacity_and_exceptions...\n";

        bounded_array<int, 2> arr;

        arr.add(1);
        arr.add(2);

        assert_true(arr.length() == 2, "Length should be 2");

        assert_throws<array_full>(
            [&]() { arr.add(3); },
            "Adding past capacity should throw array_full"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.get(-1); },
            "Accessing negative index should throw"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.get(2); },
            "Accessing index >= size should throw"
        );

        assert_throws<array_invalid_index>(
            [&]() { arr.remove(5); },
            "Removing invalid index should throw"
        );
    }


    void test_remove_and_shifting()
    {
        cout << "\nRunning test_remove_and_shifting...\n";

        bounded_array<int, 5> arr;

        arr.add(10);
        arr.add(20);
        arr.add(30);
        arr.add(40);

        arr.remove(1);  // remove 20

        assert_true(arr.length() == 3, "Length should decrease after remove");
        assert_true(arr[0] == 10, "Index 0 should remain 10");
        assert_true(arr[1] == 30, "Index 1 should now be 30");
        assert_true(arr[2] == 40, "Index 2 should now be 40");

        arr.remove(0);  // remove 10

        assert_true(arr[0] == 30, "After removing first element");
        assert_true(arr.length() == 2, "Length should be 2");
    }


    void test_accessor_variants()
    {
        cout << "\nRunning test_accessor_variants...\n";

        bounded_array<int, 3> arr;
        add(arr, 5);
        add(arr, 10);

        assert_true(length(arr) == 2, "Free length() should work");
        assert_true(capacity(arr) == 3, "Free capacity() should work");
        assert_true(get(arr, 1) == 10, "Free get() should work");

        const bounded_array<int, 3>& const_arr = arr;

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

        bounded_array<Person, 3> people;

        people.add({"Alice", 25});
        people.add({"Bob", 30});

        assert_true(people.length() == 2, "People length should be 2");
        assert_true(people[0] == Person{"Alice", 25}, "First person correct");

        people[1].age = 31;
        assert_true(people[1].age == 31, "Modifying via operator[] should work");
    }

    void test_nested_arrays()
    {
        cout << "\nRunning test_nested_arrays...\n";

        bounded_array< bounded_array<int, 3>, 2 > outer;

        bounded_array<int, 3> inner1;
        inner1.add(1);
        inner1.add(2);

        bounded_array<int, 3> inner2;
        inner2.add(10);

        outer.add(inner1);
        outer.add(inner2);

        assert_true(outer.length() == 2, "Outer length should be 2");
        assert_true(outer[0][0] == 1, "Nested access should work");
        assert_true(outer[0][1] == 2, "Nested access should work");
        assert_true(outer[1][0] == 10, "Nested access should work");

        outer[0].remove(0);
        assert_true(outer[0][0] == 2, "Nested remove should shift correctly");
    }
    void run_all_tests()
    {
        test_basic_int_operations();
        test_string();
        test_capacity_and_exceptions();
        test_remove_and_shifting();
        test_accessor_variants();
        test_complex_types();
        test_nested_arrays();

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
        assert_true(arr.capacity() == 1, "Capacity should grow to 1");

        arr.add(20);
        assert_true(arr.capacity() == 2, "Capacity should double to 2");

        arr.add(30);
        assert_true(arr.capacity() == 4, "Capacity should double to 4");

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
        assert_true(arr.capacity() < initial_capacity,
            "Capacity should shrink after enough removals");

        arr.remove(0);
        arr.remove(0);

        assert_true(arr.length() == 0, "Array should be empty");
        assert_true(arr.capacity() == 0, "Capacity should shrink to 0");
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

        assert_true(length(arr) == 2, "Free length works");
        assert_true(capacity(arr) >= 2, "Free capacity works");

        const dynamic_array<int>& const_arr = arr;

        assert_true(get(const_arr, 1) == 20, "Const get works");
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

    void run_all_dynamic_tests()
    {
        test_basic_add_and_growth();
        test_string();
        test_remove_and_shrink();
        test_exceptions();
        test_accessors();
        test_lifetime_management();

        cout << "\n=========================\n";
        cout << "Tests passed: " << tests_passed
            << " / " << tests_run << endl;
        cout << "=========================\n";
    }

}

void run_arrays_test() {

    bounded_tests::run_all_tests();
    dynamic_tests::run_all_dynamic_tests();
}
