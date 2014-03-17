#include <stlport/list>
#include <stlport/vector>
#include <stlport/string>

using namespace std;

struct S :
    public string
{
};

void test()
{
  list<S> l;
  l.push_back( S() );

  vector<S> v;
  v.push_back( S() );
}

