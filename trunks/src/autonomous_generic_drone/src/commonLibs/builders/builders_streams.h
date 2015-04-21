/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 23-03-2015
  *@brief: Archivo de clases utiles para la administracion de archivos en linux
  *
  *
  */
#ifndef BUILDERS_STREAMS_H
#define BUILDERS_STREAMS_H
#include <unordered_map>
#include <iostream>
#include <glog/logging.h>
#include "../utils_generics/xml_reader.h"
#include "../utils_generics/generis_strutures.h"
#include "builders_traits.h"
#include "builder_options.h"
#include "../comunicacion/icomm.h"
#include "../comunicacion/UDPComm.h"
#include "../comunicacion/tcpcommunication.h"
#include "../utils_generics/generis_strutures.h"
struct key
{
   std::string ProxyID;
   std::string ProxyDescription;
   std::string stream_type;
   std::string data_type;
   std::string MsgType;
   bool isValidKey() const
   {
       return (!(ProxyID.empty() &&
               stream_type.empty() &&
               data_type.empty()   &&
               ProxyDescription.empty() &&
               MsgType.empty()
               ));
   }
   void clear()
   {
     ProxyID.clear();
     ProxyDescription.clear();
     stream_type.clear();
     data_type.clear();
     MsgType.clear();

   }

   bool findByName(const std::string & aProxyDescription,
                   const std::string & aStreamType,
                   const std::string & aDataType/*command event telemetry*/
                   ) const
   {
      return (ProxyDescription==aProxyDescription &&
              stream_type==aStreamType &&
              aDataType==data_type
              );
   }
   bool operator==(const key &other) const
    {
       return (ProxyID == other.ProxyID
              && stream_type == other.stream_type
              && data_type == other.data_type
              && ProxyDescription == other.ProxyDescription
              && MsgType == other.MsgType
               );
    }
};

namespace std {
  template <>
  struct hash<key>
  {
    std::size_t operator()(const key& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      return ((hash<string>()(k.ProxyID)
               ^ (hash<string>()(k.stream_type) << 1)) >> 1)
               ^ (hash<string>()(k.data_type) << 1)
               ^ (hash<string>()(k.ProxyDescription) << 1)
               ^ (hash<string>()(k.MsgType) << 1)

              ;
    }
  };
}

namespace NSBuilders
{
    template<class ...Args>
    class Builders<NSCommonsLibs::BuilderType::StreamType,Args...> : public IBuilderInterface
    {
        typedef NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType> BuilderOption;
    public:
         Builders(const std::string & aFileName):BuilderOptions(aFileName.c_str())
                                                 ,xmlReader(&BuilderOptions)
                                                 ,ErrorCode(0)
         {
           LOG(INFO)<<"Builder Stream: "<<aFileName<<std::endl;
             xmlReader.buildAll(ErrorCode);
             LOG(INFO)<<"XML READER ErrorCode: "<<ErrorCode<<std::endl;
         }
         int getErrorCode() const
         {
                return ErrorCode;
         }

         void buildAll(int & aErrorCode)
         {
           aErrorCode=ErrorCode;
           if(ErrorCode==0)
             {
               for(auto i=0;i<BuilderOptions.SubNodeVector.size();i++)
                 {
                   aErrorCode=-1;
                   for(auto j=0;j<BuilderOptions.SubNodeVector.at(i).InnerNodeVector.size();j++)
                     {
                       key aKeyValue;
                       aKeyValue.ProxyID=BuilderOptions.SubNodeVector.at(i).getProxyId();
                       aKeyValue.ProxyDescription=BuilderOptions.SubNodeVector.at(i).getProxyDescription();
                       aKeyValue.data_type=BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getDataType();
                       aKeyValue.stream_type=BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getStreamType();
                       aKeyValue.MsgType=BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getMsgType();

                       if(aKeyValue.isValidKey())
                         {
                           const auto aPtr=getComm(BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getCommType());
                           if(aPtr!=nullptr)
                             {
                               configurateComm(aPtr,BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j));
                               comm_map.insert(std::make_pair(aKeyValue,aPtr));
                               aErrorCode=0;
                             }
                         }
                     }
                 }
             }
         }

         COMUNICACION::IComm * getComInterface(const std::string & ProxyName, const std::string & StreamType, const std::string & DataType)
         {
           LOG(INFO)<<"STREAM BUILDERS getComInterface (Tamaño del mapa: )"<<comm_map.size();

           COMUNICACION::IComm * aComPtr=nullptr;
           for(auto iterator=comm_map.begin();iterator!=comm_map.end();iterator++)
             {
               if((iterator->first).findByName(ProxyName,StreamType,DataType))
                 {

                   aComPtr=iterator->second;
                   break;
                 }
             }
            return aComPtr;
         }
         /**
          * @brief getComMapOption
          * @return mapa completo de las opciones de interfaces
          */
         std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> getComMapOption()
         {
            return comm_map;
         }
    private:
         COMUNICACION::IComm * getComm(const std::string & aCommType) const
         {
             COMUNICACION::IComm * aPtr=nullptr;

             if (aCommType.compare("UDP")==0) aPtr=new COMUNICACION::UDPComm<std::string>;

             if (aCommType.compare("TCP")==0) aPtr=new COMUNICACION::TCPCOMM<std::string>;

             return aPtr;
         }
         template<typename options>
         void configurateComm(COMUNICACION::IComm * const aCommInterface, const options & aOptions)
         {
          //si es server

           if(aOptions.getCommType()=="UDP")
             {
               aCommInterface->setLocalPort(aOptions.getLocalPort());
             }
           aCommInterface->setPort(aOptions.getPort());
           if(aOptions.getStreamType()=="out")//client
           {
             aCommInterface->setDestino(aOptions.getTargetIp());
           }
         }

        NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType>  BuilderOptions;
         NSUtils::BuilderInterfaceBase<NSCommonsLibs::BuilderType::StreamType ,BuilderOption > xmlReader;
         int ErrorCode;
         std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> comm_map;
         //std::unorderer_map<key,COMUNICACION::IComm *> comm_map;
    };
    typedef Builders<NSCommonsLibs::BuilderType::StreamType> StreamBuilderType;
}
#endif // BUILDERS_STREAMS_H
