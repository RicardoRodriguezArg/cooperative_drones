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
   std::string stream_type;
   std::string data_type;
   bool isValidKey() const
   {
       return (!(ProxyID.empty() &&
               stream_type.empty() &&
               data_type.empty()
               ));
   }
   bool operator==(const key &other) const
    {
       return (ProxyID == other.ProxyID
              && stream_type == other.stream_type
              && data_type == other.data_type);
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
               ^ (hash<string>()(k.data_type) << 1);
    }
  };
}

namespace NSBuilders
{


    template<>
    class Builders<NSCommonsLibs::BuilderType::StreamType>
    {
        typedef NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType> BuilderOption;
    public:
         Builders(const std::string & aFileName):BuilderOptions(aFileName.c_str())
                                                 ,xmlReader(&BuilderOptions)
                                                 ,ErrorCode(0)
         {
             xmlReader.buildAll(ErrorCode);
             std::cout<<"ErrorCode: "<<ErrorCode<<std::endl;
         }
         int getErrorCode() const
         {
                return ErrorCode;
         }
         void buildAll(int & aErrorCode)
         {
             for(auto i=0;i<BuilderOptions.SubNodeVector.size();i++)
             {
                      for(auto j=0;j<BuilderOptions.SubNodeVector.at(i).InnerNodeVector.size();j++)
                      {
                          key aKeyValue;
                          aKeyValue.ProxyID=BuilderOptions.SubNodeVector.at(i).getRowTitles();
                          std::cout<<"ProxyId: "<<BuilderOptions.SubNodeVector.at(i).getRowTitles()<<std::endl;
                          std::cout<<"StreamType: "<<BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getStremType()<<std::endl;
                          std::cout<<"Data Type: "<<BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getDataType()<<std::endl;
                          aKeyValue.data_type=BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getDataType();
                          aKeyValue.stream_type=BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getStremType();
                          if(aKeyValue.isValidKey())
                          {
                              comm_map.insert(std::make_pair(aKeyValue,getComm(BuilderOptions.SubNodeVector.at(i).InnerNodeVector.at(j).getCommType())));
                          }
                      }
             }


         }
         COMUNICACION::IComm * getComm(const std::string & aCommType) const
         {
             COMUNICACION::IComm * aPtr=nullptr;

             if (aCommType.compare("UDP")==0) aPtr=new COMUNICACION::UDPComm<NSUtils::MsgData>;

             if (aCommType.compare("TCP")==0) aPtr=new COMUNICACION::TCPCOMM<NSUtils::MsgData>;
             return aPtr;
         }

    private:

        NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType>  BuilderOptions;
         NSUtils::BuilderInterfaceBase<NSCommonsLibs::BuilderType::StreamType ,BuilderOption > xmlReader;
         int ErrorCode;
         std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> comm_map;
         //std::unorderer_map<key,COMUNICACION::IComm *> comm_map;
    };
}
#endif // BUILDERS_STREAMS_H