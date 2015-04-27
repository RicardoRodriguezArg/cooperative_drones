#include <glog/logging.h>
#include "../kernel/kernel.h"
int main()
{

    FLAGS_logtostderr = true;
    NSUC_Kernel::Kernel::initSystemSingletons();

    NSUC_Kernel::Kernel unidad_supervision;
    LOG(INFO)<<"Iniciando Unidad de supervision";
    unidad_supervision.init();
    LOG(INFO)<<"Creando los componnentes del nucleo";
    unidad_supervision.createKernelDevices();
    LOG(INFO)<<"Configurando los ocmponenetes del kernel";
    unidad_supervision.configurateKernelComponents();
    LOG(INFO)<<"Finalizando unidad de supervision";
    unidad_supervision.shutdownKernelComponents();
	return 0;
}
