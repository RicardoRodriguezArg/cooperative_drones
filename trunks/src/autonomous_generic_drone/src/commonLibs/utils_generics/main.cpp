#include "generis_strutures.h"
#include "linux_uitls.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
static const std::unordered_map<std::string,int> map({{"HOLA",1},
                                                   {"QWERTY",2},
                                                   {"HANDS",3}});
struct BaseComparator
{
  bool operator()(const std::tuple<std::string,uint64_t> & FirstValue,
                  const std::tuple<std::string,uint64_t> & SecondValue
                  )
  {
    return (std::get<1>(FirstValue)<
            std::get<1>(SecondValue));
  }
}Comparator;
int main()
{
  std::cout<<"utils generics"<<std::endl;


  std::string  DirectoryName("~/Desktop/CODIGO/uc/FLIR_MINSEG_Software/trunk/src/mainControlUnit_UC_SBC340/build/unidadcontrol");
  int aErrorCode=0;
  NSUtils::getPathFromString(DirectoryName,aErrorCode);
  std::cout<<"DirectoryName: "<<DirectoryName<<std::endl;
  std::cout<<"aErrorCode: "<<aErrorCode<<std::endl;
  /*
  NSUtils::LinuxUtils::getAllFilesFromDirectory(DirectoryName.c_str(),FileVector);
  NSUtils::LinuxUtils::LinuxTimeStructure * aPtr=nullptr;
  std::vector<std::tuple<std::string,uint64_t>> deltaTimeVector;
  uint64_t SecondsFromCreation=0U;
  for(auto iterator = FileVector.begin();
      iterator!= FileVector.end();
      iterator++)
    {
      NSUtils::LinuxUtils::getLastTimeModifiedDate(NSUtils::concatenate(DirectoryName,(*iterator)).c_str(),aPtr);
      NSUtils::getTimeFromCreation<uint64_t>(aPtr,SecondsFromCreation);
      deltaTimeVector.emplace_back(std::make_tuple(NSUtils::concatenate(DirectoryName,(*iterator)),SecondsFromCreation));
      aPtr=nullptr;
    }
  typedef NSUtils::Comparator<std::tuple<std::string,uint64_t>> SECONDS_COMPARATOR;

  std::sort(deltaTimeVector.begin(),deltaTimeVector.end(),NSUtils::ComparatorClass);

  for (auto it=deltaTimeVector.begin(); it!=deltaTimeVector.end(); ++it)
      std::cout << ' ' << std::get<0>((*it))<<" --->> "<<std::get<1>((*it))<<std::endl;

*/

  return 0;
}
