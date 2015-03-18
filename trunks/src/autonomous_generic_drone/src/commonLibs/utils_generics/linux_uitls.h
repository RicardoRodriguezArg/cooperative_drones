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
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include <ctime>
#include <dirent.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
namespace NSUtils
{
  typedef struct tm LinuxTimeStructure;
  enum class EComparatorType
  {
      ESeconds
  };


  template<typename T>
  struct Comparator
  {
    bool operator()(const T & FirstValue,
                    const T & SecondValue
                    )
    {
      return (std::get<1>(FirstValue)<
              std::get<1>(SecondValue));
    }
  };
  struct BaseComparator
  {
    bool operator()(const std::tuple<std::string,uint64_t> & FirstValue,
                    const std::tuple<std::string,uint64_t> & SecondValue
                    )
    {
      return (std::get<1>(FirstValue)<
              std::get<1>(SecondValue));
    }
  }ComparatorClass;

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
  static int removeFile(const std::string & aFileName)
  {
    return (unlink(aFileName.c_str()));
  }
  struct Tm : std::tm {

    constexpr static int INITIAL_YEAR=100;
    constexpr static int AVOID_JANUARY=1;
    constexpr static int DEFAULT_mSECONDS=0;
    constexpr static int NO_DST=-1;
    int tm_usecs; // [0, 999999] micros after the sec

    Tm(const int year, const int month, const int mday, const int hour,
       const int min, const int sec, const int usecs = 0, const int isDST = -1)
        : tm_usecs{usecs} {
      tm_year = year - INITIAL_YEAR;                                            //solamente sacar 100
      tm_mon = month - AVOID_JANUARY ;                                          // [0, 11] since Jan
      tm_mday = mday;                                                           // [1, 31]
      tm_hour = hour;                                                           // [0, 23] since midnight
      tm_min = min;                                                             // [0, 59] after the hour
      tm_sec = sec;                                                             // [0, 60] after the min
                                                                                //         allows for 1 positive leap second
      tm_isdst = isDST;                                                         // [-1...] -1 for unknown, 0 for not DST,
                                                                            //         any positive value if DST.
    }

    template <typename Clock_t = std::chrono::high_resolution_clock,
              typename MicroSecond_t = std::chrono::seconds>
   auto to_time_point() -> typename Clock_t::time_point
    {
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
                                      (timeFromCreation->tm_sec)
                                      );
    const std::chrono::system_clock::time_point time_ellapse =aTimePoint.to_time_point();
    TimeInSeconds=std::chrono::duration_cast<std::chrono::seconds>(now - time_ellapse).count();
  }

  static void rotateFiles(const char * const aDirectoryPath,const unsigned & MaxFileCount)
  {
    const std::string  DirectoryName(aDirectoryPath);
    std::vector<std::string> FileVector;
    NSUtils::LinuxUtils::getAllFilesFromDirectory(DirectoryName.c_str(),FileVector);
    if(!FileVector.empty())
      {
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
        if(deltaTimeVector.size()>MaxFileCount)
        {
          for(auto index=MaxFileCount;index<deltaTimeVector.size();index++)
            {
              removeFile(std::get<0>(deltaTimeVector[index]));
            }
        }
      }

  }
  /**
   * @brief rotateFilesEx Mejora sobre la funcion anterior verifica el path relativo al HOME del usuario
   * @param aDirectoryPath
   * @param aMaxFilePath
   */
  static void rotateFilesEx(const char * const aDirectoryPath, const unsigned & aMaxFilePath)
  {
    const std::string  DirectoryName(aDirectoryPath);
  }
  static void getHomeDirectory(std::string & aHomeDirectoryPath)
  {
     aHomeDirectoryPath.clear();
     struct passwd *pw = getpwuid(getuid());
       aHomeDirectoryPath.assign(getpwuid(getuid())->pw_dir);

  }
  static void getPathFromString(std::string & aPathFileName, int & aErrorCode)
  {
    aErrorCode=-1;
    if (aPathFileName.at(0)=='~')
      {
        std::string HomeDirectory;
        getHomeDirectory(HomeDirectory);
        aErrorCode=HomeDirectory.empty()?-2:0;
        if (aErrorCode==0)
          {
            aPathFileName=HomeDirectory+aPathFileName.substr(1);
          }
      }
  }

}
#endif // LINUX_UITLS_H
