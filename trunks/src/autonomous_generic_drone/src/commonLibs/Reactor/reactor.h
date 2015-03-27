/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief: Clase que representa la capa reactiva del patron acceptor - connector. Implementada con variadic templates .
  *
  */
#ifndef REACTOR_H
#define REACTOR_H
#include <vector>
#include <thread>
#include <mutex>
namespace NSReactorLayer
{
  template<typename CommType, typename ServiceTargetInterface>
  class Reactor
  {
  public:
    Reactor():ThreadPtr(nullptr)
    ,isActive(false)
    ,ErrorCode(0)
    ,isServicesActive(false)
    {}
    void make_service_tuple(CommType * const aCommType, ServiceTargetInterface * const aServiceTargetInterface)
    {
      vector_reactor.emplace_back(std::make_tuple(aCommType,aServiceTargetInterface));
    }
    void initCommServices()
    {
      typedef std::tuple<CommType * const,ServiceTargetInterface * const> service_com_tuple;
      for(service_com_tuple aTuple : vector_reactor)
        {
          std::get<comm_type>(aTuple)->inicializarcomunicacion();
          isServicesActive=true;
        }

    }
    void init()
    {
      if(ThreadPtr==nullptr && isServicesActive)
        {
          ThreadPtr=new std::thread(&Reactor::run,this);
        }
    }

    void stop()
    {
      std::lock_guard<std::mutex> lock(mutex);
      isActive=false;
    }

    private:
    enum serivice
    {
      comm_type,
      service
    };
    void run()
    {
      while(isActive)
        {
          for(auto iterator = vector_reactor.begin();iterator!=vector_reactor.end();iterator++)
            {
              Buffer.clear();
              std::get<comm_type>(iterator)->leer(Buffer,ErrorCode);
              if(ErrorCode==0)
                {
                  mutex.lock();
                  //Recorda mandar una copia
                  std::get<service>(iterator)->setRawMsg(Buffer);
                  mutex.unlock();
                }
            }
        }
    }
    std::vector<std::tuple<CommType * const,ServiceTargetInterface * const>> vector_reactor;
    std::thread * ThreadPtr;
    volatile bool isActive;
    std::mutex mutex;
    std::string Buffer;
    volatile int ErrorCode;
    bool isServicesActive;
  };
}
#endif // REACTOR_H
