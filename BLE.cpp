#include "BLE.h"
#include "PRD.h"

namespace sm {

PresetSelectCallbacks::PresetSelectCallbacks(GameState& gameState)
  : m_GameState(gameState) {}

void PresetSelectCallbacks::onWrite(NimBLECharacteristic* characteristic, NimBLEConnInfo& connInfo) {
  std::string value = characteristic->getValue();
  m_GameState.setPRDPreset(getPresetFromBLEString(value));
}

const PRDPreset& getPresetFromBLEString(const std::string& str) {
  Serial.println(str.c_str());
  if (str == "n") return PRDPresets::normal;
  else if (str == "e1") return PRDPresets::extraLucky;
  else if (str == "e2") return PRDPresets::extraLucky2;
  else if (str == "2lw") return PRDPresets::twoThenWin;
  else if (str == "3lw") return PRDPresets::threeThenWin;
  else if (str == "lw") return PRDPresets::lw;
  else if (str == "w") return PRDPresets::win;
  else if (str == "l") return PRDPresets::loss;
  else if (str == "wc") return PRDPresets::weirdChances;
  else {
    SM_ASSERT(false, "Unknown preset string sent")
    return PRDPresets::normal;
  }
}

void setupBLEforPresetSelect(GameState& gameState) {
  NimBLEDevice::init("PRD_PRESETS");
  NimBLEServer* server = NimBLEDevice::createServer();

  NimBLEService* service = server->createService(SM_SERVICE_UUID);

  NimBLECharacteristic* characteristic = service->createCharacteristic(
    SM_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::WRITE);

  characteristic->setCallbacks(new PresetSelectCallbacks(gameState));

  service->start();
  NimBLEDevice::getAdvertising()->start();
}

}
