#ifndef CvSwitchHPP
#define CvSwitchHPP

#include <Blocks/CvSwitch.h>

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

const std::string CvSwitch::deviceName(const Device& device)
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

const CvSwitch::Device& CvSwitch::getDevice() const
{
   return device;
}

const uint8_t& CvSwitch::getMaxIndex() const
{
   return maxIndex;
}

float CvSwitch::map(const uint8_t index) const
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

#endif // CvSwitchHPP
