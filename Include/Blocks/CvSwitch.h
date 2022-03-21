#ifndef CvSwitchH
#define CvSwitchH

#include <map>

#include <MusicTools.h>

class CvSwitch
{
public:
   using VoltageList = std::vector<float>;
   using VoltageMap = std::map<uint8_t, VoltageList>;

   enum class Device
   {
      MimeticDigitalis4,
      MimeticDigitalis16,
      ViceVirga2,
      ViceVirga4,
      ViceVirga8,
      TotalRecall
   };

public:
   inline CvSwitch(const Device& device);

public:
   inline static const std::string deviceName(const Device& device);
   inline const Device& getDevice() const;
   inline const uint8_t& getMaxIndex() const;
   inline float map(const uint8_t index) const;

   inline static VoltageMap compileVoltageMap();

private:
   uint8_t maxIndex;
   VoltageList offsetVoltageList;
   Device device;
};

#include "CvSwitch.hpp"

#endif // CvSwitchH
