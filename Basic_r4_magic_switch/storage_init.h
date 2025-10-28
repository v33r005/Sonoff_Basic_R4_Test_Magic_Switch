#ifndef STORAGE_INIT_H_
#define STORAGE_INIT_H_

//******************własna nazwa*****************************
  Supla::Storage::Init();
  auto cfg = Supla::Storage::ConfigInstance();
  if (cfg->getString(DEV_NAME, devName, 30)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
  } else {
    Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-BASIC_R4");
  }
//****************************************************************
cfg->getUInt8(MAGIC_SWITCH_ON, &MagicSwitchOn);
if (cfg->getUInt32(SELECT_MODE, &selectMode)) {} else {}

#endif