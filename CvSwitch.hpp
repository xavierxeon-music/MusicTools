#ifndef CvSwitchHPP
#define CvSwitchHPP

#include <Blocks/CvSwitch.h>

CvSwitch::CvSwitch(const Size& size, const VoltageOffsetMap& offsetMap)
   : size(size)
   , offsetMap(offsetMap)
{
}

uint8_t CvSwitch::getMaxIndex() const
{
   return static_cast<uint8_t>(size);
}

float CvSwitch::map(const uint8_t index, bool applyOffset) const
{
   if (index >= getMaxIndex())
      return 0.0;

   float value = voltageList(size).at(index);
   if (applyOffset)
   {
      VoltageOffsetMap::const_iterator it = offsetMap.find(index);
      if (it != offsetMap.end())
         value += it->second;
   }
   return value;
}

const CvSwitch::VoltageList& CvSwitch::voltageList(const Size& size) const
{
   using VoltageMap = std::map<Size, VoltageList>;

   static VoltageMap voltageMap;
   if (voltageMap.empty())
   {
      voltageMap[Size::Invalid] = VoltageList();

      for (const Size& size : {Size::Two, Size::Four, Size::Eight, Size::Sixteen})
      {
         const uint maxIndex = static_cast<uint8_t>(size);
         const float diff = 1.0 / maxIndex;
         const float offset = 0.5 * diff;

         VoltageList voltageList;
         for (uint8_t index = 0; index < maxIndex; index++)
         {
            const float value = offset + (index * diff);
            voltageList.push_back(value);
         }
         voltageMap[size] = voltageList;
      }
   }

   return voltageMap[size];
}

// standard offsets

const std::string CvSwitch::StandardDevices::name(const Device& device)
{
   std::string name = "Unknown";
   switch (device)
   {
      case Device::MimeticDigitalis4:
         name = "Mimetic Digitalis 4";
         break;
      case Device::MimeticDigitalis16:
         name = "Mimetic Digitalis 16";
         break;
      case Device::ViceVirga2:
         name = "Vice Virga 2";
         break;
      case Device::ViceVirga4:
         name = "Vice Virga 4";
         break;
      case Device::ViceVirga8:
         name = "Vice Virga 8";
         break;
      case Device::TotalRecall:
         name = "Total Recall";
         break;
      default:
         break;
   }

   return name;
}

CvSwitch::Size CvSwitch::StandardDevices::size(const Device& device)
{
   Size size = Size::Invalid;
   switch (device)
   {
      case Device::MimeticDigitalis4:
      case Device::ViceVirga4:
         size = 4;
         break;
      case Device::MimeticDigitalis16:
         size = 16;
         break;
      case Device::ViceVirga2:
         size = 2;
      case Device::ViceVirga8:
         maxIndex = 8;
         offsetVoltageList = VoltageList(8, 0.0);
         break;
      case Device::TotalRecall:
         maxIndex = 8;
         offsetVoltageList = VoltageList(8, 0.0);
         offsetVoltageList[4] = -0.0100;
         offsetVoltageList[5] = -0.0235;
         offsetVoltageList[6] = -0.0350;
         break;
      default:
         break;
   }

   return size;
}

CvSwitch::VoltageOffsetMap CvSwitch::StandardDevices::offsetMap(const Device& device)
{
}

/*
static const CvSwitch::VoltageMap defaultVoltageMap = CvSwitch::compileVoltageMap();

CvSwitch::CvSwitch(const Device& device)
   : maxIndex(0)
   , offsetVoltageList()
   , device(device)
{
   switch (device)
   {
      case Device::MimeticDigitalis4:
         maxIndex = 4;
         offsetVoltageList = VoltageList(4, 0.0);
         break;
      case Device::MimeticDigitalis16:
         maxIndex = 16;
         offsetVoltageList = VoltageList(16, 0.0);
         offsetVoltageList[14] = 0.0140;
         offsetVoltageList[15] = 0.0140;
         break;
      case Device::ViceVirga2:
         maxIndex = 2;
         offsetVoltageList = VoltageList(2, 0.0);
         break;
      case Device::ViceVirga4:
         maxIndex = 4;
         offsetVoltageList = VoltageList(4, 0.0);
         break;
      case Device::ViceVirga8:
         maxIndex = 8;
         offsetVoltageList = VoltageList(8, 0.0);
         break;
      case Device::TotalRecall:
         maxIndex = 8;
         offsetVoltageList = VoltageList(8, 0.0);
         offsetVoltageList[4] = -0.0100;
         offsetVoltageList[5] = -0.0235;
         offsetVoltageList[6] = -0.0350;
         break;
      default:
         break;
   }
}

float CvSwitch::map(const uint8_t index, bool applyOffset) const
{
   if (index >= maxIndex)
      return 0.0;

   const float& value = defaultVoltageMap.at(maxIndex).at(index) + offsetVoltageList.at(index);
   return value;
}

CvSwitch::VoltageMap CvSwitch::compileVoltageMap()
{
   VoltageMap voltageMap;

   for (const uint8_t maxIndex : {2, 4, 8, 16})
   {
      const float diff = 1.0 / maxIndex;
      const float offset = 0.5 * diff;

      VoltageList voltageList;
      for (uint8_t index = 0; index < maxIndex; index++)
      {
         const float value = offset + (index * diff);
         voltageList.push_back(value);
      }
      voltageMap[maxIndex] = voltageList;
   }

   return voltageMap;
}
*/

#endif // CvSwitchHPP
