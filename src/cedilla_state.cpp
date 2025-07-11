/*
 * cedilla_state.cpp - fcitx5 module for Cedilla input method
 *
 * Copyright (C) 2025 msshtdev <dev.msshta@proton.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "cedilla_state.hpp"

#include <string>

#include "cedilla_engine.hpp"

namespace fcitx {
CedillaState::CedillaState(CedillaEngine *engine, InputContext *ic)
    : engine_(engine), ic_(ic) {
    composingText_ = std::string("");
}

void CedillaState::keyEvent(KeyEvent &keyEvent) {
    FCITX_INFO() << keyEvent.key() << " isRelease=" << keyEvent.isRelease();
}

void CedillaState::reset() {
    composingText_ = std::string("");
    isFr_ = false;
    ic_->inputPanel().reset();
}
}  // namespace fcitx
