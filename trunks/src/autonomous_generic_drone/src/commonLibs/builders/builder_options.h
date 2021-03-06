#ifndef BUILDER_OPTIONS_H
#define BUILDER_OPTIONS_H
#include <tuple>
#include "builders_traits.h"
#include "definitions.h"
#include <vector>
#include <iostream>
#include <algorithm>
namespace  NSBuilders
{
namespace
{
    static const std::string LOCAL_HOST("localhost");
}
template<>
struct BuildersOptions<NSCommonsLibs::BuilderType::StreamType>
{
    BuildersOptions(const char * const aFileName):FILE_NAME(aFileName)
                    , NODE_NAME(std::make_tuple("NODE_NAME","CONFIGMODULES"))
                    ,SUB_NODE_NAME(std::make_tuple("SUB_NODES","Modules"))
   {}
    //Representa Row
        struct SubNode
        {
            struct Options
            {
                typedef std::tuple<std::string,std::string,std::string> INNER_NODE_OPTIONS;
                 Options():SUB_NODE_OPTIONS(std::make_tuple("SUB_NODE_OPTIONS","Option"))
                   ,inner_node_vector{              std::make_tuple("OPTION_TAG_STREAM_TYPE","stream_type","")
                                                    ,std::make_tuple("OPTION_TAG_DATA_TYPE","data_type","")
                                                    ,std::make_tuple("OPTION_TAG_CONNECTION_TYPE","connection_type","")
                                                    ,std::make_tuple("OPTION_TAG_IP","ip","")
                                                    ,std::make_tuple("OPTION_TAG_PORT","port","")
                                                    ,std::make_tuple("OPTION_TAG_LOCALPORT","localport","")
                                                    ,std::make_tuple("OPTION_TAG_MSG_TYPE","msg_type","")
                                                     }
                 {}
                 enum SubNodeIndex
                 {
                     Row_Tag,
                     Row_name,
                     Row_value
                 };
                 enum OPTION_TAG_INDEX
                 {
                   OPTION_TAG_STREAM_TYPE_INDEX=0,
                   OPTION_TAG_MSG_TYPE_INDEX=6
                 };
                 void cleanInnerOptions()
                 {
                     for(auto & field : inner_node_vector)
                     {
                             std::get<Row_value>(field)="";
                     }
                 }

                 void print()
                 {
                     std::cout << "sub_node NAME:"<<std::get<0>(SUB_NODE_OPTIONS) <<" "<<std::get<1>(SUB_NODE_OPTIONS) <<"  cantidad de subnodos: "<<inner_node_vector.size()
                               << "\n " ;
                     for(auto i=0;i<inner_node_vector.size();i++)
                     {
                         std::cout<<"|_ "<<std::get<1>(inner_node_vector.at(i))<<" --> "<<std::get<2>(inner_node_vector.at(i))<<"\n " ;
                     }
                 }
                 //TODO: agregar enumerado para identificar los campos
                 std::string getStreamType() const
                 {
                    return std::get<2>(inner_node_vector.at(0));
                 }
                 std::string getDataType() const
                 {
                     return std::get<2>(inner_node_vector.at(1));
                 }
                 std::string getCommType() const
                 {
                     return std::get<2>(inner_node_vector.at(2));
                 }
                 std::string getPort() const
                 {
                       return std::get<2>(inner_node_vector.at(4));
                 }
                 std::string getLocalhost() const
                 {
                    return LOCAL_HOST;
                 }

                 std::string getTargetIp() const
                 {
                      return std::get<2>(inner_node_vector.at(3));
                 }
                 std::string getLocalPort() const
                 {
                        return std::get<2>(inner_node_vector.at(5));
                 }
                 std::string getMsgType() const
                 {
                   return std::get<Row_value>(inner_node_vector.at(OPTION_TAG_MSG_TYPE_INDEX));

                 }
                std::tuple<const std::string,const std::string> SUB_NODE_OPTIONS;
                std::vector<INNER_NODE_OPTIONS> inner_node_vector;
            };//Fin Options
                typedef std::tuple<std::string,std::string,std::string> ROW_OPTIONS;
                SubNode():optionsVector{std::make_tuple("MODULE_TAG_NAME","name","")
                                                            ,std::make_tuple("MODULE_TAG_ID","id","")
                                                            ,std::make_tuple("MODULE_TAG_ID_VALUE","id_value","")
                                                            ,std::make_tuple("MODULE_TAG_TYPE","type","")
                                                        }

             {}
                bool isSameID(const std::string & aID)
                {
                    std::cout<<"aID: "<<aID<<" SUBNODE ID: "<<std::get<2>(optionsVector.at(1))<<std::endl;
                    return (aID==std::get<2>(optionsVector.at(1)));
                }

                void cleanValuesFields()
                {
                    for(auto & field : optionsVector)
                    {
                            std::get<Row_value>(field)="";
                    }
                }
            enum SubNodeIndex
            {
                Row_Tag,
                Row_name,
                Row_value
            };
            std::string getRowTitles() const
            {
                return std::get<2>(optionsVector.at(1));//nombre literal del proxy
            }
            /**
             * @brief getProxyDescription Obtiene el nombre del proxy
             * @return
             */
            std::string getProxyDescription() const
            {
                return std::get<2>(optionsVector.at(1));//nombre literal del proxy
            }
            /**
             * @brief getProxyId funcion que devuelve el ID del proxy que se quiere modelar
             * @return id en string del proxy que se quiere modelar
             */
            std::string getProxyId() const
            {
              return std::get<2>(optionsVector.at(2));
            }
            void print()
            {
                std::cout<<"[SUBNODE]"<<std::endl;
                for(auto i=0;i<optionsVector.size();i++)
                {
                    std::cout<<"["<<std::get<1>(optionsVector.at(i))<<"===>> "<<std::get<2>(optionsVector.at(i))<<"] ";
                }
                //SubNodeOptions
                std::cout<<"\n";
                for(auto i=0;i<InnerNodeVector.size();i++) InnerNodeVector.at(i).print();

            }
            Options InnerNodeOption;
            std::vector<Options> InnerNodeVector;
             std::vector<ROW_OPTIONS> optionsVector;
        };//termina SubNode


        void print()
        {

            std::cout<<std::get<0>(NODE_NAME)<<" "<<std::get<1>(NODE_NAME)<<" "<<std::get<0>(SUB_NODE_NAME)<<" "<<std::get<1>(SUB_NODE_NAME)<<"\n";
            std::cout<<"[Node] cantidad de subNodos: "<< SubNodeVector.size()<<std::endl;
            for(auto i=0;i<SubNodeVector.size();i++)  SubNodeVector.at(i).print();
        }
        SubNode * getSubnode(const std::string & aNodeName)
        {
            SubNode * aPtr=nullptr;
            for(auto i= 0;i<SubNodeVector.size();i++)
            {
                if (SubNodeVector.at(i).isSameID(aNodeName))
                     {
                            aPtr=&SubNodeVector.at(i);
                            break;
                      }
            }
            return aPtr;
        }
      void getSubNode(const std::string & aNodeName,SubNode * aNodeVector)
      {
          aNodeVector=nullptr;
                for(auto i= 0;i<SubNodeVector.size();i++)
                {
                    if (SubNodeVector.at(i).isSameID(aNodeName))
                         {
                                aNodeVector=&SubNodeVector.at(i);
                                break;
                          }
                }

      }

    //Nodes
       const std::string FILE_NAME;
       const std::tuple<const std::string, const std::string > NODE_NAME;
        const std::tuple<const std::string, const std::string > SUB_NODE_NAME;
        std::vector<SubNode> SubNodeVector;
        SubNode Sub_Node_Row;

        //Options


};
typedef BuildersOptions<NSCommonsLibs::BuilderType::StreamType> BUILDER_STREAM_OPTIONS;
}
#endif // BUILDER_OPTIONS_H

