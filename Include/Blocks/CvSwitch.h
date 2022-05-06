#ifndef CvSwitchH
#define CvSwitchH

#include <map>

#include <MusicTools.h>

// things that have steps that can also be set by CV
// voltages range from 0.0V to 5.0V

class CvSwitch
{
public:
   enum class ChannelCount
   {
      None = 0,
      Two = 2,
      Four = 4,
      Eight = 8,
      Sixteen = 16
   };
   using VoltageList = std::vector<float>;

   using Step = uint8_t;
   using VoltageOffsetMap = std::map<Step, float>;

   struct StandardDevices;

public:
   inline CvSwitch(const ChannelCount& channelCount, const VoltageOffsetMap& offestMap = VoltageOffsetMap());

public:
   inline uint8_t getMaxIndex() const;
   inline uint8_t index(const float& voltage) const;
   inline float voltage(const uint8_t& index, bool applyOffset = true) const;

private:
   inline const VoltageList& voltageList(const ChannelCount& channelCount) const;

private:
   ChannelCount channelCount;
   VoltageOffsetMap offsetMap;
};

struct CvSwitch::StandardDevices
{
   enum class TargetDevice
   {
      MimeticDigitalis4,
      MimeticDigitalis16,
      ViceVirga2,
      ViceVirga4,
      ViceVirga8,
      TotalRecall
   };

   inline static CvSwitch create(const TargetDevice& device);

   inline static const std::string name(const TargetDevice& device);
   inline static ChannelCount channelCount(const TargetDevice& device);
   inline static VoltageOffsetMap offsetMap(const TargetDevice& device);
};

#ifndef CvSwitchHPP
#include "../../CvSwitch.hpp"
#endif

#endif // CvSwitchH
