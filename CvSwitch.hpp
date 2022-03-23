#ifndef CvSwitchHPP
#define CvSwitchHPP

#include <Blocks/CvSwitch.h>

CvSwitch::CvSwitch(const ChannelCount& channelCount, const VoltageOffsetMap& offsetMap)
   : channelCount(channelCount)
   , offsetMap(offsetMap)
{
}

uint8_t CvSwitch::getMaxIndex() const
{
   return static_cast<uint8_t>(channelCount);
}

float CvSwitch::map(const uint8_t index, bool applyOffset) const
{
   if (index >= getMaxIndex())
      return 0.0;

   float value = voltageList(channelCount).at(index);
   if (applyOffset)
   {
      VoltageOffsetMap::const_iterator it = offsetMap.find(index);
      if (it != offsetMap.end())
         value += it->second;
   }
   return value;
}

const CvSwitch::VoltageList& CvSwitch::voltageList(const ChannelCount& channelCount) const
{
   using VoltageMap = std::map<ChannelCount, VoltageList>;

   static VoltageMap voltageMap;
   if (voltageMap.empty())
   {
      voltageMap[ChannelCount::None] = VoltageList();

      for (const ChannelCount& cCount : {ChannelCount::Two, ChannelCount::Four, ChannelCount::Eight, ChannelCount::Sixteen})
      {
         const uint maxIndex = static_cast<uint8_t>(cCount);
         const float diff = 5.0 / maxIndex;
         const float offset = 0.5 * diff;

         VoltageList voltageList;
         for (uint8_t index = 0; index < maxIndex; index++)
         {
            const float value = offset + (index * diff);
            voltageList.push_back(value);
         }
         voltageMap[cCount] = voltageList;
      }
   }

   return voltageMap[channelCount];
}

// standard offsets

CvSwitch CvSwitch::StandardDevices::create(const TargetDevice& device)
{
   return CvSwitch(channelCount(device), offsetMap(device));
}

const std::string CvSwitch::StandardDevices::name(const TargetDevice& device)
{
   std::string name = "Unknown";
   switch (device)
   {
      case TargetDevice::MimeticDigitalis4:
         name = "Mimetic Digitalis 4";
         break;
      case TargetDevice::MimeticDigitalis16:
         name = "Mimetic Digitalis 16";
         break;
      case TargetDevice::ViceVirga2:
         name = "Vice Virga 2";
         break;
      case TargetDevice::ViceVirga4:
         name = "Vice Virga 4";
         break;
      case TargetDevice::ViceVirga8:
         name = "Vice Virga 8";
         break;
      case TargetDevice::TotalRecall:
         name = "Total Recall";
         break;
      default:
         break;
   }

   return name;
}

CvSwitch::ChannelCount CvSwitch::StandardDevices::channelCount(const TargetDevice& device)
{
   ChannelCount count = ChannelCount::None;
   switch (device)
   {
      case TargetDevice::ViceVirga2:
         count = ChannelCount::Two;
         break;
      case TargetDevice::MimeticDigitalis4:
      case TargetDevice::ViceVirga4:
         count = ChannelCount::Four;
         break;
      case TargetDevice::ViceVirga8:
      case TargetDevice::TotalRecall:
         count = ChannelCount::Eight;
         break;
      case TargetDevice::MimeticDigitalis16:
         count = ChannelCount::Sixteen;
         break;
      default:
         break;
   }

   return count;
}

CvSwitch::VoltageOffsetMap CvSwitch::StandardDevices::offsetMap(const TargetDevice& device)
{
   VoltageOffsetMap offestMap;

   switch (device)
   {
      case TargetDevice::MimeticDigitalis16:
         offestMap[14] = 0.03;
         offestMap[15] = 0.07;
         break;
      case TargetDevice::TotalRecall:
         offestMap[4] = -0.04;
         offestMap[5] = -0.08;
         offestMap[6] = -0.14;
         break;
      case TargetDevice::MimeticDigitalis4:
      case TargetDevice::ViceVirga2:
      case TargetDevice::ViceVirga4:
      case TargetDevice::ViceVirga8:
      default:
         break;
   }
   return offestMap;
}

#endif // CvSwitchHPP
