/*
 * cedilla_ruleset.cpp - fcitx5 module for Cedilla input method
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

#include "cedilla_ruleset.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>

const std::unordered_set<std::string> triggerLetterSet{"`", "'", ":", "^", ",",
                                                       "a", "A", "o", "O"};

const std::unordered_map<std::string, std::string> convertTable = {
    {"`A", "À"}, {"`a", "à"}, {":A", "Ä"}, {":a", "ä"}, {"^A", "Â"},
    {"^a", "â"}, {"AE", "Æ"}, {"ae", "æ"}, {",C", "Ç"}, {",c", "ç"},
    {"`E", "È"}, {"`e", "è"}, {"'E", "É"}, {"'e", "é"}, {":E", "Ë"},
    {":e", "ë"}, {"^E", "Ê"}, {"^e", "ê"}, {":I", "Ï"}, {":i", "ï"},
    {"^I", "Î"}, {"^i", "î"}, {"^O", "Ô"}, {"^o", "ô"}, {"OE", "Œ"},
    {"oe", "œ"}, {"`U", "Ù"}, {"`u", "ù"}, {":U", "Ü"}, {":u", "ü"},
    {"^U", "Û"}, {"^u", "û"}};

extern const std::unordered_map<std::string, std::string> ligatureTable = {
    {"AE", "Æ"}, {"ae", "æ"}, {"OE", "Œ"}, {"oe", "œ"}};
