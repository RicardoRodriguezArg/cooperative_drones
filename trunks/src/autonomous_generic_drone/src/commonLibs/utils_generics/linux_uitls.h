/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief: Archivo de clases utiles para la administracion de archivos en linux
  *
  *
  */
#ifndef LINUX_UITLS_H
#define LINUX_UITLS_H
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <ctime>
#include <dirent.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
namespace NSUtils
{
  typedef struct tm LinuxTimeStructure;
  enum class EComparatorType
  {
      ESeconds
  };

  template<EComparatorType,typename T>
  struct Comparator
  {

  };
  template<typename T>
  struct Comparator<EComparatorType::ESeconds,T>
  {
    bool operator()(const T & FirstValue,
                    const T & SecondValue
                    )
    {
      return (std::get<1>(FirstValue)<
              std::get<1>(SecondValue));
    }
  };

  struct LinuxUtils
  {
    typedef struct stat LinuxFileAttributes;
    typedef struct tm LinuxTimeStructure;
    static void getLastTimeModifiedDate(const char * const aFileName, LinuxTimeStructure *& timeFromCreation)
    {
      LinuxFileAttributes attributes;
      stat(aFileName , &attributes);
      timeFromCreation = gmtime(&(attributes.st_mtime));


    }

    template<typename Vector>
    static void getAllFilesFromDirectory( const char * const aDirectoryName, Vector & aVectorFileName)
    {
      DIR *dpdf;
      struct dirent *epdf;
      dpdf = opendir(aDirectoryName);
      if (dpdf != nullptr)
        {
         while (epdf = readdir(dpdf)){
             const auto file=std::move(std::string(epdf->d_name));
             if ((file.compare(".")!=0) && ((file.compare("..")!=0))) aVectorFileName.emplace_back(std::string(epdf->d_name));
          }
        }
    }


  };
  static std::string concatenate(const std::string & FirstPart, const std::string & SecondPart)
  {
    return (FirstPart +"/" +SecondPart);
  }

  struct Tm : std::tm {
    int tm_usecs; // [0, 999999] micros after the sec

    Tm(const int year, const int month, const int mday, const int hour,
       const int min, const int sec, const int usecs, const int isDST = -1)
        : tm_usecs{usecs} {
      tm_year = year - 100; //solamente sacar 100
      tm_mon = month - 1;    // [0, 11] since Jan
      tm_mday = mday;        // [1, 31]
      tm_hour = hour;        // [0, 23] since midnight
      tm_min = min;          // [0, 59] after the hour
      tm_sec = sec;          // [0, 60] after the min
                             //         allows for 1 positive leap second
      tm_isdst = isDST;      // [-1...] -1 for unknown, 0 for not DST,
                             //         any positive value if DST.
    }

    template <typename Clock_t = std::chrono::high_resolution_clock,
              typename MicroSecond_t = std::chrono::seconds>
    auto to_time_point() -> typename Clock_t::time_point {
      auto time_c = mktime(this);
      return Clock_t::from_time_t(time_c) /*+ MicroSecond_t{tm_usecs}*/;
    }
  };

  template<typename type>
  static void getTimeFromCreation(LinuxTimeStructure * const timeFromCreation, type & TimeInSeconds)
  {
    const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto aTimePoint=Tm((timeFromCreation->tm_year),
                                      (timeFromCreation->tm_mon),
                                      (timeFromCreation->tm_mday),
                                      (timeFromCreation->tm_hour),
                                      (timeFromCreation->tm_min),
                                      (timeFromCreation->tm_sec),
                                      0);
    const std::chrono::system_clock::time_point time_ellapse =aTimePoint.to_time_point();
    TimeInSeconds=std::chrono::duration_cast<std::chrono::seconds>(now - time_ellapse).count();
  }

}
#endif // LINUX_UITLS_H
