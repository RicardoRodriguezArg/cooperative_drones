#ifndef XML_READER_H
#define XML_READER_H
#include "tinyxml2.h"
#include <string>
#include <iostream>
#include "definitions.h"

namespace NSUtils {
template<NSCommonsLibs::BuilderType,class OptionStructure>
class BuilderInterfaceBase{};
/**
 * @brief The BuilderInterfaceBase class clase generica para la lectura de archivos xml usando TinyXml2
 */
template<class OptionStructure>
class BuilderInterfaceBase<NSCommonsLibs::BuilderType::StreamType,OptionStructure>
{
public:
    BuilderInterfaceBase(OptionStructure * const aOptionStructurePtr
                          ):OptionStructurePtr(aOptionStructurePtr)
                            ,BaseNodePtr(nullptr)
                            ,NodePtr(nullptr)
                             ,mXmlError(tinyxml2::XML_NO_ERROR)
    {
        if(OptionStructurePtr!=nullptr)
        {

            mXmlError=mXmlDoc.LoadFile(OptionStructurePtr->FILE_NAME.c_str());
            std::cout<<"ERROR XML: "<<mXmlError<<std::endl;
        }
    }

    virtual void buildAll(int & aErrorCode)
    {

        aErrorCode=static_cast<int>(mXmlError);

        if(isPossibleToProcess())
        {
           std::cout<<"Leyendo primer opcion archivo: "<<std::get<Value>(OptionStructurePtr->NODE_NAME)<<std::endl;
            BaseNodePtr=mXmlDoc.FirstChildElement(std::get<Value>(OptionStructurePtr->NODE_NAME).c_str());
            //nodo raiz
            processNodeInfo(aErrorCode);
        }

    }


protected:
    bool isPossibleToProcess() const
    {
        const bool result=(static_cast<int>(mXmlError)==tinyxml2::XML_SUCCESS)
                                        && (mXmlDoc.FirstChildElement(std::get<Value>(OptionStructurePtr->NODE_NAME).c_str())!=nullptr
                                        );
        return result;
    }
    //extrae info de la linea del nodo
    void processNodeInfo(int & aErrorCode)
    {

        //Options
          auto RowPtr=BaseNodePtr->FirstChildElement(std::get<Value>(OptionStructurePtr->SUB_NODE_NAME).c_str());
          std::cout<<"leyendo las SUB NODE: "<<std::get<Value>(OptionStructurePtr->SUB_NODE_NAME)<<std::endl;
          aErrorCode=(RowPtr==nullptr)?-2:0;

          if(aErrorCode==0)
          {
             extractSubNodeRowInfo(RowPtr);
           }

    }
    void extractSubNodeRowInfo(tinyxml2::XMLElement  * const aRowOptionPtr)
    {
       auto Ptr=aRowOptionPtr;
            do{
                OptionStructurePtr->Sub_Node_Row.cleanValuesFields();
                std::cout<<"cantidad de opciones: "<<(OptionStructurePtr->SubNodeVector).size()<<std::endl;
                for(auto i=0;i<OptionStructurePtr->Sub_Node_Row.optionsVector.size();i++)
                {
                    std::cout<<"valor de fabrica:(row tag) "<<std::get<0>(OptionStructurePtr->Sub_Node_Row.optionsVector.at(i))<<std::endl;
                    std::cout<<"valor de fabrica (row name): "<<std::get<1>(OptionStructurePtr->Sub_Node_Row.optionsVector.at(i))<<std::endl;
                    const auto attributeName=std::get<1>(OptionStructurePtr->Sub_Node_Row.optionsVector.at(i));
                    if(Ptr->Attribute(attributeName.c_str())!=nullptr)
                    {
                        std::get<2>(OptionStructurePtr->Sub_Node_Row.optionsVector.at(i))=Ptr->Attribute(attributeName.c_str());
                        std::cout<<"valor obtenido (row value): "<<std::get<2>(OptionStructurePtr->Sub_Node_Row.optionsVector.at(i))<<std::endl;
                    }
                }

             extractSubNodeOptions(Ptr);
             (OptionStructurePtr->SubNodeVector).emplace_back(OptionStructurePtr->Sub_Node_Row);
              std::cout<<"==========================="<<std::endl<<std::endl;
        }
       while((Ptr=Ptr->NextSiblingElement())!=nullptr);

    }

    void extractSubNodeOptions(tinyxml2::XMLElement  *  const aRowOptionPtr)
    {
        auto aSubNodePtr=aRowOptionPtr->FirstChildElement(std::get<1>(OptionStructurePtr->Sub_Node_Row.InnerNodeOption.SUB_NODE_OPTIONS).c_str());
        do
        {
            for(auto i=0; i<OptionStructurePtr->Sub_Node_Row.InnerNodeOption .inner_node_vector.size();i++)
            {

            std::cout<<"Factory Sub Node Tag Name: "<<std::get<1>(OptionStructurePtr->Sub_Node_Row.InnerNodeOption.inner_node_vector.at(i))<<std::endl;
            const auto attribute_from_factory=std::get<1>(OptionStructurePtr->Sub_Node_Row.InnerNodeOption.inner_node_vector.at(i));
            aSubNodePtr->Attribute(attribute_from_factory.c_str());
            if(aSubNodePtr->Attribute(attribute_from_factory.c_str())!=nullptr)
            {
                std::get<2>(OptionStructurePtr->Sub_Node_Row.InnerNodeOption.inner_node_vector.at(i))=aSubNodePtr->Attribute(attribute_from_factory.c_str());
                 std::cout<<"SubNode Value From XMl: "<<std::get<2>(OptionStructurePtr->Sub_Node_Row.InnerNodeOption.inner_node_vector.at(i))<<std::endl;
            }

            }
            OptionStructurePtr->Sub_Node_Row.InnerNodeVector.emplace_back(OptionStructurePtr->Sub_Node_Row.InnerNodeOption);
            OptionStructurePtr->Sub_Node_Row.InnerNodeOption.cleanInnerOptions();
        }
        while ((aSubNodePtr=aSubNodePtr->NextSiblingElement())!=nullptr);
    }

    enum OptionsIndex
    {
        Name,
        Value
    };
    const std::string RowTag;

    tinyxml2::XMLDocument mXmlDoc;
    tinyxml2::XMLError mXmlError;
    tinyxml2::XMLElement  * BaseNodePtr;
    tinyxml2::XMLElement * NodePtr;
   OptionStructure * const OptionStructurePtr;
};
}
#endif // XML_READER_H
