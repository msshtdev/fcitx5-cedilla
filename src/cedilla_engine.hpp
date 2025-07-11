/*
 * cedilla_engine.hpp - fcitx5 module for Cedilla input method
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

#ifndef SRC_CEDILLA_ENGINE_HPP_
#define SRC_CEDILLA_ENGINE_HPP_

#include <fcitx/addonfactory.h>
#include <fcitx/addonmanager.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx/instance.h>

#include "cedilla_state.hpp"

namespace fcitx {

class CedillaEngine : public fcitx::InputMethodEngineV2 {
   public:
    explicit CedillaEngine(Instance *instance);
    void activate(const InputMethodEntry &entry,
                  InputContextEvent &event) override;
    void deactivate(const InputMethodEntry &entry,
                    InputContextEvent &event) override;
    void keyEvent(const InputMethodEntry &entry, KeyEvent &keyEvent) override;
    auto factory() const { return &factory_; }
    auto instance() const { return &instance_; }

   private:
    Instance *instance_;
    FactoryFor<CedillaState> factory_;
};

class CedillaEngineFactory : public AddonFactory {
    AddonInstance *create(AddonManager *manager) override {
        return new CedillaEngine(manager->instance());
    }
};

}  // namespace fcitx

#endif  // SRC_CEDILLA_ENGINE_HPP_
