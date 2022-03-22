#ifndef CvSwitchH
#define CvSwitchH

#include <map>

#include <MusicTools.h>

class CvSwitch
{
public:
   enum class Size
   {
      None = 1,
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
   inline CvSwitch(const Size& size, const VoltageOffsetMap& offestMap = VoltageOffsetMap());

public:
   inline uint8_t getMaxIndex() const;
   inline float map(const uint8_t index, bool applyOffset = true) const;

private:
   inline const VoltageList& voltageList(const Size& size);

private:
   Size size;
   VoltageOffsetMap offestMap;
};

struct CvSwitch::StandardDevices
{
   enum class Device
   {
      MimeticDigitalis4,
      MimeticDigitalis16,
      ViceVirga2,
      ViceVirga4,
      ViceVirga8,
      TotalRecall
   };

   inline static const std::string name(const Device& device);
   inline static Size size(const Device& device);
   inline static VoltageOffsetMap offsetMap(const Device& device);
};

#include "CvSwitch.hpp"

#endif // CvSwitchH
