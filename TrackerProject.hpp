#ifndef TrackerProjectHPP
#define TrackerProjectHPP

#include <Tracker/TrackerProject.h>

Tracker::Project::Project()
   : Remember::Container()
   , name(this, "")
   , beatsPerMinute(this, 120)
   , division(this, Tempo::Bar)
   , segmentCount(this, 0)
   , banks(this)
   , loop(this, false)
   , pastLoop(false)
{
}

void Tracker::Project::clear(const uint8_t bankCount, const Tempo::Division& newDivision, const uint32_t newSegementCount)
{
   division = newDivision;
   segmentCount = newSegementCount;

   banks.clear();
   for (uint8_t index = 0; index < bankCount; index++)
   {
      Bank bank;
      bank.init(segmentCount);
      banks.append(bank);
   }

   Remember::Root::setUnsynced();
}

void Tracker::Project::clockTick()
{
}

void Tracker::Project::clockReset()
{
}

const std::string Tracker::Project::getName() const
{
   return name;
}

void Tracker::Project::setName(const std::string& text)
{
   name = text;
   Remember::Root::setUnsynced();
}

uint8_t Tracker::Project::getBeatsPerMinute() const
{
   return beatsPerMinute;
}

void Tracker::Project::setBeatsPerMintute(const uint8_t value)
{
   beatsPerMinute = value;
   Remember::Root::setUnsynced();
}

Tempo::Division Tracker::Project::getDivison() const
{
   return division;
}

uint32_t Tracker::Project::getSegementCount() const
{
   return segmentCount;
}

uint8_t Tracker::Project::getBankCount() const
{
   return banks.size();
}

Tracker::Bank& Tracker::Project::getBank(const uint8_t index)
{
   return banks[index];
}

bool Tracker::Project::isLooping() const
{
   return loop;
}

void Tracker::Project::setLooping(bool on)
{
   loop = on;
   Remember::Root::setUnsynced();
}

#endif // NOT TrackerProjectHPP
