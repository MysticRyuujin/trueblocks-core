/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "options.h"

//-------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
    nodeNotRequired();
    acctlib_init(quickQuitHandler);

    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    bool once = true;
    for (auto command : options.commandLines) {
        if (!options.parseArguments(command))
            return 0;

        if (options.isConfig) {
            if (once)
                cout << exportPreamble(expContext().fmtMap["header"], GETRUNTIME_CLASS(CConfiguration));
            options.handle_config(cout);

        } else {
            if (once)
                cout << exportPreamble(expContext().fmtMap["header"], "");
            options.handle_status(cout);
        }
        once = false;
    }
    cout << exportPostamble(options.errors, expContext().fmtMap["meta"]);

    acctlib_cleanup();
    return 0;
}
