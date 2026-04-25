#pragma once
#include <NimBLEDevice.h>
#include "GameState.h"

#define SM_SERVICE_UUID "948e30fe-fe3b-4c65-bf36-e55c02133aa7"
#define SM_CHARACTERISTIC_UUID "34813e21-cfec-441c-8b5b-5c096604aa1f"

namespace sm {

class PresetSelectCallbacks : public NimBLECharacteristicCallbacks {
public:
  PresetSelectCallbacks(GameState& gameState);

private:
  void onWrite(NimBLECharacteristic* characteristic, NimBLEConnInfo& connInfo) override;

  GameState& m_GameState;
};

const PRDPreset& getPresetFromBLEString(const std::string& str);

void setupBLEforPresetSelect(GameState& gameState);

}
