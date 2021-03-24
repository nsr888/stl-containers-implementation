#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <list>
#include <vector>
#include <iterator>
#include "List.hpp"
#include "Vector.hpp"

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
{ return ( int(first) < int(second) ); }
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
            REQUIRE( second_impl.front() == second.front() );
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
            ft::List<int> fourth_impl(second_impl);
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
        REQUIRE( first_impl.front() == first.front() );
        REQUIRE( first_impl.size() == first.size() );
        REQUIRE( second_impl.front() == second.front() );
        REQUIRE( second_impl.size() == second.size() );
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
            ft::List<int>::reverse_iterator rit_impl = mylist_impl.rend(); 
            std::list<int>::reverse_iterator rit = mylist.rend(); 
            REQUIRE( *rit_impl == *rit );
            --rit_impl;
            --rit;
            REQUIRE( *rit_impl == *rit );
            ++rit_impl;
            ++rit;
            REQUIRE( *rit_impl == *rit );
        }
        SECTION("list rend") {
            ft::List<int>::reverse_iterator rit_impl = mylist_impl.rbegin(); 
            std::list<int>::reverse_iterator rit = mylist.rbegin(); 
            REQUIRE( *rit_impl == *rit );
            --rit_impl;
            --rit;
            REQUIRE( *rit_impl == *rit );
            ++rit_impl;
            ++rit;
            REQUIRE( *rit_impl == *rit );
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
            myints.insert(myints.begin(), 10, 100);
            myints_impl.insert(myints_impl.begin(), 10, 100);
            REQUIRE( myints_impl.size() == myints.size() );
            myints.pop_back();
            myints_impl.pop_back();
            REQUIRE( myints_impl.size() == myints.size() );
        }
        SECTION("max_size") {
            ft::List<int> mylist_impl;
            REQUIRE( mylist_impl.max_size() > 0 );
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
            std::list<int> second_impl;

            first.assign (7,100);                      // 7 ints with value 100
            first_impl.assign (7,100);                      // 7 ints with value 100

            second.assign (first.begin(),first.end()); // a copy of first
            second_impl.assign (first.begin(),first.end()); // a copy of first

            int myints[]={1776,7,4};
            first.assign (myints,myints+3);            // assigning from array
            first_impl.assign (myints,myints+3);            // assigning from array
            REQUIRE( int(first.size()) == int(first_impl.size()) );
            REQUIRE( int(first.back()) == int(first.back()) );
            REQUIRE( int(second.size()) == int(second_impl.size()) );
            REQUIRE( int(second.back()) == int(second_impl.back()) );
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
            ft::List<int>::iterator it_impl;
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
            std::list<int>::iterator it1, it2, it3;
            for (int i=1; i<10; ++i) mylist.push_back(i*10);
                                        // 10 20 30 40 50 60 70 80 90
            it1 = it2 = mylist.begin(); // ^^
            /* std::advance (it2,6);            // ^                 ^ */
            ++it1;                      //    ^              ^
            it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
                                        //    ^           ^
            it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
                                        //    ^           ^
            ++it1;                      //       ^        ^
            --it2;                      //       ^     ^
            it3 = mylist.erase (it1, it2);     // 10 30 60 80 90
                                        //        ^
            ft::List<int> mylist_impl;
            ft::List<int>::iterator it1_impl, it2_impl, it3_impl;
            for (int i=1; i<10; ++i) mylist_impl.push_back(i*10);
                                        // 10 20 30 40 50 60 70 80 90
            it1_impl = it2_impl = mylist_impl.begin(); // ^^
            /* std::advance(it2_impl,6);            // ^                 ^ */
            ++it1_impl;                      //    ^              ^
            it1_impl = mylist_impl.erase (it1_impl);   // 10 30 40 50 60 70 80 90
            it2_impl = mylist_impl.erase (it2_impl);   // 10 30 40 50 60 80 90
            ++it1_impl;                      //       ^        ^
            --it2_impl;                      //       ^     ^
            it3_impl = mylist_impl.erase (it1_impl, it2_impl);     // 10 30 60 80 90

            REQUIRE( *it3 == *it3_impl );

            it1 = mylist.begin();
            it1_impl = mylist_impl.begin();
            while ( it1 != mylist.end() && it1_impl != mylist_impl.end() )
            {
                REQUIRE( *it1 == *it1_impl);
                ++it1;
                ++it1_impl;
            }
        }
        SECTION("swap") {
            std::list<int> first;   // three ints with a value of 100
            for (int i = 1; i < 10; ++i) first.push_back(i*10);
            std::list<int> second (5,200);  // five ints with a value of 200
            first.swap(second);
            std::list<int>::iterator it = second.begin();

            ft::List<int> first_impl;   // three ints with a value of 100
            for (int i = 1; i < 10; ++i) first_impl.push_back(i*10);
            ft::List<int> second_impl (5,200);  // five ints with a value of 200
            first_impl.swap(second_impl);
            ft::List<int>::iterator it_impl = second_impl.begin();

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

            it = mylist.begin();
            it_impl = mylist_impl.begin();
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
            it = mylist1.begin();
            it++;
            it++;
            it++;
            mylist1.splice (mylist1.begin(), mylist1, it, mylist1.end());
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
            ++it_impl;
            ++it_impl;
            ++it_impl;
            mylist1_impl.splice ( mylist1_impl.begin(), mylist1_impl, it_impl, mylist1_impl.end());

            it = mylist1.begin();
            it_impl = mylist1_impl.begin();
            while ( it != mylist1.end() && it_impl != mylist1_impl.end() )
            {
                REQUIRE( *it == *it_impl);
                ++it;
                ++it_impl;
            }
            it = mylist2.begin();
            it_impl = mylist2_impl.begin();
            while ( it != mylist2.end() && it_impl != mylist2_impl.end() )
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
            first.push_back (2.2);
            first.push_back (2.9);
            first.push_back (3.1);
            second.push_back (1.4);
            second.push_back (3.7);
            second.push_back (7.1);
            first.merge(second);
            // (second is now empty)
            second.push_back (2.1);
            first.merge(second, mycomparison);

            ft::List<double> first_impl, second_impl;
            first_impl.push_back (2.2);
            first_impl.push_back (2.9);
            first_impl.push_back (3.1);
            second_impl.push_back (1.4);
            second_impl.push_back (3.7);
            second_impl.push_back (7.1);
            first_impl.merge(second_impl);
            // (second is now empty)
            second_impl.push_back (2.1);
            first_impl.merge(second_impl, mycomparison);

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

TEST_CASE("Vector", "[vector]") {
    SECTION("Constructors") {
        std::vector<int> first;                                // empty vector of ints
        std::vector<int> second (4,100);                       // four ints with value 100
        std::vector<int> third (second.begin(),second.end());  // iterating through second
        std::vector<int> fourth (third);                       // a copy of third

        // the iterator constructor can also be used to construct from arrays:
        int myints[] = {16,2,77,29};
        std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

        ft::Vector<int> first_impl;                                // empty vector of ints
        ft::Vector<int> second_impl (4,100);                       // four ints with value 100
        ft::Vector<int> third_impl (second_impl.begin(),second_impl.end());  // iterating through second
        ft::Vector<int> fourth_impl (third_impl);                       // a copy of third

        // the iterator constructor can also be used to construct from arrays:
        ft::Vector<int> fifth_impl (myints, myints + sizeof(myints) / sizeof(int) );

        std::vector<int>::iterator it = fifth.begin();
        ft::Vector<int>::iterator it_impl = fifth_impl.begin();
        for (; it != fifth.end() && it_impl != fifth_impl.end(); ++it, ++it_impl)
            REQUIRE( *it == *it_impl);
    }
    SECTION("vector::operator=") {
        std::vector<int> foo (3,0);
        std::vector<int> bar (5,0);
        bar = foo;
        foo = std::vector<int>();
        ft::Vector<int> foo_impl (3,0);
        ft::Vector<int> bar_impl (5,0);
        bar_impl = foo_impl;
        foo_impl = ft::Vector<int>();
        REQUIRE( foo.size() == foo_impl.size() );
        REQUIRE( bar.size() == bar_impl.size() );
    }
    SECTION("begin, end") {
        std::vector<int> myvector;
        for (int i=1; i<=5; i++) myvector.push_back(i);
        ft::Vector<int> myvector_impl;
        for (int i=1; i<=5; i++) myvector_impl.push_back(i);
        std::vector<int>::iterator it = myvector.begin();
        ft::Vector<int>::iterator it_impl = myvector_impl.begin();
        for (; it != myvector.end() && it_impl != myvector_impl.end(); ++it,++it_impl)
            REQUIRE( *it == *it_impl);
    }
    SECTION("rbegin, rend") {
        std::vector<int> myvector(5);
        int i = 0;
        std::vector<int>::reverse_iterator rit = myvector.rbegin();
        for (; rit!= myvector.rend(); ++rit)
            *rit = ++i;
        ft::Vector<int> myvector_impl(5);
        i = 0;
        ft::Vector<int>::reverse_iterator rit_impl = myvector_impl.rbegin();
        for (; rit_impl != myvector_impl.rend(); ++rit_impl)
            *rit_impl = ++i;
        std::vector<int>::iterator it = myvector.begin();
        ft::Vector<int>::iterator it_impl = myvector_impl.begin();
        for (; it != myvector.end() && it_impl != myvector_impl.end(); ++it,++it_impl)
        {
            REQUIRE( *it == *it_impl);
        }
    }
    SECTION("size") {
        std::vector<int> myvector;
        ft::Vector<int> myvector_impl;
        REQUIRE(myvector.size() == myvector_impl.size());
        for (int i=1; i<=5; i++) myvector.push_back(i);
        for (int i=1; i<=5; i++) myvector_impl.push_back(i);
        REQUIRE(myvector.size() == myvector_impl.size());
        myvector.insert (myvector.end(),10,100);
        myvector_impl.insert (myvector_impl.end(),10,100);
        REQUIRE(myvector.size() == myvector_impl.size());
        myvector.pop_back();
        myvector_impl.pop_back();
        REQUIRE(myvector.size() == myvector_impl.size());
    }
    SECTION("max_size")
    {
        ft::Vector<int> myvector_impl;
        for (int i=1; i<=105; i++) myvector_impl.push_back(i);
        REQUIRE(myvector_impl.max_size() > 0);
    }
    SECTION("resize")
    {
        std::vector<int> myvector;
        for (int i=1; i<=10; i++) myvector.push_back(i);
        myvector.resize(5);
        myvector.resize(8,100);
        myvector.resize(12);
        ft::Vector<int> myvector_impl;
        for (int i=1; i<=10; i++) myvector_impl.push_back(i);
        myvector_impl.resize(5);
        myvector_impl.resize(8,100);
        myvector_impl.resize(12);
        for (size_t i = 0; i < myvector.size() && i < myvector_impl.size(); i++)
            REQUIRE(myvector[i] == myvector_impl[i]);
    }
    SECTION("capacity")
    {
        std::vector<int> myvector;
        for (int i=1; i<=105; i++) myvector.push_back(i);
        ft::Vector<int> myvector_impl;
        for (int i=1; i<=105; i++) myvector_impl.push_back(i);
        REQUIRE(myvector.capacity() == myvector_impl.capacity());
    }
    SECTION("empty")
    {
        int sum(0);
        std::vector<int> myvector;
        for (int i=1; i<=10; i++) myvector.push_back(i);
        while (!myvector.empty()) {
            sum += myvector.back();
            myvector.pop_back();
        } 
        int sum_impl(0);
        ft::Vector<int> myvector_impl;
        for (int i=1; i<=10; i++) myvector_impl.push_back(i);
        while (!myvector_impl.empty()) {
            sum_impl += myvector_impl.back();
            myvector_impl.pop_back();
        } 
        REQUIRE(sum == sum_impl);
    }
    SECTION("reserve")
    {
        std::vector<int>::size_type sz;
        std::vector<int> foo;
        sz = foo.capacity();
        ft::Vector<int>::size_type sz_impl;
        ft::Vector<int> foo_impl;
        sz_impl = foo_impl.capacity();
        for (int i=0; i<100; ++i) {
            foo.push_back(i);
            foo_impl.push_back(i);
            if (sz!=foo.capacity()) {
                sz = foo.capacity();
                sz_impl = foo_impl.capacity();
                REQUIRE(sz == sz_impl);
            }
        }

        std::vector<int> bar;
        sz = bar.capacity();
        bar.reserve(100);   // this is the only difference with foo above
        ft::Vector<int> bar_impl;
        sz_impl = bar_impl.capacity();
        bar_impl.reserve(100);   // this is the only difference with foo above
        for (int i=0; i<100; ++i) {
            bar.push_back(i);
            bar_impl.push_back(i);
            if (sz!=bar.capacity()) {
                sz = bar.capacity();
                sz_impl = bar_impl.capacity();
                REQUIRE(sz == sz_impl);
            }
        }
    }
    SECTION("vector::operator[]")
    {
        std::vector<int> myvector (10);   // 10 zero-initialized elements
        std::vector<int>::size_type sz = myvector.size();
        // assign some values:
        for (unsigned i = 0; i < sz; i++) myvector[i] = i;
        // reverse vector using operator[]:
        for (unsigned i = 0; i < sz/2; i++)
        {
            int temp;
            temp = myvector[sz - 1 - i];
            myvector[sz - 1 - i] = myvector[i];
            myvector[i] = temp;
        }

        ft::Vector<int> myvector_impl (10);   // 10 zero-initialized elements
        ft::Vector<int>::size_type sz_impl = myvector_impl.size();
        // assign some values:
        for (unsigned i = 0; i < sz_impl; i++) myvector_impl[i] = i;
        // reverse vector using operator[]:
        for (unsigned i = 0; i < sz_impl/2; i++)
        {
            int temp;
            temp = myvector_impl[sz - 1 - i];
            myvector_impl[sz - 1 - i] = myvector_impl[i];
            myvector_impl[i] = temp;
        }
        for (unsigned i = 0; i < sz; i++)
            REQUIRE(myvector[i] == myvector_impl[i]);
    }
    SECTION("vector::at")
    {
        std::vector<int> myvector (10);   // 10 zero-initialized ints
        // assign some values:
        for (unsigned i=0; i<myvector.size(); i++)
            myvector.at(i)=i;

        ft::Vector<int> myvector_impl (10);   // 10 zero-initialized ints
        // assign some values:
        for (unsigned i=0; i<myvector_impl.size(); i++)
            myvector_impl.at(i)=i;

        for (unsigned i=0; i < myvector.size(); i++)
            REQUIRE(myvector.at(i) == myvector_impl.at(i));
    }
    SECTION("front")
    {
        std::vector<int> myvector;
        myvector.push_back(78);
        myvector.push_back(16);
        // now front equals 78, and back 16
        myvector.front() -= myvector.back();

        ft::Vector<int> myvector_impl;
        myvector_impl.push_back(78);
        myvector_impl.push_back(16);
        // now front equals 78, and back 16
        /* WARN(myvector_impl.front()); */
        /* WARN(myvector_impl.back()); */
        myvector_impl.front() -= myvector_impl.back();

        REQUIRE(myvector.front() == myvector_impl.front() );
    }
    SECTION("back")
    {
        std::vector<int> myvector;
        myvector.push_back(10);
        while (myvector.back() != 0)
            myvector.push_back ( myvector.back() -1 );

        ft::Vector<int> myvector_impl;
        myvector_impl.push_back(10);
        while (myvector_impl.back() != 0)
            myvector_impl.push_back ( myvector_impl.back() -1 );

        for (unsigned i=0; i<myvector.size() ; i++)
            REQUIRE(myvector[i] == myvector_impl[i]);
    }
    SECTION("assign")
    {
        std::vector<int> first;
        std::vector<int> second;
        std::vector<int> third;
        first.assign (7,100);             // 7 ints with a value of 100
        std::vector<int>::iterator it;
        it=first.begin()+1;
        second.assign (it,first.end()-1); // the 5 central values of first
        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);   // assigning from array.

        ft::Vector<int> first_impl;
        ft::Vector<int> second_impl;
        ft::Vector<int> third_impl;
        first_impl.assign (7,100);             // 7 ints with a value of 100
        ft::Vector<int>::iterator it_impl;
        it_impl = first_impl.begin() + 1;
        second_impl.assign(it_impl, first_impl.end() - 1); // the 5 central values of first_impl
        third_impl.assign(myints, myints + 3);   // assigning from array.

        REQUIRE( int(first.size()) == int(first_impl.size()) );
        REQUIRE( int(second.size()) == int(second_impl.size()) );
        REQUIRE( int(third.size()) == int(third_impl.size()) );
    }
    SECTION("push_back")
    {
        std::vector<int> myvector;
        ft::Vector<int> myvector_impl;
        for (unsigned int i = 0; i < 240; i++) {
            myvector.push_back(i);
            myvector_impl.push_back(i);
        }
        for (unsigned i=0; i<myvector.size() ; i++)
            REQUIRE(myvector[i] == myvector_impl[i]);
        REQUIRE(myvector.size() == myvector_impl.size());
    }
    SECTION("pop_back")
    {
        std::vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);
        while (!myvector.empty())
        {
            sum += myvector.back();
            myvector.pop_back();
        }

        ft::Vector<int> myvector_impl;
        int sum_impl (0);
        myvector_impl.push_back (100);
        myvector_impl.push_back (200);
        myvector_impl.push_back (300);
        while (!myvector_impl.empty())
        {
            sum_impl += myvector_impl.back();
            myvector_impl.pop_back();
        }
        REQUIRE(sum == sum_impl);
    }
    SECTION("insert")
    {
        std::vector<int> myvector (3,100);
        std::vector<int>::iterator it;
        it = myvector.begin();
        it = myvector.insert ( it , 200 );
        myvector.insert (it,2,300);
        // "it" no longer valid, get a new one:
        it = myvector.begin();
        std::vector<int> anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());
        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);

        ft::Vector<int> myvector_impl (3,100);
        ft::Vector<int>::iterator it_impl;
        it_impl = myvector_impl.begin();
        it_impl = myvector_impl.insert ( it_impl , 200 );
        myvector_impl.insert (it_impl, 2, 300);
        // "it" no longer valid, get a new one:
        it_impl = myvector_impl.begin();
        ft::Vector<int> anothervector_impl (2,400);
        myvector_impl.insert (it_impl+2,anothervector_impl.begin(),anothervector_impl.end());
        int myarray_impl [] = { 501,502,503 };
        myvector_impl.insert (myvector_impl.begin(), myarray_impl, myarray_impl + 3);

        for (it = myvector.begin(), it_impl = myvector_impl.begin(); 
                it < myvector.end(); ++it, ++it_impl)
        {
            REQUIRE(*it == *it_impl);
        }
    }
    SECTION("erase")
    {
        std::vector<int> myvector;
        ft::Vector<int> myvector_impl;
        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);
        for (int i=1; i<=10; i++) myvector_impl.push_back(i);
        // erase the 6th element
        myvector.erase (myvector.begin()+5);
        myvector_impl.erase (myvector_impl.begin()+5);
        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);
        myvector_impl.erase (myvector_impl.begin(),myvector_impl.begin()+3);

        for (unsigned i=0; i < myvector.size(); ++i)
        {
            REQUIRE(myvector[i] == myvector_impl[i]);
        }
    }
    SECTION("swap")
    {
        std::vector<int> foo (3,100);   // three ints with a value of 100
        std::vector<int> bar (5,200);   // five ints with a value of 200
        foo.swap(bar);

        ft::Vector<int> foo_impl (3,100);   // three ints with a value of 100
        ft::Vector<int> bar_impl (5,200);   // five ints with a value of 200
        foo_impl.swap(bar_impl);

        for (unsigned i=0; i<foo_impl.size(); i++)
            REQUIRE(foo[i] == foo_impl[i]);

        for (unsigned i=0; i<bar.size(); i++)
            REQUIRE(bar[i] == bar_impl[i]);
    }
    SECTION("clear")
    {
        std::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);
        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        ft::Vector<int> myvector_impl;
        myvector_impl.push_back (100);
        myvector_impl.push_back (200);
        myvector_impl.push_back (300);
        myvector_impl.clear();
        myvector_impl.push_back (1101);
        myvector_impl.push_back (2202);

        for (unsigned i=0; i<myvector.size(); i++)
            REQUIRE(myvector[i] == myvector_impl[i]);
    }
    SECTION("relational operators")
    {
        ft::Vector<int> foo_impl (3,100);   // three ints with a value of 100
        ft::Vector<int> bar_impl (2,200);   // two ints with a value of 200
        ft::Vector<int> cer_impl (2,200);   // two ints with a value of 200
        REQUIRE(bar_impl == cer_impl);
        REQUIRE_FALSE(cer_impl == foo_impl);
        REQUIRE(foo_impl < bar_impl);
        REQUIRE(foo_impl <= bar_impl);
        REQUIRE(bar_impl >= foo_impl);
        REQUIRE(bar_impl > foo_impl);
        REQUIRE(foo_impl != bar_impl);
    }
    SECTION("swap (vector)")
    {
        std::vector<int> foo (3,100);   // three ints with a value of 100
        std::vector<int> bar (5,200);   // five ints with a value of 200
        swap(foo, bar);

        ft::Vector<int> foo_impl (3,100);   // three ints with a value of 100
        ft::Vector<int> bar_impl (5,200);   // five ints with a value of 200
        swap(foo_impl, bar_impl);

        std::vector<int>::iterator it = foo.begin();
        ft::Vector<int>::iterator it_impl = foo_impl.begin();
        for (; it!=foo.end(); ++it,++it_impl)
            REQUIRE(*it == *it_impl);

        std::vector<int>::iterator itb = bar.begin();
        ft::Vector<int>::iterator itb_impl = bar_impl.begin();
        for (; itb!=bar.end(); ++itb,++itb_impl)
            REQUIRE(*itb == *itb_impl);
    }
}
bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};
TEST_CASE("Map", "[map]") {
    /* std::map<char,int> first; */
    /* first['a']=10; */
    /* first['b']=30; */
    /* first['c']=50; */
    /* first['d']=70; */
    /* ft::Map<char,int> first_impl; */
    /* first_impl['a']=10; */
    /* first_impl['b']=30; */
    /* first_impl['c']=50; */
    /* first_impl['d']=70; */
    /* SECTION("Constructors and operator[]") { */
    /*     std::map<char,int> second (first.begin(),first.end()); */
    /*     std::map<char,int> third (second); */
    /*     std::map<char,int,classcomp> fourth;                 // class as Compare */
    /*     bool(*fn_pt)(char,char) = fncomp; */
    /*     std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare */
    /*     ft::Map<char,int> second_impl (first.begin(),first.end()); */
    /*     ft::Map<char,int> third_impl (second); */
    /*     ft::Map<char,int,classcomp> fourth_impl;                 // class as Compare */
    /*     bool(*fn_pt)(char,char) = fncomp; */
    /*     ft::Map<char,int,bool(*)(char,char)> fifth_impl (fn_pt); // function pointer as Compare */
    /*     REQUIRE(first_impl['a'] == first['a']); */
    /*     REQUIRE(second_impl['c'] == second['c']); */
    /*     REQUIRE(third_impl['d'] == third['d']); */
    /*     REQUIRE(fourth_impl['b'] == fourth['b']); */
    /*     REQUIRE(fifth_impl['b'] == fifth['b']); */
    /* } */
    /* SECTION("size") { */
    /*     REQUIRE(first_impl.size() == 4); */
    /* } */
    /* SECTION("Operator =") { */
    /*     ft::Map<char,int> second_impl; */
    /*     second_impl = first_impl; */
    /*     first_impl = ft::Map<char,int>; */
    /*     REQUIRE(first_impl.size() == 0); */
    /*     REQUIRE(second_impl.size() == 4); */
    /*     REQUIRE(second_impl['c'] == 50); */
    /* } */
    /* SECTION("begin") { */
    /*     ft::Map<char,int>::iterator it = first_impl.begin(); */
    /*     REQUIRE(it->first == 'a'); */
    /*     REQUIRE(it->second == 10); */
    /*     ++it; */
    /*     REQUIRE(it->first == 'b'); */
    /*     REQUIRE(it->second == 30); */
    /*     --it; */
    /*     REQUIRE(it->first == 'a'); */
    /*     REQUIRE(it->second == 10); */
    /* } */
    /* SECTION("clear") { */
    /*     first_impl.clear(); */
    /*     first_impl['x'] = 1101; */
    /*     first_impl['y'] = 2202; */
    /*     REQUIRE(first_impl.size() == 2); */
    /*     ft::Map<char,int>::iterator it = first_impl.begin(); */
    /*     REQUIRE(it->first == 'x'); */
    /*     REQUIRE(it->second == 1101); */
    /* } */
    /* SECTION("count") { */
    /*     REQUIRE(first_impl.count('a') == 1); */
    /* } */
    /* SECTION("empty") { */
    /*     while (!first_impl.empty()) */
    /*         first_impl.erase(mymap.begin()); */
    /*     REQUIRE(first_impl.empty()); */
    /* } */
    /* SECTION("end") { */
    /*     ft::Map<char,int>::iterator it_impl = first_impl.end(); */
    /*     std::map<char,int>::iterator it = first.end(); */
    /*     --it; */
    /*     --it_impl; */
    /*     REQUIRE(it == it_impl); */
    /* } */
    /* SECTION("equal_range") { */
    /*     std::pair<ft::Map<char,int>::iterator,ft::Map<char,int>::iterator> ret; */
    /*     ret = first_impl.equal_range('b'); */ 
    /*     REQUIRE(ret.first->first == 'b'); */
    /*     REQUIRE(ret.first->second == 30); */
    /*     REQUIRE(ret.second->first == 'c'); */
    /*     REQUIRE(ret.second->second == '50'); */
    /* } */
    /* SECTION("find") { */
    /*     ft::Map<char,int>::iterator it_impl; */
    /*     it_impl = first_impl.find('b'); */
    /*     REQUIRE(it_impl->first == 'b'); */
    /*     REQUIRE(it_impl->second == 30); */
    /* } */
    /* SECTION("erase") { */
    /*     ft::Map<char,int>::iterator it_impl; */
    /*     first_impl['a']=10; */
    /*     first_impl['b']=20; */
    /*     first_impl['c']=30; */
    /*     first_impl['d']=40; */
    /*     first_impl['e']=50; */
    /*     first_impl['f']=60; */
    /*     it_impl = first_impl.find('b'); */
    /*     first_impl.erase(it_impl); */
    /*     REQUIRE(first_impl.size() == 5); */
    /*     first_impl.erase('c'); */
    /*     REQUIRE(first_impl.size() == 4); */
    /*     it_impl = first_impl.find('e'); */
    /*     first_impl.erase(it_impl, first_impl.end()); */
    /*     std::map<char,int>::iterator it; */
    /*     first['a']=10; */
    /*     first['b']=20; */
    /*     first['c']=30; */
    /*     first['d']=40; */
    /*     first['e']=50; */
    /*     first['f']=60; */
    /*     it = first.find('b'); */
    /*     first.erase(it_impl); */
    /*     first.erase('c'); */
    /*     it = first.find('e'); */
    /*     first.erase(it, first.end()); */
    /*     it = first.begin() */
    /*     it_impl = first_impl.begin() */
    /*     for(; it != first.end() && it_impl != first_impl.end(); ++it, ++it_impl) */
    /*         REQUIRE( it->first == it_impl->first); */
    /* } */
    /* SECTION("insert") { */
    /*     std::map<char,int> mymap; */
    /*     // first insert function version (single parameter): */
    /*     mymap.insert ( std::pair<char,int>('a',100) ); */
    /*     mymap.insert ( std::pair<char,int>('z',200) ); */
    /*     ft::Map<char,int> mymap_impl; */
    /*     mymap_impl.insert ( std::pair<char,int>('a',100) ); */
    /*     mymap_impl.insert ( std::pair<char,int>('z',200) ); */
    /*     std::pair<std::map<char,int>::iterator,bool> ret; */
    /*     ret = mymap_impl.insert ( std::pair<char,int>('z',500) ); */
    /*     REQUIRE (ret.second == false); */
    /*     // second insert function version (with hint position): */
    /*     std::map<char,int>::iterator it = mymap.begin(); */
    /*     mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting */
    /*     mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting */
    /*     ft::Map<char,int>::iterator it_impl = mymap_impl.begin(); */
    /*     mymap_impl.insert (it_impl, std::pair<char,int>('b',300));  // max efficiency inserting */
    /*     mymap_impl.insert (it_impl, std::pair<char,int>('c',400));  // no max efficiency inserting */
    /*     // third insert function version (range insertion): */
    /*     std::map<char,int> anothermap; */
    /*     ft::Map<char,int> anothermap_impl; */
    /*     anothermap.insert(mymap.begin(),mymap.find('c')); */
    /*     anothermap_impl.insert(mymap_impl.begin(),mymap_impl.find('c')); */
    /*     // showing contents: */
    /*     for (it=mymap.begin(), it_impl = mymap_impl.begin(); it!=mymap.end(); ++it, ++it_impl) */
    /*     { */
    /*         REQUIRE(it->first == it_impl->first); */
    /*         REQUIRE(it->second == it_impl->second); */
    /*     } */
    /*     for (it=anothermap.begin(), it_impl = anothermap_impl.begin(); it!=anothermap.end(); ++it, ++it_impl) */
    /*     { */
    /*         REQUIRE(it->first == it_impl->first); */
    /*         REQUIRE(it->second == it_impl->second); */
    /*     } */
    /* } */
    /* SECTION("rbegin & rend") { */
    /*     std::map<char,int>::reverse_iterator rit = first.rbegin(); */
    /*     ft::Map<char,int>::reverse_iterator rit_impl = first_impl.rbegin(); */
    /*     for(;rit != first.rend(); ++rit, ++rit_impl) */
    /*     { */
    /*         REQUIRE(rit->first == rit_impl->first); */
    /*         REQUIRE(rit->second == rit_impl->second); */
    /*     } */
    /* } */
    /* SECTION("key_comp") { */
    /*     std::map<char,int>::key_compare mycomp = first.key_comp(); */
    /*     ft::Map<char,int>::key_compare mycomp_impl = first_impl.key_comp(); */
    /*     char highest = first.rbegin()->first; */
    /*     char highest_impl = first_impl.rbegin()->first; */
    /*     REQUIRE(mycomp(it->first, highest) == mycomp_impl.(it_impl->first, highest_impl)); */
    /* } */
    /* SECTION("lower_bound") { */
    /*     ft::Map<char,int>::iterator itlow_impl,itup_impl; */
    /*     first_impl['a']=10; */
    /*     first_impl['b']=20; */
    /*     first_impl['c']=30; */
    /*     first_impl['d']=40; */
    /*     first_impl['e']=50; */
    /*     first_impl['f']=60; */
    /*     std::map<char,int>::iterator itlow, itup; */
    /*     first['a']=10; */
    /*     first['b']=20; */
    /*     first['c']=30; */
    /*     first['d']=40; */
    /*     first['e']=50; */
    /*     first['f']=60; */
    /*     itlow = first.lower_bound('b'); */
    /*     itup = first.upper_bound('d'); */
    /*     first.erase(itlow,itup); */
    /*     itlow_impl = first_impl.lower_bound('b'); */
    /*     itup_impl = first_impl.upper_bound('d'); */
    /*     first_impl.erase(itlow_impl,itup_impl); */
    /*     std::map<char,int>::iterator it = first.begin(); */
    /*     ft::Map<char,int>::iterator it_impl = first_impl.begin(); */
    /*     for(;rit != first.rend(); ++it, ++it_impl) */
    /*     { */
    /*         REQUIRE(rit->first == rit_impl->first); */
    /*         REQUIRE(rit->second == rit_impl->second); */
    /*     } */
    /* } */
    /* SECTION("max_size") { */
    /*     REQUIRE(first_impl.max_size > 0); */
    /* } */
    /* SECTION("swap") { */
    /*     ft::Map<char,int> second_impl; */
    /*     second_impl['x'] = 100; */
    /*     second_impl.swap(first); */
    /*     REQUIRE(second_impl['b'] == 30); */
    /*     REQUIRE(first_impl['x'] == 100); */
    /* } */
    /* SECTION("value_comp") { */
    /*     std::pair<char,int> highest = *first.rbegin(); */
    /*     std::pair<char,int> highest_impl = *first_impl.rbegin(); */
    /*     std::map<char,int>::iterator it = first.begin(); */
    /*     ft::Map<char,int>::iterator it_impl = first_impl.begin(); */
    /*     REQUIRE(first.value_comp()(*it, highest) == first_impl.value_comp()(*it_impl, highest_impl)); */
    /* } */
    /* SECTION("relational operators") */
    /* { */
    /*     ft::Map<char,int> second_impl; */
    /*     second_impl['a'] = 100; */
    /*     second_impl['z'] = 1000; */
    /*     REQUIRE_FALSE(first_impl == second_impl); */
    /*     REQUIRE(first_impl != second_impl); */
    /*     REQUIRE(first_impl < second_impl); */
    /*     REQUIRE(first_impl <= second_impl); */
    /*     REQUIRE_FALSE(first_impl > second_impl); */
    /*     REQUIRE_FALSE(first_impl >= second_impl); */
    /* } */
    /* SECTION("swap non-member overloads") { */
    /*     ft::Map<char,int> second_impl; */
    /*     second_impl['x'] = 100; */
    /*     swap(first, second_impl); */
    /*     REQUIRE(second_impl['b'] == 30); */
    /*     REQUIRE(first_impl['x'] == 100); */
    /* } */
}
