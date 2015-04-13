#ifndef UTILS_BUILDER_H
#define UTILS_BUILDER_H
namespace NSBuilders
{
  namespace Utils
  {
    template<typename InputDataType,typename OutputDataType>
    class TransformStructure
    {
    public:
      TransformStructure(InputDataType * const aInputStructure):InputStructure(aInputStructure)
      {

      }
      void transform(int & aErrorCode)
      {

      }
    private:
      InputDataType * const InputStructure;
      OutputDataType OutPutStructure;
    };
  }
}
#endif // UTILS_BUILDER_H
