/*
 * cedilla_state.hpp - fcitx5 module for Cedilla input method
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

#ifndef SRC_CEDILLA_STATE_HPP_
#define SRC_CEDILLA_STATE_HPP_

#include <fcitx/inputcontext.h>
#include <fcitx/inputpanel.h>
#include <fcitx/surroundingtext.h>

#include <string>

namespace fcitx {

class CedillaEngine;

class CedillaState : public InputContextProperty {
   public:
    CedillaState(CedillaEngine *engine, InputContext *ic);
    void keyEvent(KeyEvent &keyEvent);
    void reset();

   private:
    CedillaEngine *engine_;
    InputContext *ic_;
    std::string composingText_;
    bool isFr_ = false;
};
}  // namespace fcitx

#endif  // SRC_CEDILLA_STATE_HPP_
