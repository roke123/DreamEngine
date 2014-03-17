#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h> 
  
int main()
{
	CppUnit::TextTestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run(); 

	system("pause");

    return 0;
} 