/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <broadcast.hxx>
#include <address.hxx>
#include <formulacell.hxx>

namespace sc {

BroadcasterState::CellListener::CellListener(const ScFormulaCell* p) :
    eType(ListenerType::FormulaCell), pData(p)
{
}

BroadcasterState::CellListener::CellListener(const SvtListener* p) :
    eType(ListenerType::Generic), pData(p)
{
}

void BroadcasterState::dump(std::ostream& rStrm, const ScDocument* pDoc) const
{
    constexpr ScRefFlags nPosFlags = ScRefFlags::VALID | ScRefFlags::TAB_3D;

    for (const auto& [rPos, rListeners] : aCellListenerStore)
    {
        rStrm << "* broadcaster: (" << rPos.Format(nPosFlags, pDoc) << ")" << std::endl;

        for (const auto& rLis : rListeners)
        {
            switch (rLis.eType)
            {
                case BroadcasterState::ListenerType::FormulaCell:
                {
                    auto* pFC = std::get<const ScFormulaCell*>(rLis.pData);
                    rStrm << "  * listener: formula cell (" << pFC->aPos.Format(nPosFlags, pDoc) << ")" << std::endl;
                    break;
                }
                case BroadcasterState::ListenerType::Generic:
                {
                    rStrm << "  * listener: unknown" << std::endl;
                    break;
                }
            }
        }
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
