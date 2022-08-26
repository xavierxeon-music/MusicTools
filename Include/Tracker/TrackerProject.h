#ifndef TrackerProjectH
#define TrackerProjectH

#include <Remember.h>

#include <Music/Tempo.h>

#include "TrackerBank.h"

namespace Tracker
{
   pyexport class Project : public Remember::Container
   {
   public:
      pyexport inline Project();

   public:
      pyexport inline void clear(const uint8_t bankCount, const Tempo::Division& newDivision, const uint32_t newLength);

      pyexport inline void clockTick();
      pyexport inline void clockReset();

      pyexport inline const std::string getName() const;
      pyexport inline void setName(const std::string& text);

      pyexport inline uint8_t getBeatsPerMinute() const;
      pyexport inline void setBeatsPerMintute(const uint8_t value);

      pyexport inline Tempo::Division getDivison() const;
      pyexport inline uint32_t getLength() const;

      pyexport inline uint8_t getBankCount() const;
      pyexport inline Bank& getBank(const uint8_t index);

   private:
      using Name_ = Remember::String;
      using Tempo_ = Remember::Value<uint8_t>;
      using Division_ = Remember::Value<Tempo::Division>;
      using Length_ = Remember::Value<uint32_t>;
      using Banks_ = Remember::RefList<Bank>;
      using Loop_ = Remember::Value<bool>;

   private:
      Name_ name;
      Tempo_ beatsPerMinute;
      Division_ division;
      Length_ length;
      Banks_ banks;
      Loop_ loop;

      bool pastLoop;
   };
} // namespace Tracker

#ifndef TrackerProjectHPP
#include "../../TrackerProject.hpp"
#endif // NOT TrackerProjectHPP

#endif // NOT TrackerProjectH
