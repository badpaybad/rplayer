#include "ffi_flutter.h"

extern "C" {
DART_EXPORT void* RPlayer_createInstance() {
  return static_cast<void*>(RPlayer::createInstance());
}

DART_EXPORT int RPlayer_createDecodeThread(void* p, char* url) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  return pPlayer->createDecodeThread(url);
}

DART_EXPORT void RPlayer_setPlaying(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  pPlayer->setPlaying();
}

DART_EXPORT void RPlayer_setPaused(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  pPlayer->setPaused();
}

DART_EXPORT int RPlayer_dispose(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  if (int disposeResult = pPlayer->dispose() != 0) {
    return disposeResult;
  }
  delete pPlayer;
  return 0;
}

DART_EXPORT int RPlayer_getHeight(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  return pPlayer->getHeight();
}

DART_EXPORT int RPlayer_getWidth(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  return pPlayer->getWidth();
}

DART_EXPORT int RPlayer_getState(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  return pPlayer->state;
}

DART_EXPORT long RPlayer_getTextureId(void* p) {
  RPlayer* pPlayer = static_cast<RPlayer*>(p);
  if (pPlayer->pTextureAndroid == nullptr) {
    return -1;
  }
  return static_cast<long>(pPlayer->pTextureAndroid->id);
}
}
