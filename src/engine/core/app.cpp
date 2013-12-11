#include "app.h"
#include "engine/virtual/context.h"

using namespace drill;

application::application() : _running(false), _frozen(false) {
}

application::~application() {
}

void application::add_service(service& serv) {
  _services.push_back(&serv);
  serv.init();
}

void application::run() {
  if (_frozen) {
    _frozen = false;
    return;
  }

  _timeinfo = { 0.0, 0.0, 0.0, 0.0 };
  clocks_at_start = clock();
  current_second = clocks_at_start / CLOCKS_PER_SEC;
  last_second = 0;
  last_frames = 0;

  LOG_INFO("CPS " << clocks_at_start);

  _running = true;
  while (_running) {
    if (_frozen) { continue; }
    for (auto serv : _services) {
      serv->update(_timeinfo);
    }

    _timeinfo.frames_since_start += 1; 
    
    // FIXME time information is incorrect
    _timeinfo.clocks_since_start = clock() - clocks_at_start;
    _timeinfo.seconds_since_start = _timeinfo.clocks_since_start / CLOCKS_PER_SEC;
    _timeinfo.average_fps = _timeinfo.frames_since_start / _timeinfo.seconds_since_start;

    if (last_second != _timeinfo.seconds_since_start) {
      _timeinfo.instant_fps = (_timeinfo.frames_since_start - last_frames) /
        (_timeinfo.seconds_since_start - last_second);
      last_second = _timeinfo.seconds_since_start;
      last_frames = _timeinfo.frames_since_start;
    }
  }
}

void application::freeze() {
  _frozen = true;
}

void application::kill() {
  _running = false;
}
