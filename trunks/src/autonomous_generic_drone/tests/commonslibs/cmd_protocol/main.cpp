
#include "gtest/gtest.h"
#include "cmd_state_aux.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/cmd_protocol/cmd_state_unit.h"
namespace {

    constexpr unsigned TEST_TIMEOUT_VALUE=100U;

  class CmdStateUnitTest :public ::testing::Test
  {
  protected:
    CmdStateUnitTest():CmdStateUnit(&CmdStateModel,&ActionInterface,TEST_TIMEOUT_VALUE)
    {}
    virtual void SetUp()
    {
      /**
        *Aca se setea el estado
        */
    //  CmdStateUnit.
    }
    virtual ~CmdStateUnitTest()
    {}
    virtual void TearDown() {
       // Code here will be called immediately after each test (right
       // before the destructor).
     }

    NSTests::CmdStateModel CmdStateModel;
    NSTests::ActionInterface ActionInterface;
    NSProtocol::CmdState<NSTests::CmdStateModel,NSTests::ActionInterface,NSTests::StateInfo> CmdStateUnit;
  };
}

TEST_F(CmdStateUnitTest,TestInicializarEstado)
{
  NSTests::Variables_Setup::ActionInterface_chechCondition=false;
  CmdStateUnit.init();
  EXPECT_EQ(false,CmdStateUnit.isStateRunning());
}


int main(int argc, char **argv)
{

  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();



 return 0;
}
