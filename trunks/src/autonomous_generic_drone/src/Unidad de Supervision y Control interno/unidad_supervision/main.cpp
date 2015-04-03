#include "kernel.h"
int main()
{
    FLAGS_logtostderr = true;
    NSUC_Kernel::Kernel::initSystemSingletons();
    NSUC_Kernel::Kernel unidad_supervision;
    unidad_supervision.init();
	return 0;
}
