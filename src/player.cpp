#include "player.h"

RPlayer* RPlayer::createInstance() {
  RPlayer* pPlayer = new RPlayer();
  pPlayer->state = RPlayerState::INIT;
  return pPlayer;
}

int RPlayer::createDecodeThread(char* urlIn) {
  if (pid != 0) {
    dispose();
    state = RPlayerState::INIT;
  }

  url = urlIn;
  return pthread_create(&pid, nullptr, _decode, static_cast<void*>(this));
}

int RPlayer::dispose() {
  setStopped();
  if (pid == 0) {
    return 0;
  }

  if (int threadReturn = pthread_join(pid, nullptr) != 0) {
    setError("Failed to detach decode thread: code %d.", threadReturn);
  }

  LOG::D("Decode thread finished. PID: %ld", pid);

  if (pTextureAndroid != nullptr && pTextureAndroid->release() != 0) {
    setError(
        "Failed to release native window. This might cause unpredictable "
        "error when you create a decode thread from RPlayer next time.");
  }

  decoder->release();
  decoder = nullptr;

  config->release();
  config = nullptr;

  return 0;
}

int RPlayer::getHeight() {
  if (decoder == nullptr || decoder->codecContext == nullptr) {
    return 0;
  }
  return decoder->codecContext->height;
}

int RPlayer::getWidth() {
  if (decoder == nullptr || decoder->codecContext == nullptr) {
    return 0;
  }
  return decoder->codecContext->width;
}

void RPlayer::setBuffering() {
  if (state == RPlayerState::STOPPED || state == RPlayerState::ERROR) {
    LOG::E("Failed to set player state to BUFFERING: player in state %d",
           state);
    return;
  }
  state = RPlayerState::BUFFERING;
}

void RPlayer::setPlaying() {
  if (state != RPlayerState::PAUSED && state != RPlayerState::BUFFERING) {
    LOG::E("Failed to set player state to PLAYING: player in state %d", state);
    return;
  }
  state = RPlayerState::PLAYING;
}

void RPlayer::setPaused() {
  if (state != RPlayerState::PLAYING && state != RPlayerState::BUFFERING) {
    LOG::E("Failed to set player state to PAUSED: player in state %d", state);
    return;
  }
  state = RPlayerState::PAUSED;
}

void RPlayer::setStopped() {
  state = RPlayerState::STOPPED;
}

void RPlayer::setError(const char* fmt, ...) {
  if (state == RPlayerState::STOPPED) {
    LOG::E("Failed to set player state to ERROR: player in state %d", state);
    return;
  }
  state = RPlayerState::ERROR;
  va_list args;
  va_start(args, fmt);
  __android_log_vprint(ANDROID_LOG_ERROR, LOG::TAG, fmt, args);
  vsprintf(msg, fmt, args);
  va_end(args);
}
