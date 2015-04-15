#include "gtest/gtest.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/builders_proxy.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/builder_proxy_info.h"

#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/utils_builder.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/builders_streams.h"

class StructureTransformTest :public ::testing::Test
{
protected:
  StructureTransformTest()
  {}
  typedef std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> InputStructure;
  typedef std::unordered_map<std::string,NSBuilders::ProxyInfo> OutputStructure;
};

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();



 return 0;
}

