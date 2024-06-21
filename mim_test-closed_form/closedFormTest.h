#include <stdbool.h> // for bool
#include <stdint.h>  // for uint8_t


typedef struct Data
{
  float storedEnergy;
  float maxEnergy;
  float speed;
  float rotation;
  uint8_t magnets;
  bool ownsOutputGauge;
  bool ownsFlywheel;
  bool ownsMagnetsUpgrade;
  bool ownsHamster;
} Data;
