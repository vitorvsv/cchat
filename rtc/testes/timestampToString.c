    #include <string.h>
    #include <stdio.h>
     
    typedef unsigned uint;
    typedef unsigned long long uint64;
     
    void SecondsSinceEpochToDateTime(uint64 SecondsSinceEpoch)
    {
      uint64 sec;
      uint quadricentennials, centennials, quadrennials, annuals/*1-ennial?*/;
      uint year, leap;
      uint yday, hour, min;
      uint month, mday, wday;
      static const uint daysSinceJan1st[2][13]=
      {
        {0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
        {0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
      };
     
      // Re-bias from 1970 to 1601:
      // 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
      // (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
      sec = SecondsSinceEpoch + 11644473600LL;
     
      wday = (uint)((sec / 86400 + 1) % 7); // day of week
     
      // Remove multiples of 400 years (incl. 97 leap days)
      quadricentennials = (uint)(sec / 12622780800ULL); // 400*365.2425*24*3600
      sec %= 12622780800ULL;
     
      // Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
      // (because multiples of 4*100=400 years (incl. leap days) have been removed)
      centennials = (uint)(sec / 3155673600ULL); // 100*(365+24/100)*24*3600
      if (centennials > 3)
      {
        centennials = 3;
      }
      sec -= centennials * 3155673600ULL;
     
      // Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
      // (because multiples of 25*4=100 years (incl. leap days) have been removed)
      quadrennials = (uint)(sec / 126230400); // 4*(365+1/4)*24*3600
      if (quadrennials > 24)
      {
        quadrennials = 24;
      }
      sec -= quadrennials * 126230400ULL;
     
      // Remove multiples of years (incl. 0 leap days), can't be more than 3
      // (because multiples of 4 years (incl. leap days) have been removed)
      annuals = (uint)(sec / 31536000); // 365*24*3600
      if (annuals > 3)
      {
        annuals = 3;
      }
      sec -= annuals * 31536000ULL;
     
      // Calculate the year and find out if it's leap
      year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
      leap = !(year % 4) && (year % 100 || !(year % 400));
     
      // Calculate the day of the year and the time
      yday = sec / 86400;
      sec %= 86400;
      hour = sec / 3600;
      sec %= 3600;
      min = sec / 60;
      sec %= 60;
     
      // Calculate the month
      for (mday = month = 1; month < 13; month++)
      {
        if (yday < daysSinceJan1st[leap][month])
        {
          mday += yday - daysSinceJan1st[leap][month - 1];
          break;
        }
      }
     
      // Fill in C's "struct tm"
      
      //printf("\n%d",(int)sec);          // [0,59]
      //printf("\n%d",(int)min);          // [0,59]
      //printf("\n%d",(int)hour);        // [0,23]
      //printf("\n%d",(int)mday);        // [1,31]  (day of month)
      //printf("\n%d",(month));    // [0,11]  (month)
      //printf("\n%d",(int)(year)); // 70+     (year since 1900)
    }

    int main(){
        SecondsSinceEpochToDateTime(1555935132);
        return 0;
    }