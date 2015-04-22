/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef REACTOR_H
#define REACTOR_H
#include <vector>
#include <tuple>
#include <thread>
#include <mutex>
#include <glog/logging.h>
#include <iostream>
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
    {
      LOG(INFO)<<"Constructor Reactor";

    }
    void make_service_tuple(CommType * const aCommType, ServiceTargetInterface * const aServiceTargetInterface)
    {


      if(aCommType!=nullptr && aServiceTargetInterface!=nullptr)
        {
          LOG(INFO)<<"Creando Tuple";
        const auto aTuple=std::make_tuple(nullptr,nullptr);//std::make_tuple(aCommType,aServiceTargetInterface);
        vector_reactor.emplace_back(aTuple);
        LOG(INFO)<<"Vector Size: "<<vector_reactor.size();

        }
    }
    void initCommServices()
    {
      typedef std::tuple<CommType * const,ServiceTargetInterface * const> service_com_tuple;
      for(service_com_tuple aTuple : vector_reactor)
        {
          std::get<comm_type>(aTuple)->inicializarServer(ErrorCode);
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
      comm_type = 0,
      service
    };
    void run()
    {
      while(isActive)
        {
          for(auto iterator = vector_reactor.begin();iterator!=vector_reactor.end();iterator++)
            {
              Buffer.clear();
              std::get<static_cast<int>(comm_type)>(*iterator)->leer(Buffer,ErrorCode);
              if(ErrorCode==0)
                {
                  mutex.lock();
                  //Recorda mandar una copia
                  std::get<service>(*iterator)->setRawMsg(Buffer);
                  mutex.unlock();
                }
            }
        }
    }
    std::vector<std::tuple<CommType * const,ServiceTargetInterface * const> > vector_reactor;

    std::thread * ThreadPtr;
    volatile bool isActive;
    std::mutex mutex;
    std::string Buffer;
     int ErrorCode;
    bool isServicesActive;
  };
}
#endif // REACTOR_H
