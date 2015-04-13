/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef CMD_STATE_TEST_H
#define CMD_STATE_TEST_H
#include "gtest/gtest.h"
#include "cmd_state_aux.h"
#include "../../../../src/autonomous_generic_drone/src/commonLibs/cmd_protocol/cmd_state_unit.h"
namespace NSTests
{
  namespace
  {
    constexpr unsigned TEST_TIMEOUT_VALUE=100U;
  }
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
    NSTests::CmdStateModel CmdStateModel;
    NSTests::ActionInterface ActionInterface;
    NSProtocol::CmdState<NSTests::CmdStateModel,NSTests::ActionInterface,NSTests::StateInfo> CmdStateUnit;
  };
}
#endif // CMD_STATE_TEST_H
