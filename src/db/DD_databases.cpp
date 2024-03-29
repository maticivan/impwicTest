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

#ifndef _INCL_DATABASES_CPP
#define _INCL_DATABASES_CPP

#include "DSD_dbSetup.cpp"

namespace DD{
  DSD::Setup GL_DBS;
}



#include "MWID_mainWebInit.cpp"

namespace DD{
  MWID::MainDB GL_MAIN_DB;
}





#endif
