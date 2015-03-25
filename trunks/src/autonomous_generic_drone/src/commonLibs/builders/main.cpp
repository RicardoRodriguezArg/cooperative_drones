#include "builder_options.h"
#include "../utils_generics/xml_reader.h"
#include "builders_streams.h"
int main()
{
    std::string aName;
      int aErrorCode=0;
/*
    NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType>  aBuilderOptions("/home/ricardo/Desktop/proyecto/cooperative_drones/trunks/src/autonomous_generic_drone/config/config/generaloptionconfig.xml");
    typedef NSBuilders::BuildersOptions<NSCommonsLibs::BuilderType::StreamType> BuilderOption;
    NSUtils::BuilderInterfaceBase<NSCommonsLibs::BuilderType::StreamType
            ,BuilderOption
            >StreamOptionXmlReader(&aBuilderOptions);

     StreamOptionXmlReader.buildAll(aErrorCode);

     std::cout<<"ErrorCode: "<<aErrorCode<<std::endl;
     std::cout<<"cantidad de subnodos: "<<aBuilderOptions.SubNodeVector.size()<<std::endl;
     */
     //aBuilderOptions.SubNodeVector.at(0).print();//Row name options
     //aBuilderOptions.getSubnode("USyCI")->print();
     NSBuilders::Builders<NSCommonsLibs::BuilderType::StreamType> aStreamBuilder("/home/ricardo/Desktop/proyecto/cooperative_drones/trunks/src/autonomous_generic_drone/config/config/generaloptionconfig.xml");
     aStreamBuilder.buildAll(aErrorCode);
	return 0;
}
