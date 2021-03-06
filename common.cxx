#include "common.h"


std::ostream& get_time(std::ostream& out, time_t const& start)
{
  time_t end;
  time(&end);//measure time when the calculation is done
  int seconds = difftime(end, start);//subtract start from end and return seconds
  int mins = seconds / 60;
  seconds %= 60;
  int hours = mins / 60;
  mins %= 60;
  out << hours << 'h' << mins << 'm' << seconds << 's';
  return out;
}

