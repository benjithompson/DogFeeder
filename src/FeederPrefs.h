#ifndef FEEDERPREFS_H
#define FEEDERPREFS_H
#include <Preferences.h>

  extern Preferences prefs;
  extern int breakfastTime;
  extern int dinnerTime;
  extern double feedCups;
  extern int restartRequested;

  void pullPreferences();
  int getBreakfastTime();
  int getDinnerTime();
  double getFeedCup();
  int setBreakfastTime(String command);
  int setDinnerTime(String command);
  int setFeedCups(String command);
  int resetPreferences(String command);
  void setRestartRequested(int restartState);
  void printPrefs(void);

#endif
