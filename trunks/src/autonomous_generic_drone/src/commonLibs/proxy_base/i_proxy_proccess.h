/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef I_PROXY_PROCCESS_H
#define I_PROXY_PROCCESS_H
namespace NSProxy
{
  template<class Proxy>
  class IProxyProcess
  {
    public:
      virtual ~IProxyProcess(){}
      virtual void setProxy(Proxy * const )=0;
      virtual void setState(const int &)=0;
      virtual void runAsyncProcess() = 0;
      virtual void getAssyncProcessCodeError(int &)=0;
      virtual void stopProcess() = 0;
  };
}
#endif // I_PROXY_PROCCESS_H
