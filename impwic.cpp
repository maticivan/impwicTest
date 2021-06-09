//    impwic-test : simple content management system
//
//    Copyright (C) 2021 Ivan Matic, https://impwic.com
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see https://www.gnu.org/licenses/.



#include "src/fundamental/SHF_standardHeaders.cpp"

#include "src/fundamental/MTF_mainTable.cpp"

#include "src/db/DD_databases.cpp"
#include "src/interface/BI_baseFunctions.cpp"
#include "src/interface/MWII_mainWI.cpp"

int main() {

  cgicc::Cgicc ch;

  std::string setups=IOF::fileToString("setupWSAll.txt");
  HDPF::GLOBAL_PS.getSetupFromString(setups);

  DD::GL_DBS.getSetupFromString(setups);
  DD::GL_MAIN_DB.initialize();

  SII::SessionInformation mainSession;


  mainSession.initSession(ch);
  std::cout<<mainSession.preparePage()<<"\n";

  return 0;
}
