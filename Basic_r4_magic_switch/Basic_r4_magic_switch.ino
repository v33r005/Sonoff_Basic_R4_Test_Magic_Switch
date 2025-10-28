#include "definicje.h"
#include "biblioteki.h"
#include "zmienne.h"
#include "funkcje.h"
#include "c_iterate.h"
#include "html_classes.h"
void setup() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  
  Serial.begin(115200);
  #include "storage_init.h"
  if (MagicSwitchOn == ON_){
    attachInterrupt(INTERRUPT_PIN, zmienStan, RISING);
  }
  auto buttonCfgRelay = new Supla::Control::Button(BUTTON_CFG_RELAY_GPIO, true, true);
  buttonCfgRelay->configureAsConfigButton(&SuplaDevice);

  relay_ = new Supla::Control::Relay(RELAY_PIN,true);
  relay_->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);
  switch (selectMode) {
    case 1:
      relay_->setDefaultStateOn();
      break;
    case 2:
      relay_->setDefaultStateRestore();
      break;
    default:
      relay_->setDefaultStateOff();
      break;
  }

  buttonCfgRelay->addAction(Supla::TOGGLE, relay_, Supla::ON_CLICK_1);
 

  #include "html.h"
  httpUpdater.setup(suplaServer.getServerPtr(), "/update");
  SuplaDevice.allowWorkInOfflineMode(0); 
  SuplaDevice.setLeaveCfgModeAfterInactivityMin(0);
  SuplaDevice.setName(devName);
  SuplaDevice.setSwVersion(SOFT_VERSION);
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);
  SuplaDevice.setProtoVerboseLog(false);
  SuplaDevice.begin();
}

void loop() {
  SuplaDevice.iterate();
}
