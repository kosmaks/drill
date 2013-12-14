#include "app.h"
#include "engine/virtual/context.h"

using namespace drill;

application::application() : _running(false), _frozen(false) {
  set_max_fps(60);
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
  clocks_at_last_update = 0;

  _running = true;
  while (_running) {
    if (_frozen) { continue; }

    uint32_t c = clock();
    if ((c - clocks_at_last_update) >= min_clocks_per_frame) {
      for (auto serv : _services) {
        serv->update(_timeinfo);
      }

      _timeinfo.frames_since_start += 1; 
      _timeinfo.clocks_since_start = clock() - clocks_at_start;
      _timeinfo.seconds_since_start = _timeinfo.clocks_since_start / CLOCKS_PER_SEC;
      _timeinfo.average_fps = _timeinfo.frames_since_start / _timeinfo.seconds_since_start;
      clocks_at_last_update = c;
    }
  }
}

void application::freeze() {
  _frozen = true;
}

void application::kill() {
  _running = false;
}

void application::set_max_fps(uint32_t fps) {
  max_fps = fps;
  min_clocks_per_frame = CLOCKS_PER_SEC / fps;
  LOG_DEBUG("min_clocks_per_frame = " << min_clocks_per_frame);
}
