#define CATCH_CONFIG_MAIN
#include "tests/catch.hpp"
#include <list>
#include "List.hpp"

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }
// a predicate implemented as a class:
struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};
// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }
// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};
// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }
// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

TEST_CASE("List", "[list]")
{
    std::list<int> second (4,100);                       // four ints with value 100
    ft::List<int> second_impl(4,100);

    int myints[] = {16,2,77,29};

    SECTION("Constructors") {
        SECTION("empty list of ints") {
            std::list<int> first;                                // empty list of ints
            ft::List<int> first_impl;
            REQUIRE( first_impl.front() == first.front() );
        }
        SECTION("four ints with value 100") {
            REQUIRE( second_impl.front() == second.front );
        }
        SECTION("iterating through second") {
            std::list<int> third(second.begin(),second.end());  // iterating through second
            ft::List<int> third_impl(second_impl.begin(), second_impl.end());
            REQUIRE( third_impl.front() == third.front() );
        }
        SECTION("iterating through second") {
            std::list<int> third(second.begin(),second.end());  // iterating through second
            ft::List<int> third_impl(second_impl.begin(), second_impl.end());
            std::list<int> fourth(third);                       // a copy of third
            ft::List<int> fourth_impl(second);
            REQUIRE( fourth_impl.front() == fourth.front() );
        }
        SECTION("fifth test of constructor") {
            std::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
            ft::List<int> fifth_impl (myints, myints + sizeof(myints) / sizeof(int) );
            REQUIRE( fifth_impl.front() == fifth.front() );
        }
    }
    SECTION("list operator=") {
        std::list<int> first (3);      // list of 3 zero-initialized ints
        std::list<int> second (5);     // list of 5 zero-initialized ints
        second = first;
        first = std::list<int>();

        ft::List<int> first_impl (3);      // list of 3 zero-initialized ints
        ft::List<int> second_impl (5);     // list of 5 zero-initialized ints
        second_impl = first_impl;
        first_impl = ft::List<int> ();
        REQUIRE( first_impl.front() == second.front() );
        REQUIRE( second_impl.front() == second.front() );
    }
    SECTION("Iterators") {
        int myints[] = {75,23,65,42,13};
        std::list<int> mylist (myints,myints+5);
        ft::List<int> mylist_impl (myints,myints+5);
        SECTION("list begin") {
            ft::List<int>::iterator it_impl = mylist_impl.begin(); 
            std::list<int>::iterator it = mylist.begin(); 
            REQUIRE( *it_impl == *it );
        }
        SECTION("list end") {
            ft::List<int>::iterator it_impl = mylist_impl.end(); 
            std::list<int>::iterator it = mylist.end(); 
            REQUIRE( *it_impl == *it );
        }
        SECTION("list rbegin") {
            ft::List<int>::reverse_iterator it_impl = mylist_impl.end(); 
            std::list<int>::reverse_iterator it = mylist.end(); 
            REQUIRE( *it_impl == *it );
        }
        SECTION("list rend") {
            ft::List<int>::reverse_iterator it_impl = mylist_impl.begin(); 
            std::list<int>::reverse_iterator it = mylist.begin(); 
            REQUIRE( *it_impl == *it );
        }
    }
    SECTION("Capacity") {
        SECTION("empty") {
            std::list<int> mylist;
            ft::List<int> mylist_impl;
            int sum (0);
            int sum_impl (0);

            for (int i=1;i<=10;++i) mylist.push_back(i);
            for (int i=1;i<=10;++i) mylist_impl.push_back(i);

            while (!mylist.empty())
            {
             sum += mylist.front();
             mylist.pop_front();
            }
            while (!mylist_impl.empty())
            {
             sum_impl += mylist_impl.front();
             mylist_impl.pop_front();
            }
            REQUIRE( sum_impl == sum );
        }
        SECTION("size") {
            std::list<int> myints;
            ft::List<int> myints_impl;
            REQUIRE( myints_impl.size() == myints.size() );
            for (int i=0; i<10; i++) myints.push_back(i);
            for (int i=0; i<10; i++) myints_impl.push_back(i);
            REQUIRE( myints_impl.size() == myints.size() );
            myints.insert (myints.begin(),10,100);
            myints_impl.insert (myints_impl.begin(),10,100);
            REQUIRE( myints_impl.size() == myints.size() );
            myints.pop_back();
            myints_impl.pop_back();
            REQUIRE( myints_impl.size() == myints.size() );
        }
        SECTION("max_size") {
            std::list<int> mylist;
            ft::List<int> myints_impl;
            REQUIRE( myints_impl.max_size() == myints.max_size() );
        }
    }
    SECTION("Element access") {
        SECTION("front") {
            std::list<int> mylist;
            ft::List<int> mylist_impl;
            mylist.push_back(77);
            mylist_impl.push_back(77);
            mylist.push_back(22);
            mylist_impl.push_back(22);
            mylist.front() -= mylist.back();
            mylist_impl.front() -= mylist_impl.back();
            REQUIRE( mylist_impl.front() == mylist.front() );
        }
        SECTION("back") {
            std::list<int> mylist;
            ft::List<int> mylist_impl;
            mylist.push_back(10);
            mylist_impl.push_back(10);
            while (mylist.back() != 0)
            {
              mylist.push_back ( mylist.back() -1 );
            }
            while (mylist_impl.back() != 0)
            {
              mylist_impl.push_back ( mylist_impl.back() -1 );
            }
            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            ++it;
            ++it_impl;
            REQUIRE( mylist_impl.front() == mylist.front() );
        }
    }
    SECTION("Modifiers") {
        SECTION("Assign") {
            std::list<int> first;
            ft::List<int> first_impl;
            std::list<int> second;
            std::List<int> second_impl;

            first.assign (7,100);                      // 7 ints with value 100
            first_impl.assign (7,100);                      // 7 ints with value 100

            second.assign (first.begin(),first.end()); // a copy of first
            second_impl.assign (first.begin(),first.end()); // a copy of first

            int myints[]={1776,7,4};
            first.assign (myints,myints+3);            // assigning from array
            first_impl.assign (myints,myints+3);            // assigning from array
            REQUIRE( int(first.size()) == int(first_impl.size()) );
            REQUIRE( int(second.size()) == int(second_impl.size()) );
        }
        SECTION("push_front") {
            std::list<int> mylist (2,100);         // two ints with a value of 100
            ft::List<int> mylist_impl (2,100);         // two ints with a value of 100
            mylist.push_front (200);
            mylist_impl.push_front (200);
            mylist.push_front (300);
            mylist_impl.push_front (300);
            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("pop_front") {
            std::list<int> mylist;         // two ints with a value of 100
            ft::List<int> mylist_impl;         // two ints with a value of 100
            mylist.push_front (100);
            mylist_impl.push_front (100);
            mylist.push_front (200);
            mylist_impl.push_front (200);
            mylist.push_front (300);
            mylist_impl.push_front (300);
            while (!mylist.empty() && !mylist_impl.empty())
            {
                REQUIRE(mylist.front() == mylist_impl.front());
                mylist.pop_front();
                mylist_impl.pop_front();
            }
            REQUIRE(mylist.size() == mylist_impl.size());
        }
        SECTION("push_back") {
            std::list<int> mylist;         // two ints with a value of 100
            ft::List<int> mylist_impl;         // two ints with a value of 100
            mylist.push_back (5);
            mylist_impl.push_back (5);
            REQUIRE(mylist.size() == mylist_impl.size());
        }
        SECTION("pop_back") {
            int sum (0);
            int sum_impl (0);
            std::list<int> mylist;         // two ints with a value of 100
            ft::List<int> mylist_impl;         // two ints with a value of 100
            mylist.push_front (100);
            mylist_impl.push_front (100);
            mylist.push_front (200);
            mylist_impl.push_front (200);
            mylist.push_front (300);
            mylist_impl.push_front (300);
            while (!mylist.empty())
            {
                sum+=mylist.back();
                mylist.pop_back();
            }
            while (!mylist_impl.empty())
            {
                sum_impl+=mylist_impl.back();
                mylist_impl.pop_back();
            }
            REQUIRE(sum_impl == sum);
        }
        SECTION("insert") {
            std::list<int> mylist;
            ft::List<int> mylist_impl;
            std::list<int>::iterator it;
            ft::list<int>::iterator it_impl;
            for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5
            for (int i=1; i<=5; ++i) mylist_impl.push_back(i); // 1 2 3 4 5
            it = mylist.begin();
            it_impl = mylist_impl.begin();
            ++it;       // it points now to number 2           ^
            ++it_impl;       // it points now to number 2           ^
            mylist.insert (it,10);                        // 1 10 2 3 4 5
            mylist_impl.insert (it_impl,10);                        // 1 10 2 3 4 5
            mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
            mylist_impl.insert (it_impl,2,20);                      // 1 10 20 20 2 3 4 5
            it = mylist.begin();
            it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("erase") {
            std::list<int> mylist;
            std::list<int>::iterator it1,it2;
            for (int i=1; i<10; ++i) mylist.push_back(i*10);
                                        // 10 20 30 40 50 60 70 80 90
            it1 = it2 = mylist.begin(); // ^^
            advance (it2,6);            // ^                 ^
            ++it1;                      //    ^              ^
            it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
                                        //    ^           ^
            it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
                                        //    ^           ^
            ++it1;                      //       ^        ^
            --it2;                      //       ^     ^
            mylist.erase (it1,it2);     // 10 30 60 80 90
                                        //        ^
            ft::List<int> mylist_impl;
            ft::List<int>::iterator it1_impl,it2_impl;
            for (int i=1; i<10; ++i) mylist_impl.push_back(i*10);
                                        // 10 20 30 40 50 60 70 80 90
            it1_impl = it2_impl = mylist_impl.begin(); // ^^
            advance (it2_impl,6);            // ^                 ^
            ++it1_impl;                      //    ^              ^
            it1_impl = mylist_impl.erase (it1_impl);   // 10 30 40 50 60 70 80 90
            it2_impl = mylist_impl.erase (it2_impl);   // 10 30 40 50 60 80 90
            ++it1_impl;                      //       ^        ^
            --it2_impl;                      //       ^     ^
            mylist_impl.erase (it1_impl,it2_impl);     // 10 30 60 80 90
            while ( it1 != mylist.end() && it1_impl != mylist_impl.end() )
            {
                REQUIRE( *it1 == *it1_impl);
                ++it1;
                ++it1_impl;
            }
        }
        SECTION("swap") {
            std::list<int> first (3,100);   // three ints with a value of 100
            std::list<int> second (5,200);  // five ints with a value of 200
            first.swap(second);
            std::list<int>::iterator it=second.begin();

            ft::List<int> first_impl (3,100);   // three ints with a value of 100
            ft::List<int> second_impl (5,200);  // five ints with a value of 200
            first_impl.swap(second_impl);
            ft::List<int>::iterator it_impl=second_impl.begin();

            while ( it != second.end() && it_impl != second_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("resize") {
            std::list<int> mylist;
            for (int i=1; i<10; ++i) mylist.push_back(i);
            mylist.resize(5);
            mylist.resize(8,100);
            mylist.resize(12);

            ft::List<int> mylist_impl;
            for (int i=1; i<10; ++i) mylist_impl.push_back(i);
            mylist_impl.resize(5);
            mylist_impl.resize(8,100);
            mylist_impl.resize(12);

            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("clear") {
            std::list<int> mylist;
            std::list<int>::iterator it;
            mylist.push_back (100);
            mylist.push_back (200);
            mylist.push_back (300);
            mylist.clear();
            mylist.push_back (1101);
            mylist.push_back (2202);

            ft::List<int> mylist_impl;
            ft::List<int>::iterator it_impl;
            mylist_impl.push_back (100);
            mylist_impl.push_back (200);
            mylist_impl.push_back (300);
            mylist_impl.clear();
            mylist_impl.push_back (1101);
            mylist_impl.push_back (2202);

            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("splice") {
            std::list<int> mylist1, mylist2;
            std::list<int>::iterator it;
            for (int i=1; i<=4; ++i)
             mylist1.push_back(i);      // mylist1: 1 2 3 4
            for (int i=1; i<=3; ++i)
             mylist2.push_back(i*10);   // mylist2: 10 20 30
            it = mylist1.begin();
            ++it;                         // points to 2
            mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                        // mylist2 (empty)
                                        // "it" still points to 2 (the 5th element)
            mylist2.splice (mylist2.begin(),mylist1, it);
                                        // mylist1: 1 10 20 30 3 4
                                        // mylist2: 2
                                        // "it" is now invalid.
            it_impl = mylist1_impl.begin();
            ft::advance(it_impl,3);           // "it_impl" points now to 30
            mylist1_impl.splice ( mylist1_impl.begin(), mylist1_impl, it_impl, mylist1_impl.end());
                                        // mylist1_impl: 30 3 4 1 10 20
            
            ft::List<int> mylist1_impl, mylist2_impl;
            ft::List<int>::iterator it_impl;
            for (int i=1; i<=4; ++i)
             mylist1_impl.push_back(i);      // mylist1_impl: 1 2 3 4
            for (int i=1; i<=3; ++i)
             mylist2_impl.push_back(i*10);   // mylist2_impl: 10 20 30
            it_impl = mylist1_impl.begin();
            ++it_impl;                         // points to 2
            mylist1_impl.splice (it_impl, mylist2_impl); // mylist1_impl: 1 10 20 30 2 3 4
            mylist2_impl.splice (mylist2_impl.begin(),mylist1_impl, it_impl);
            it_impl = mylist1_impl.begin();
            ft::advance(it_impl,3);           // "it_impl" points now to 30
            mylist1_impl.splice ( mylist1_impl.begin(), mylist1_impl, it_impl, mylist1_impl.end());

            it = mylist1.begin();
            it_impl = mylist1_impl.begin();
            while ( it != mylist1.end() && it_impl != mylist1_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("remove") {
            int myints[]= {17,89,7,14};
            std::list<int> mylist (myints,myints+4);
            mylist.remove(89);
            
            ft::List<int> mylist_impl (myints,myints+4);
            mylist_impl.remove(89);

            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("remove_if") {
            int myints[]= {15,36,7,17,20,39,4,1};
            std::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1
            mylist.remove_if (single_digit);           // 15 36 17 20 39
            mylist.remove_if (is_odd());               // 36 20

            ft::List<int> mylist_impl (myints,myints+8);   // 15 36 7 17 20 39 4 1
            mylist_impl.remove_if (single_digit);           // 15 36 17 20 39
            mylist_impl.remove_if (is_odd());               // 36 20

            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("unique") {
            double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                                 12.77, 73.35, 72.25, 15.3,  72.25 };
            std::list<double> mylist (mydoubles,mydoubles+10);
            mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                                       // 15.3,  72.25, 72.25, 73.0,  73.35
            mylist.unique();           //  2.72,  3.14, 12.15, 12.77
                                       // 15.3,  72.25, 73.0,  73.35
            mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                                 // 15.3,  72.25, 73.0
            mylist.unique (is_near());           //  2.72, 12.15, 72.25

            ft::List<double> mylist_impl (mydoubles,mydoubles+10);
            mylist_impl.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
            mylist_impl.unique();           //  2.72,  3.14, 12.15, 12.77
            mylist_impl.unique (same_integral_part);  //  2.72,  3.14, 12.15
            mylist_impl.unique (is_near());           //  2.72, 12.15, 72.25

            std::list<double>::iterator it = mylist.begin();
            ft::List<double>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("merge") {
            std::list<double> first, second;
            first.push_back (3.1);
            first.push_back (2.2);
            first.push_back (2.9);
            second.push_back (3.7);
            second.push_back (7.1);
            second.push_back (1.4);
            first.sort();
            second.sort();
            first.merge(second);
            // (second is now empty)
            second.push_back (2.1);
            first.merge(second,mycomparison);

            ft::List<double> first_impl, second_impl;
            first_impl.push_back (3.1);
            first_impl.push_back (2.2);
            first_impl.push_back (2.9);
            second_impl.push_back (3.7);
            second_impl.push_back (7.1);
            second_impl.push_back (1.4);
            first_impl.sort();
            second_impl.sort();
            first_impl.merge(second_impl);
            // (second is now empty)
            second_impl.push_back (2.1);
            first_impl.merge(second,mycomparison);

            std::list<double>::iterator it = first.begin();
            ft::List<double>::iterator it_impl = first_impl.begin();
            while ( it != first.end() && it_impl != first_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("sort") {
            std::list<std::string> mylist;
            std::list<std::string>::iterator it;
            mylist.push_back ("one");
            mylist.push_back ("two");
            mylist.push_back ("Three");
            mylist.sort();

            ft::List<std::string> mylist_impl;
            ft::List<std::string>::iterator it_impl;
            mylist_impl.push_back ("one");
            mylist_impl.push_back ("two");
            mylist_impl.push_back ("Three");
            mylist_impl.sort();
            
            it = mylist.begin();
            it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }

            mylist.sort(compare_nocase);
            mylist_impl.sort(compare_nocase);

            it = mylist.begin();
            it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
        SECTION("reverse") {
            std::list<int> mylist;
            for (int i=1; i<10; ++i) mylist.push_back(i);
            mylist.reverse();

            ft::List<int> mylist_impl;
            for (int i=1; i<10; ++i) mylist_impl.push_back(i);
            mylist_impl.reverse();

            std::list<int>::iterator it = mylist.begin();
            ft::List<int>::iterator it_impl = mylist_impl.begin();
            while ( it != mylist.end() && it_impl != mylist_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
        }
    }
}
