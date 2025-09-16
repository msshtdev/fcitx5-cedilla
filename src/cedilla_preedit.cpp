/*
 * cedilla_preedit.cpp - fcitx5 module for Cedilla input method
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

#include "cedilla_preedit.hpp"

#include <string>

namespace fcitx {

std::string CedillaPreedit::text() const {
    if (ic_->capabilityFlags().test(CapabilityFlag::Preedit)) {
        return ic_->inputPanel().clientPreedit().toString();
    } else {
        return ic_->inputPanel().preedit().toString();
    }
}

void CedillaPreedit::setPreedit(Text text) {
    text.setCursor(text.size());
    if (ic_->capabilityFlags().test(CapabilityFlag::Preedit)) {
        ic_->inputPanel().setClientPreedit(text);
    } else {
        ic_->inputPanel().setPreedit(text);
    }
}

void CedillaPreedit::commitPreedit() {
    if (ic_->capabilityFlags().test(fcitx::CapabilityFlag::Preedit)) {
        ic_->commitString(
            ic_->inputPanel().clientPreedit().toStringForCommit());
    } else {
        ic_->commitString(ic_->inputPanel().preedit().toStringForCommit());
    }
}

}  // namespace fcitx
