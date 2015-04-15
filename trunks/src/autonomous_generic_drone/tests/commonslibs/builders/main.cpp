/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#include "gtest/gtest.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/builders_proxy.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/builders/builder_proxy_info.h"
#include "builder_aux.h"
namespace {

namespace
        {
         typedef NSTest::ProxyBuilder::BuilderUitlsOption<NSTest::ProxyBuilder::KeyType,NSTest::ProxyBuilder::ICom> BuilderOptions;
         template<class key_type>
         using InputStructureType=std::vector<key_type>;
          static BuilderOptions Options;
          static BuilderOptions * const OptionPtr = nullptr;
          static InputStructureType<NSTest::ProxyBuilder::KeyType> InputDataStructure;
          static InputStructureType<NSTest::ProxyBuilder::KeyType> * InputDataStructurePtr=nullptr;
        }

  class BuilderProxyTest :public ::testing::Test
  {
  protected:
    BuilderProxyTest()//:ProxyBuilder(InputDataStructurePtr)
    {}
    virtual void SetUp()
    {
      /**
        *Aca se setea el estado
        */
    //  CmdStateUnit.
    }
    virtual ~BuilderProxyTest()
    {}
    virtual void TearDown() {
       // Code here will be called immediately after each test (right
       // before the destructor).
     }


    typedef std::unordered_map<std::string,NSBuilders::ProxyInfo> OutputStructure;

   // NSBuilders::Builders<NSCommonsLibs::BuilderType::ProxyType,InputStructureType<NSTest::ProxyBuilder::KeyType>,OutputStructure> ProxyBuilder;
  };
}

TEST_F(BuilderProxyTest,TestInicializarBuilder_Puntero_vacio)
{
  int aErrorCode=0;
//  ProxyBuilder.buildAll(aErrorCode);
  EXPECT_EQ(aErrorCode,std::get<1>(NSCommonsLibs::ERROR_CODES::BUILDER_PROXY_ERROR));
}
TEST_F(BuilderProxyTest,TestInicializarBuilder)
{
  int aErrorCode=0;
  //ProxyBuilder.buildAll(aErrorCode);
  EXPECT_EQ(aErrorCode,std::get<1>(NSCommonsLibs::ERROR_CODES::BUILDER_PROXY_ERROR));
}

int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();



 return 0;
}
