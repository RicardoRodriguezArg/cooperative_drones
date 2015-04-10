#ifndef CMD_STATE_UNIT_TEST_H
#define CMD_STATE_UNIT_TEST_H

namespace NSTests
{
  namespace Variables_Setup
  {
    static bool ActionInterface_chechCondition=true;
  }
  class StateInfo{};

 class CmdStateModel
 {
  public:
    void verifyCmdContext(StateInfo * const aRowStateInfo, bool &)
    {}
 };

class ActionInterface
{
public:
  void setInitcondition(bool & chechCondition)
  {
    chechCondition=Variables_Setup::ActionInterface_chechCondition;
  }
  void execute(bool & aResult)
  {}
  StateInfo * getStateInfo()
 {
    return  &aStateInfoRow;
  }

  StateInfo aStateInfoRow;
};


struct Options{};

}
#endif // CMD_STATE_UNIT_TEST_H
