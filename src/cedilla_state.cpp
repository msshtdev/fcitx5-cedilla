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
#include "cedilla_preedit.hpp"
#include "cedilla_ruleset.hpp"

namespace fcitx {

CedillaState::CedillaState(CedillaEngine *engine, InputContext *ic)
    : engine_(engine), ic_(ic), preedit_(CedillaPreedit(ic)) {
    composingText_ = std::string("");
}

void CedillaState::keyEvent(KeyEvent &keyEvent) {
    if (keyEvent.isRelease()) {
        return;
    }

    if (keyEvent.key().states() == KeyState::Shift &&
        keyEvent.key().sym() == FcitxKey_space) {
        isFr_ = !isFr_;
        composingText_ = std::string("");
        preedit_.setPreedit(Text(composingText_));
        return keyEvent.filterAndAccept();
    }

    if (!isFr_) {
        return keyEvent.filter();
    }

    handleFrKeyEvent(keyEvent);
}

void CedillaState::handleFrKeyEvent(KeyEvent &keyEvent) {
    auto key = keyEvent.key();
    auto keysym = key.sym();
    std::string newLetter = Key::keySymToUTF8(keysym);

    if (key.states() == KeyState::Ctrl) {
        return keyEvent.filter();
    }

    if (composingText_.empty()) {
        if (triggerLetterSet.find(newLetter) != triggerLetterSet.end()) {
            composingText_ += newLetter;
            preedit_.setPreedit(Text(composingText_));
        } else {
            return keyEvent.filter();
        }
    } else {
        switch (keysym) {
            case FcitxKey_Return:
                preedit_.commitPreedit();
                reset();
                break;
            case FcitxKey_BackSpace:
                composingText_.pop_back();
                preedit_.setPreedit(Text(composingText_));
                break;
            case FcitxKey_Escape:
                reset();
                break;
            case FcitxKey_Tab: {
                auto convertIter = convertTable.find(composingText_);
                if (convertIter == convertTable.end()) {
                    ic_->commitString(composingText_);
                    composingText_ = std::string("");
                    preedit_.setPreedit(Text(composingText_));
                    return keyEvent.filter();
                }
                ic_->commitString(convertIter->second);
                composingText_ = std::string("");
                preedit_.setPreedit(Text(composingText_));
                break;
            }
            default:
                if (key.isSimple()) {
                    composingText_ += newLetter;

                    auto convertIter = convertTable.find(composingText_);
                    if (convertIter != convertTable.end()) {
                        if (ligatureTable.find(composingText_) ==
                            ligatureTable.end()) {
                            composingText_ = "";
                            ic_->commitString(convertIter->second);
                        }
                    } else {
                        std::string lastLetter =
                            std::string(1, composingText_.back());
                        if (triggerLetterSet.find(lastLetter) !=
                            triggerLetterSet.end()) {
                            composingText_.pop_back();
                            ic_->commitString(composingText_);
                            composingText_ = lastLetter;
                        } else {
                            ic_->commitString(composingText_);
                            composingText_ = "";
                        }
                    }
                    preedit_.setPreedit(Text(composingText_));
                    break;
                } else {
                    return keyEvent.filter();
                }
        }
    }
    return keyEvent.filterAndAccept();
}

void CedillaState::reset() {
    composingText_ = std::string("");
    ic_->inputPanel().reset();
}
}  // namespace fcitx
