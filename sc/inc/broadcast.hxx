/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <address.hxx>

#include <map>
#include <variant>
#include <ostream>

class ScFormulaCell;
class SvtListener;

namespace sc {

struct BroadcasterState
{
    enum class ListenerType
    {
        FormulaCell,
        Generic,
    };

    struct CellListener
    {
        using DataType = std::variant<const ScFormulaCell*, const SvtListener*>;

        ListenerType eType;
        DataType pData;

        CellListener(const ScFormulaCell* p);
        CellListener(const SvtListener* p);
    };

    std::map<ScAddress, std::vector<CellListener>> aCellListenerStore;

    void dump(std::ostream& rStrm, const ScDocument* pDoc = nullptr) const;
};

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
