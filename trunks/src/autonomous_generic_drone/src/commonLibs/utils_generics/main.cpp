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

  std::vector<std::string> FileVector;
  const std::string  DirectoryName("/home/ricardo/Desktop/CODIGO/uc/FLIR_MINSEG_Software/trunk/src/mainControlUnit_UC_SBC340/build/unidadcontrol");
  NSUtils::LinuxUtils::getAllFilesFromDirectory(DirectoryName.c_str(),FileVector);
  NSUtils::LinuxUtils::LinuxTimeStructure * aPtr=nullptr;
  std::vector<std::tuple<std::string,uint64_t>> deltaTimeVector;
  for(auto iterator = FileVector.begin();
      iterator!= FileVector.end();
      iterator++)
    {

     // std::cout<<"nombre: "<<NSUtils::concatenate(DirectoryName,(*iterator))<<std::endl;
      NSUtils::LinuxUtils::getLastTimeModifiedDate(NSUtils::concatenate(DirectoryName,(*iterator)).c_str(),aPtr);

      const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
      auto aTimePoint=NSUtils::Tm((aPtr->tm_year),
                                        (aPtr->tm_mon),
                                        (aPtr->tm_mday),
                                        (aPtr->tm_hour),
                                        (aPtr->tm_min),
                                        (aPtr->tm_sec),
                                        0);
      const std::chrono::system_clock::time_point time_ellapse =aTimePoint.to_time_point();

      deltaTimeVector.emplace_back(std::make_tuple(NSUtils::concatenate(DirectoryName,(*iterator)),
                                                   std::chrono::duration_cast<std::chrono::seconds>(now - time_ellapse).count()));



      aPtr=nullptr;
      //std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(tp_nomicro).count()<<std::endl;
    }
  typedef NSUtils::Comparator<NSUtils::EComparatorType::ESeconds,std::tuple<std::string,uint64_t>> SECONDS_COMPARATOR;
  std::sort(deltaTimeVector.begin(),deltaTimeVector.end(),SECONDS_COMPARATOR);

  for (auto it=deltaTimeVector.begin(); it!=deltaTimeVector.end(); ++it)
      std::cout << ' ' << std::get<0>((*it))<<" --->> "<<std::get<1>((*it))<<std::endl;


  return 0;
}
