#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include "TestDynamic.cpp"

int main()
{
    CPPUNIT_NS::TestResult tr;
    CPPUNIT_NS::TestResultCollector trc;
    tr.addListener(&trc);
    
    CPPUNIT_NS::BriefTestProgressListener progress;
    tr.addListener(&progress);
    
    CPPUNIT_NS::TestRunner runner;
    CPPUNIT_NS::TestFactoryRegistry &reg = CppUnit::TestFactoryRegistry::getRegistry("TestDynamic");
    runner.addTest(reg.makeTest());
    runner.run(tr);
    
    CPPUNIT_NS::CompilerOutputter outputter(&trc, CPPUNIT_NS::stdCOut());
    outputter.write();
}
