#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include <mutex>
#include "definiciones.h"
#include <unordered_map>
#include "component_sadi_model.h"
#include "model_property_unit.h"
#include "proxy_properties.h"
#include "process_gimbal_speed.h"
#include <condition_variable>
#include "property_action_process_manager.h"
#include "sadi_nodes_properties.h"
#include "watchdog_manager.h"
namespace SADI_MODEL
{
  struct WatchDogOption
  {
    constexpr WatchDogOption(const unsigned low_time_out_value
                   ,const unsigned high_time_out_value):low_time_out(low_time_out_value)
                                                        ,high_time_out(high_time_out_value)
    {

    }
    const unsigned low_time_out;
    const unsigned high_time_out;
  };
class ModelManager
{
    static constexpr WatchDogOption watchdog_option{800,800};
    public:
    typedef SADI_KERNEL::SadiComponent SADIComponentNode;
    typedef std::unordered_map<SADI_KERNEL::EProxyID,SADIComponentNode,std::enum_hash>::iterator ComponentNodeIterator;

    static ModelManager & getModel()
    {
        static std::mutex aLocalMutex;
        static std::lock_guard<std::mutex> lock(aLocalMutex);
        if(ModelManagerPtr==nullptr)
        {
            if(!isNullPtr) deadReferenceDetected();
            else createInstance();
        }
        return *ModelManagerPtr;


    }
    void setConditionVariablePtr(std::condition_variable * const aConditionVariablePtr)
    {
      _ConditionVariablePtr=aConditionVariablePtr;
    }
    void notifyConditionVariable()
    {
      _ConditionVariablePtr->notify_one();
    }
    void getHeaderId(unsigned & _HeaderId)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        _HeaderId=static_cast<unsigned>(aHeaderID++);
    }

    void setUCState(const SADI_KERNEL::EUCSTATE & aState)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        mCurrentUCState=aState;

    }
    void getCurrentUCState(SADI_KERNEL::EUCSTATE & aState)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        aState=mCurrentUCState;
    }
    //TODO agregar los estado de la unidad de control aca!
    void setNanoCmdStateById(const int & aNanoCmdId, const SADI_KERNEL::ECMDSTATE & aCmdState)
    {
        std::lock_guard<std::mutex> lock(aMutex);

        nanoCmdIterator=aNanoGlobalCmdTable.find(aNanoCmdId);
        if (nanoCmdIterator==aNanoGlobalCmdTable.end())
        {
            auto aPair=std::make_pair(aNanoCmdId,aCmdState);
            aNanoGlobalCmdTable.insert(aPair);
        }
        else (nanoCmdIterator->second)=aCmdState;
    }
    void getNanoCmdStateByID(const int & aNanoCmdId, SADI_KERNEL::ECMDSTATE & aCmdState, int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        nanoCmdIterator=aNanoGlobalCmdTable.find(aNanoCmdId);
        aErrorCode=ERROR_PROCESSING_CODE;
        if(nanoCmdIterator==aNanoGlobalCmdTable.end()) return;
        aCmdState=nanoCmdIterator->second;
        aErrorCode=OK_ERROR_CODE;
    }
    void setComponentNodeMap(const std::unordered_map<SADI_KERNEL::EProxyID,SADIComponentNode,std::enum_hash> & aMap)
    {
        mComponentNodeMap=aMap;
    }
    void setComponenteState(const SADI_KERNEL::EProxyID & aProxyId
                            , const SADI_PROXY::EPROXYSTATE & aComponentState
                            , int & aErrorCode)
    {
         std::lock_guard<std::mutex> lock(aMutex);
        aErrorCode=ERROR_PROCESSING_CODE;
        mComponentNodeIterator=mComponentNodeMap.find(aProxyId);
        if(mComponentNodeIterator==mComponentNodeMap.end()) return;
        ((mComponentNodeIterator->second)).setComponentState(aComponentState);
        aErrorCode=OK_ERROR_CODE;
    }

    void setSubComponenteStatusError(const SADI_KERNEL::EProxyID & aComponentId
                                     ,const SADI_KERNEL::EProxyID & aSubComponentId
                                     , const unsigned  & aErrorLevel
                                     , int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        aErrorCode=ERROR_PROCESSING_CODE;
        mComponentNodeIterator=mComponentNodeMap.find(aComponentId);
        if(mComponentNodeIterator==mComponentNodeMap.end()) return;
        (mComponentNodeIterator->second).setSubComponentErrorLevel(aSubComponentId,aErrorLevel,aErrorCode);
    }
    //-------------------------------------------------------------------
    void getSubComponentStatusError(const SADI_KERNEL::EProxyID & aComponentId
                                    ,const SADI_KERNEL::EProxyID & aSubComponentId
                                    , unsigned  & aErrorLevel
                                    , int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        aErrorCode=ERROR_PROCESSING_CODE;
        mComponentNodeIterator=mComponentNodeMap.find(aComponentId);
        if(mComponentNodeIterator==mComponentNodeMap.end()) {

            return;
        }
        (mComponentNodeIterator->second).getSubComponentErrorLevel(aSubComponentId,aErrorLevel,aErrorCode);


    }

    void getCurrentProxyState(const SADI_KERNEL::EProxyID & aProxyID, SADI_PROXY::EPROXYSTATE & aProxyState, int & aErrorCode)
    {
         std::lock_guard<std::mutex> lock(aMutex);
        aErrorCode=ERROR_PROCESSING_CODE;
        mComponentNodeIterator=mComponentNodeMap.find(aProxyID);
        if(mComponentNodeIterator==mComponentNodeMap.end()) return;
        (mComponentNodeIterator->second).getComponentCurrentSate(aProxyState);
        aErrorCode=OK_ERROR_CODE;
    }
    void setModelPropertiesMap(std::unordered_map<SADI_MODEL::Properties,SADI_MODEL::IModelProperties * ,std::enum_hash> * const aMapPtr)
    {
        _MapPtr=aMapPtr;
        _MapPtr->insert(std::make_pair(SADI_MODEL::Properties::ALL_CAMERAS_READY,new  SADI_MODEL::ModelProperties<bool>(false) ));
        _MapPtr->insert(std::make_pair(SADI_MODEL::Properties::DEFROSTER_STATE,
                                       new SADI_MODEL::ModelProperties<int>(static_cast<int>(EDEFROSTER_STATE::OFF))));
        _MapPtr->insert(std::make_pair(SADI_MODEL::Properties::TERMICAL_CONTROL_ALARM_STATE,
                                       new SADI_MODEL::ModelProperties<int>(static_cast<int>(CT_ALARM_STATE::OFF))));
        //HAS_DEFROSTER_ARRIVED
        //
        _MapPtr->insert(std::make_pair(SADI_MODEL::Properties::HAS_DEFROSTER_ARRIVED,
                                       new SADI_MODEL::ModelProperties<bool>(static_cast<bool>(DEFROSTER_CMD_ARRIVED::FALSE))));
    }
    template<typename T >
    void getModelProperty(const SADI_MODEL::Properties & aProperty, T & aUValue, int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        auto const_iterator=_MapPtr->find(aProperty);
        aErrorCode=ERROR_PROCESSING_CODE;
        if (const_iterator==_MapPtr->end()) return;
        (const_iterator->second)->getProperty(aUValue);
        aErrorCode=OK_ERROR_CODE;
    }

    void setModelProperty(const SADI_MODEL::Properties & aProperty,const unsigned & aUValue, int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        auto const_iterator=_MapPtr->find(aProperty);
        aErrorCode=ERROR_PROCESSING_CODE;
        if (const_iterator==_MapPtr->end()) return;
        dynamic_cast<ModelProperties<unsigned>*>((const_iterator->second))->setValue(aUValue);
        aErrorCode=OK_ERROR_CODE;
    }

    template<typename T>
    void setModelProperty(const SADI_MODEL::Properties & aProperty,const T & aUValue, int & aErrorCode)
    {
        std::lock_guard<std::mutex> lock(aMutex);
        auto const_iterator=_MapPtr->find(aProperty);
        aErrorCode=ERROR_PROCESSING_CODE;
        if (const_iterator==_MapPtr->end()) return;
        dynamic_cast<ModelProperties<T>*>((const_iterator->second))->setValue(aUValue);
        aErrorCode=OK_ERROR_CODE;
    }

    void setProxyPropertiesMap(const std::unordered_map<SADI_KERNEL::EProxyID,ProxyProperties, std::enum_hash> & aProxyPropertyMap)
    {
      _ProxyPropertiesMaps=aProxyPropertyMap;
      //TODO:FIXEAR MAOA DE PROPIEADADES ORIGINAL!!!
      _ProxyStateMap.insert(std::make_pair(SADI_KERNEL::EProxyID_UISG,SADI_PROXY::EPROXYSTATE_NO_INIT));
      _ProxyStateMap.insert(std::make_pair(SADI_KERNEL::EProxyID_UPI,SADI_PROXY::EPROXYSTATE_NO_INIT));
      //ingreso a mano del estado actual del proxy

    }
    /*
    void getProxyProperties(const SADI_KERNEL::EProxyID & aProxyId, ProxyProperties & aProxyProoerty, int & aErrorCode)
    {
       std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=ERROR_PROCESSING_CODE;
      const auto iterator=_ProxyPropertiesMaps.find(aProxyId);
      if(iterator!=_ProxyPropertiesMaps.end())
        {
          aErrorCode=OK_ERROR_CODE;
          aProxyProoerty=iterator->second;
        }
    }
    */
    //
    template<typename T>
    void setProxyProperties(const SADI_KERNEL::EProxyID & aProxyId,const SADI_PROXY::EProxyProperties & aProxyPropertie, const T& aValue, int & aErrorCode)
    {
       std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=ERROR_PROCESSING_CODE;
      const auto iterator=_ProxyPropertiesMaps.find(aProxyId);
      if(iterator!=_ProxyPropertiesMaps.end())
        {
          aErrorCode=OK_ERROR_CODE;
          (iterator->second).updateProxyProperty(aProxyPropertie,aValue,aErrorCode);
        }
    }
    template<typename T>
    void getProxyProperty(const SADI_KERNEL::EProxyID & aProxyId,const SADI_PROXY::EProxyProperties & aProxyPropertie, T& aValue, int & aErrorCode)
    {
       std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=ERROR_PROCESSING_CODE;
      const auto iterator= _ProxyPropertiesMaps.find(aProxyId);
      if(iterator!=_ProxyPropertiesMaps.end())
        {
          aErrorCode=OK_ERROR_CODE;
          (iterator->second).getPropiestyValue(aProxyPropertie,aValue,aErrorCode);
        }
    }

    void translateNanoCmdIDToProtoCmdId(const unsigned & aNanoID, unsigned & aProtoCmdId, int & aErrorCode)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=ERROR_PROCESSING_CODE;
      auto iterator=_TranslationMap.find(aNanoID);
      if (iterator!=_TranslationMap.end())
        {
          aProtoCmdId=iterator->second;
          aErrorCode=OK_ERROR_CODE;
        }
    }
    void translateProtoToNanoCmdId(const unsigned & aProtoCmdId, unsigned & aNanoCmdId, int & aErrorCode)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      const auto iterator=TranslationMapProto.find(aProtoCmdId);
      aErrorCode=ERROR_CODES::ERROR_ERROR_CODE;//-1
      if (iterator!=TranslationMapProto.end())
        {
            aNanoCmdId=iterator->second;
            aErrorCode=ERROR_CODES::OK_ERROR_CODE;
        }
    }
    void setCmdTranslationMatrix(const std::unordered_map<unsigned,unsigned> & aTranslationMap)
    {
      _TranslationMap.clear();
      _TranslationMap=aTranslationMap;
    }
    template<typename T>
    void setProxySubNodeProperty(const SADI_KERNEL::EProxyID & aProxyId, const SADI_KERNEL::EProxyID & aSubNodeID
                                 , const SADI_PROXY::EProxyProperties & aProperty
                                 , const T & aValue
                                 ,int & aErrorCode)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=ERROR_CODES::ACTION_ERROR_PROCESS;
      auto iterator=_ProxySubNodeProperties.find(aProxyId);
      if(iterator!=_ProxySubNodeProperties.end())
        {
          auto it=(iterator->second).mSubNodeMap.find(aSubNodeID);
          if(it!=((iterator->second).mSubNodeMap).end())
            {
              (iterator->second).mSubNodeMap[aSubNodeID].setProperty(aProperty,aValue);
              aErrorCode=ERROR_CODES::OK_ERROR_CODE;
            }

        }
    }
    template<typename T>
    void getProxySubNodeProperty(const SADI_KERNEL::EProxyID & aProxyId, const SADI_KERNEL::EProxyID & aSubNodeID
                                  , const SADI_PROXY::EProxyProperties & aProperty
                                  , T & aValue
                                  ,int & aErrorCode)
    {
      std::lock_guard<std::mutex> lock(aMutex);
       aErrorCode=ERROR_CODES::ACTION_ERROR_PROCESS;
      auto iterator=_ProxySubNodeProperties.find(aProxyId);
      if(iterator!=_ProxySubNodeProperties.end())
        {
          auto it=(iterator->second).mSubNodeMap.find(aSubNodeID);
          if(it!=((iterator->second).mSubNodeMap).end())
            {
              (iterator->second).mSubNodeMap[aSubNodeID].getProperty(aProperty,aValue);
              aErrorCode=ERROR_CODES::OK_ERROR_CODE;
            }

        }
    }
    void setProxySubNodesPropertiesMap(const std::unordered_map<SADI_KERNEL::EProxyID,SADI_KERNEL::sadi_node,std::enum_hash> & aProxySubNodeProperties)
    {
        _ProxySubNodeProperties=aProxySubNodeProperties;

    }
    template<typename T>
    void executeModelProperty(const SADI_KERNEL::EProxyID &,const SADI_KERNEL::EProxyID &,const SADI_MODEL::EModelProperty &,const T &, int &)
    {

    }
    void setProxyState(const SADI_KERNEL::EProxyID & aProxyID,
                        const SADI_PROXY::EPROXYSTATE & aState
                        ,int & aErrorCode)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      aErrorCode=-1;
      const auto iterator=_ProxyStateMap.find(aProxyID);
      if(iterator!=_ProxyStateMap.end())
        {
          _ProxyStateMap[aProxyID]=aState;
          aErrorCode=ERROR_CODES::OK_ERROR_CODE;
        }
    }
    void getProxyState(const SADI_KERNEL::EProxyID & aProxyID,
                        SADI_PROXY::EPROXYSTATE &aState ,
                        int & aErrorCode)
    {
          std::lock_guard<std::mutex> lock(aMutex);
          aErrorCode=-1;
          const auto iterator=_ProxyStateMap.find(aProxyID);
          if(iterator!=_ProxyStateMap.end())
            {
              aState=_ProxyStateMap[aProxyID];
              aErrorCode=ERROR_CODES::OK_ERROR_CODE;
            }
    }
    void setCamIdToTrack(const unsigned & idCam)
    {
       std::lock_guard<std::mutex> lock(aMutex);
      _IdCamToTrack=idCam;
       //std::cout<<SH_FG_LIGHT_RED<<"(SET autotracker MODELMANAGER)"<<SH_DEFAULT<<_IdCamToTrack<<std::endl;
    }
    void getTrackerCamId(unsigned & idCam)
    {
       std::lock_guard<std::mutex> lock(aMutex);
       //std::cout<<SH_FG_LIGHT_RED<<"GET autotracker MODELMANAGER)"<<SH_DEFAULT<<_IdCamToTrack<<std::endl;
       idCam=_IdCamToTrack;
    }
    void setGimbalSpeedSensibility(const float & aSensibilityValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
        _GimbalSpeed=aSensibilityValue;
    }
    void getGimbalSpeedSensibility(float & aSensibilityValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
        aSensibilityValue=_GimbalSpeed;
    }
    void setGimbalElevationValue(const float aElevationValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      ElevationValue=aElevationValue;
    }
    void getGimbalElevationValue(float & aElevationValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      aElevationValue=ElevationValue;
    }
    void setGimbalAzimutValue(const float aAzimutValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      AzimutValue=aAzimutValue;
    }
    void getGimbalAzimutValue(float & aAzimutValue)
    {
      std::lock_guard<std::mutex> lock(aMutex);
      aAzimutValue=AzimutValue;
    }
    void initWatchDog()
    {
      WatchDogManager.setupPin();
      WatchDogManager.init();
    }
    void stopWatchDog()
    {
      WatchDogManager.stop();
    }
    private:
    static const int OK_ERROR_CODE=0;
    static const int ERROR_PROCESSING_CODE=-1;
    static const unsigned high_wacthdog_timeout=800u;
    static const unsigned low_wacthdog_timeout=800u;
    ModelManager():aHeaderID(0)
      ,mCurrentUCState(SADI_KERNEL::EUCSTATE::EUCSTATE_INIT)
    ,_ConditionVariablePtr(nullptr)
    ,_IdCamToTrack(5001u)
    ,_GimbalSpeed(10.0f)
    ,ElevationValue(0.0f)
    ,AzimutValue(0.0f)
    ,WatchDogManager(800u,800u)
    {
      auto aPair=std::make_pair(static_cast<unsigned>(SADI_KERNEL::EUPI_CMD::EUPI_CMD_TX_CAMERA_ON),static_cast<unsigned>(SADI_KERNEL::UCP_CMD_TX_H264));
      _TranslationMap.insert(aPair);
      aPair=std::make_pair(static_cast<unsigned>(SADI_KERNEL::EUPI_CMD::EUPI_CMD_TX_CAMERA_OFF),static_cast<unsigned>(SADI_KERNEL::UCP_CMD_TX_H264_STOP));
      _TranslationMap.insert(aPair);
      _TranslationMap.insert(std::make_pair(static_cast<unsigned>(SADI_KERNEL::EUISG_CMD::EUISG_CMD_NADIR_MODE),static_cast<unsigned>(SADI_KERNEL::UCP_CMD_MODO_NADIR)));
      _TranslationMap.insert(std::make_pair(static_cast<unsigned>(SADI_KERNEL::EUISG_CMD::EUISG_CMD_RESET_AHRS),static_cast<unsigned>(SADI_KERNEL::UCP_CMD_RESET_AHRS)));
      //
        setProtoCmdIdTranslationMap();
        
    }
    ModelManager(const ModelManager & ) = delete;
    ModelManager(const ModelManager && ) = delete;
    const ModelManager & operator=( const ModelManager &) = delete;
    ~ModelManager()
    {
        ModelManagerPtr= nullptr;
        isNullPtr=true;
        //Destruir mapas que tienen punteros

    }
    void setProtoCmdIdTranslationMap()
    {
      TranslationMapProto.insert(std::make_pair(static_cast<unsigned>(SADI_KERNEL::UCP_CMD_DESEMPANADOR)
                                                ,static_cast<unsigned>(SADI_KERNEL::EUISG_CMD::EUISG_CMD_DESEMPANADOR)));
    }
    static void deadReferenceDetected()
    {
        throw std::runtime_error("Model Manager Dead Reference Detected!");
    }
    static void createInstance()
    {
            static ModelManager aModelManager;
            ModelManagerPtr=& aModelManager;
            isNullPtr=false;
    }

    static ModelManager * ModelManagerPtr;
    static bool isNullPtr;
    volatile unsigned aHeaderID;
    std::mutex aMutex;
    SADI_KERNEL::EUCSTATE mCurrentUCState;
    std::unordered_map<int,SADI_KERNEL::ECMDSTATE> aNanoGlobalCmdTable;
    std::unordered_map<int,SADI_KERNEL::ECMDSTATE>::iterator nanoCmdIterator;
    std::unordered_map<SADI_KERNEL::EProxyID,SADIComponentNode,std::enum_hash> mComponentNodeMap;
    ComponentNodeIterator mComponentNodeIterator;
    std::unordered_map<SADI_MODEL::Properties,SADI_MODEL::IModelProperties * ,std::enum_hash> * _MapPtr;
    std::unordered_map<SADI_KERNEL::EProxyID,ProxyProperties, std::enum_hash> _ProxyPropertiesMaps;
    //calculo de la sensibilidad del gimbal en funcion del zoom
    std::unordered_map<SADI_MODEL::EModelProperty,std::unordered_map<SADI_KERNEL::EProxyID,SADI_MODEL::IModelProcess<float>*,std::enum_hash>,std::enum_hash> _ModelPropertyMap;
    std::unordered_map<unsigned,unsigned> _TranslationMap;

    std::condition_variable * _ConditionVariablePtr;
    std::unordered_map<SADI_KERNEL::EProxyID,SADI_KERNEL::sadi_node,std::enum_hash> _ProxySubNodeProperties;
    //TODO:Eliminar correctamente los mapas creados por el manager
    ActionPropertiesManager _ActionPropertyManager;
    std::unordered_map<SADI_KERNEL::EProxyID,SADI_PROXY::EPROXYSTATE,std::enum_hash> _ProxyStateMap;
    unsigned _IdCamToTrack;
    float _GimbalSpeed;
    float ElevationValue;
    float AzimutValue;
    std::unordered_map<unsigned, unsigned > TranslationMapProto;
    SADI_KERNEL::WatchDogManager WatchDogManager;

};
ModelManager * ModelManager::ModelManagerPtr= nullptr;
bool ModelManager::isNullPtr=true;
}
#endif // MODELMANAGER_H
