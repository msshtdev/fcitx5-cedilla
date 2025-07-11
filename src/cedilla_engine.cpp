/*
 * cedilla_engine.cpp - fcitx5 module for Cedilla input method
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

#include "cedilla_engine.hpp"

#include "cedilla_state.hpp"

namespace fcitx {

CedillaEngine::CedillaEngine(Instance *instance)
    : instance_(instance), factory_([this](InputContext &ic) {
          return new CedillaState(this, &ic);
      }) {
    instance->inputContextManager().registerProperty("CedillaState", &factory_);
}

void CedillaEngine::activate(const InputMethodEntry &entry,
                             InputContextEvent &event) {
    FCITX_UNUSED(entry);
    FCITX_DEBUG() << "CedillaEngine activate";

    auto inputContext = event.inputContext();
    auto state = inputContext->propertyFor(&factory_);
    state->reset();
    inputContext->updatePreedit();
    inputContext->updateUserInterface(UserInterfaceComponent::InputPanel);
}

void CedillaEngine::deactivate(const InputMethodEntry &entry,
                               InputContextEvent &event) {
    FCITX_UNUSED(entry);
    FCITX_DEBUG() << "CedillaEngine deactivate";

    auto inputContext = event.inputContext();
    auto state = inputContext->propertyFor(&factory_);
    state->reset();
    inputContext->updatePreedit();
    inputContext->updateUserInterface(UserInterfaceComponent::InputPanel);
}

void CedillaEngine::keyEvent(const InputMethodEntry &entry,
                             KeyEvent &keyEvent) {
    FCITX_UNUSED(entry);
    FCITX_DEBUG() << keyEvent.key() << " isRelease=" << keyEvent.isRelease();

    auto inputContext = keyEvent.inputContext();
    inputContext->propertyFor(&factory_)->keyEvent(keyEvent);
    inputContext->updatePreedit();
    inputContext->updateUserInterface(UserInterfaceComponent::InputPanel);
}

FCITX_ADDON_FACTORY(CedillaEngineFactory)

}  // namespace fcitx
